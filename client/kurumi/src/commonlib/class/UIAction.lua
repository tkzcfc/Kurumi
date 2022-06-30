-- @Author : fc
-- @Date   : 2022-03-21 14:58:47
-- @remark : 

local UIAction = {}

local UIActionType = enum {
	"SCALE_TO",
	"NO_ACTION"
}

local openActions = {}
local closeActions = {}

UIAction.openActions = openActions
UIAction.closeActions = closeActions


global.UIActionType = UIActionType

-------------------------------------------- SCALE_TO --------------------------------------------

-- @brief 打开动画
openActions[UIActionType.SCALE_TO] = function (this, call)
	local actNode = this.pContentView or this
	
	actNode:setScale(0.3)

    local action = cc.Sequence:create(
    	cc.ScaleTo:create(0.25, 1.1), 
    	cc.ScaleTo:create(0.1, 1.0), 
    	cc.CallFunc:create(call)
    )
    actNode:runAction(action)
end


-- @brief 关闭动画
closeActions[UIActionType.SCALE_TO] = function(this, call)
	local actNode = this.pContentView or this

    actNode:setScale(1.0)

    local action = cc.Sequence:create(
    	cc.ScaleTo:create(0.1, 1.1), 
    	cc.ScaleTo:create(0.25, 0.5), 
    	cc.CallFunc:create(call)
    )
    actNode:runAction(action)
end


-------------------------------------------- NO_ACTION --------------------------------------------

-- @brief 打开动画
openActions[UIActionType.NO_ACTION] = function (this, call)
	call()
end


-- @brief 关闭动画
closeActions[UIActionType.NO_ACTION] = function(this, call)
	call()
end

return UIAction

