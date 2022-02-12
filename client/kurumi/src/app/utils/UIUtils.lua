-- @Author: fangcheng
-- @Date:   2020-03-22 15:46:45
-- @remark: UI工具方法相关


local UIUtils = {}


local remindMap = {}
local ttfConfig = 
{
    fontFilePath = "fonts/huakang.ttf",
    fontSize = 38,
}

-- @brief 显示软文提示
-- @param text 提示文字
-- @param rootNode 父节点，可选
function UIUtils:showRemind(text, rootNode)
    if G_MACROS.DEBUG then
        print("showRemind:", text)
        assert(type(text) == 'string')
    else
        text = tostring(text)
    end

	if remindMap[text] then
		return
	end

    if rootNode == nil then
        local scene = display.getRunningScene()

        rootNode = scene:getChildByName("__remind_node_")
        if rootNode == nil then
            rootNode = cc.Node:create()
            rootNode:setName("__remind_node_")
            scene:addChild(rootNode, 0xff)
        end
    end

	local sprite = ccui.ImageView:create("plist/bg_remind.png")
	sprite:setPosition(display.cx, display.cy)
	sprite:setCascadeOpacityEnabled(true)
	sprite:setOpacity(0)
	rootNode:addChild(sprite)

    local spriteRawSize = sprite:getContentSize()
    local minWidth = spriteRawSize.width - 300
    local maxWidth = display.width - 300

    sprite:setCapInsets({x = 200, y = 20, width = spriteRawSize.width - 400, spriteRawSize.height - 40})


    local label = cc.Label:createWithTTF(ttfConfig, text, cc.TEXT_ALIGNMENT_CENTER, maxWidth)
    label:setTextColor(cc.c3b(255,255,255))
    sprite:addChild(label)

    local labelSize = label:getContentSize()
    if labelSize.width > minWidth then
        spriteRawSize.width = labelSize.width + 300
    end
    spriteRawSize.height = labelSize.height + 30
    sprite:setContentSize(spriteRawSize)
    label:setPosition(spriteRawSize.width * 0.5, spriteRawSize.height * 0.5 + 4)

    sprite:runAction(cc.Sequence:create({
        cc.FadeIn:create(0.4),
        cc.DelayTime:create(2),
        cc.Spawn:create(cc.MoveTo:create(0.4, cc.p(display.cx, display.cy + 100)),
        cc.FadeOut:create(0.4)),
        cc.CallFunc:create(function() remindMap[text] = nil end),
        cc.RemoveSelf:create()
    }))

    remindMap[text] = sprite
end

function UIUtils:showError(err, ...)
    local cfg = G_Config.Error.getData(err)
    if not  cfg then
        print("Error表中找不到错误:", err)
        return
    end

    local args = {...}
    if #args > 0 then
        UIUtils:showRemind(string.format(STR(cfg.Lang), ...))
    else
        UIUtils:showRemind(STR(cfg.Lang))
    end
end

-- @brief 显示带有只有一个选项的弹窗
function UIUtils:showOneBtnMsgBox(content, call)
    local box = require("app.ui.general.UIMessageBox").new()
    box:showOneButton(content, call)
    box:show()
    return box
end

-- @brief 显示带有两个选项的弹窗
function UIUtils:showTwoBtnMsgBox(content, okCall, cancelCall)
    local box = require("app.ui.general.UIMessageBox").new()
    box:showTwoButton(content, okCall, cancelCall)
    box:show()
    return box
end

-- @brief 当Button作为ScrollView的间接节点时会影响到ScrollView的滑动以及button点击效果
--        这里监听touch事件来确定button是否点击，以及设定不吞没事件来保证ScrollView的正常滑动
-- @param widget widget以及其子类
-- @param listener 回调函数
function UIUtils:addClickEventListener(widget, listener)
    widget:setSwallowTouches(false)
    widget:addTouchEventListener(function (sender, eventType)
        if eventType == ccui.TouchEventType.moved then
            if not sender.isMovingTag then
                if cc.pDistanceSQ(sender:getTouchBeganPosition(), sender:getTouchMovePosition()) > 9 then
                    sender.isMovingTag = true
                end
            end
        elseif eventType == ccui.TouchEventType.ended or eventType == ccui.TouchEventType.canceled then
            if not sender.isMovingTag then
                listener(sender)
            end
            sender.isMovingTag = false
        end
    end)
end

-- @brief ccui.ListView转换为TableViewEx
function UIUtils:convertToTableView(listView)
    local panelSize = listView:getContentSize()
    local tableView = TableViewEx:create(panelSize)
    tableView:setAnchorPoint(listView:getAnchorPoint())
    tableView:setScaleX(listView:getScaleX())
    tableView:setScaleY(listView:getScaleY())
    listView:getParent():addChild(tableView)
    listView:removeFromParent()
    return tableView
end

-- @brief 获取当前tableView总行数
-- @param dataArr 数据数组
-- @param itemCount 一行显示多少个
function UIUtils:getTableViewCellCount(dataArr, itemCount)
    if #dataArr <= 0 then
        return 0
    end
    return math.ceil(#dataArr / itemCount)
end

-- @brief 获取当前tableView总行数
-- @param dataCount 数据个数
-- @param itemCount 一行显示多少个
function UIUtils:getTableViewCellCountByDataCount(dataCount, itemCount)
    if dataCount <= 0 then
        return 0
    end
    return math.ceil(dataCount / itemCount)
end

-- @brief 获取当前数据开始下标
-- @param index tableView返回的当前Cell下标
-- @param itemCount 一行显示多少个
function UIUtils:getTableViewDataArrIndex(index, itemCount)
    return index * itemCount + 1
end


cc.exports.UIUtils = UIUtils
