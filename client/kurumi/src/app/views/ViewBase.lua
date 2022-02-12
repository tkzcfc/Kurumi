-- @Author : fc
-- @Date   : 2021-10-29 15:35:44
-- @remark : 


local ViewBase = class("ViewBase", G_Class.SuperNode)

property(ViewBase, "pUIRoot")

function ViewBase:ctor()
    self.iFullWindowCount = 0

    -- UI根节点
    self.pUIRoot = cc.Node:create()
    self:addChild(self.pUIRoot, 0xFFFFFF)

    self:setNodeEventEnabled(true)
end

-- @interface 异步加载数据逻辑
-- @param loader [class LoadAsync]
function ViewBase:onAsyncLoad(loader)
end

-- @interface 加载完成,加载界面相关
function ViewBase:onLoadView()
end

function ViewBase:loadUILua(path)
    self.ui = G_Helper.loadStudioFile(path, self)
    self:addChild(self.ui.root)
end

function ViewBase:initWithParameter(args)
end

-- @brief 监听网络消息
-- @param msgID 消息ID
-- @param call 回调
-- @param priority 监听优先级
function ViewBase:onNetMsg(msgID, call, priority)
    G_NetEventEmitter:on(msgID, call, self, priority)
end

-- @brief 监听系统消息
-- @param msgID 消息ID
-- @param call 回调
-- @param priority 监听优先级
function ViewBase:onSysMsg(msgID, call, priority)
    G_SysEventEmitter:on(msgID, call, self, priority)
end

function ViewBase:onEnter()
    self:onSysMsg(SysEvent.UI_SHOW_FINISH, function(window, unique)
        if not unique then return end
        if self ~= _MyG.ViewManager:getCurView() then return end

        self.iFullWindowCount = self.iFullWindowCount + 1
        if self.iFullWindowCount == 1 then
            self:onHideNodes()
        end
    end)

    self:onSysMsg(SysEvent.UI_DISMISS, function(window, unique)
        if not unique then return end
        if self ~= _MyG.ViewManager:getCurView() then return end

        self.iFullWindowCount = self.iFullWindowCount - 1
        if self.iFullWindowCount == 0 then
            self:onShowNodes()
        end
    end)

    if type(self.initNetEvent) == "function" then
        self:initNetEvent()
    end
end

function ViewBase:onExit()
    G_NetEventEmitter:offByTag(self)
    G_SysEventEmitter:offByTag(self)
end

-- @brief 返回按键按下
function ViewBase:onKeyBackReleased()
end

-- @brief 优化操作,隐藏场景子节点
function ViewBase:onHideNodes()
    self.ui.root:setVisible(false)
end

-- @brief 优化操作,显示场景子节点
function ViewBase:onShowNodes()
    self.ui.root:setVisible(true)
end

return ViewBase


