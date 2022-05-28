-- @Author : fc
-- @Date   : 2021-10-29 15:35:44
-- @remark : 


local ViewBase = class("ViewBase", G_Class.SuperNode)

property(ViewBase, "pUIRoot")

function ViewBase:ctor()
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
    self:onSysMsg(SysEvent.UPDATE_VIEW_VISIBLE, function(show)
        local hide = not show

        if self.bCurIsHide == hide then
            return
        end
        self.bCurIsHide = hide
        if hide then
            self:onHideNodes()
        else
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
    if self.ui == nil then return end
    self.ui.root:setVisible(false)
    -- print("hide me------------>>>")
end

-- @brief 优化操作,显示场景子节点
function ViewBase:onShowNodes()
    if self.ui == nil then return end
    self.ui.root:setVisible(true)
    -- print("show me------------>>>")
end

return ViewBase


