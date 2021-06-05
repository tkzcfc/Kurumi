-- @Author: fangcheng
-- @Date:   2020-11-07 16:33:58
-- @remark: 针对commonlib/G_Helper的扩展

cc.exports.socket = {}
local socket = require("socket")

function G_Helper.loadStudioFile(fileName, target)
    local ui = require(fileName).create(function (path, node, funcName)
        if target == nil then
            return
        end
        return function(...) 
            if target[funcName] and type(target[funcName]) == "function" then
                target[funcName](target, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
        end
    end)

    local root = ui.root
    if root:getChildrenCount() == 1 then
        local contentNode = root:getChildByName("Panel_Content")
        contentNode:setContentSize(display.size)
        ccui.Helper:doLayout(contentNode)

        contentNode:removeFromParent()
        ui.root = contentNode
    end

    return ui
end

function G_Helper:gettime()
    return socket.gettime()
end
