local GameSceneSwither = class("GameSceneSwither")


function GameSceneSwither:switchTo()

end

function GameSceneSwither:enterScene(sceneName, transition, time, more)
    local view = self:createView(sceneName)
    view:showWithScene(transition, time, more)
    self.curView = view
    return view
end

return GameSceneSwither