-- @Author : fc
-- @Date   : 2021-10-29 18:13:17
-- @remark : 主界面


local MainView = class("MainView", import(".ViewBase"))


local kType = {
    FIGHT = 1,
    PVP   = 2,
    Test  = 3,
}

function MainView:onLoadView()
    MainView.super.onLoadView(self)

    self:loadUILua("ccs.views.UI_MainView")

    -- changeParticleSystemPositionType(self.ui.root, 2)

    self.ui.ScrollView:jumpToPercentHorizontal(35)
    self.ui.ScrollView:setScrollBarEnabled(false)

    local children = self.ui.Panel_Touch:getChildren()
    for k, v in pairs(children) do
        UIUtils:addClickEventListener(v, function()
            self:onClickUnit(v.UserData[1])
        end)
    end
end

function MainView:onClickUnit(sysId)
    sysId = tonumber(sysId)
    print("onClickUnit", sysId)
    
    if kType.FIGHT == sysId then
        require("app.ui.home.MapWindow").new():show()
    elseif kType.PVP == sysId then
        require("app.ui.pvp.Matching").new():show()
    elseif kType.Test == sysId then
        -- self:playVideo()
        
        require("app.ui.test.TestMain").new():show()
    end
end

function MainView:onClickEnter()
    print("onClickEnter---------->>")
end

function MainView:playVideo()
    require("app.ui.general.UIVideoPlay").new():show()
    
    
    -- local visibleRect = cc.Director:getInstance():getOpenGLView():getVisibleRect()
    -- local videoFullPath = cc.FileUtils:getInstance():fullPathForFilename("video/plot.mp4")

    -- local width = visibleRect.width/2
    -- local height = visibleRect.height/2
    -- local x = display.cx
    -- local y = display.cy

    -- local Layout = ccui.Layout:create() 
    -- Layout:setAnchorPoint(0.5, 0.5)
    -- Layout:setPosition(cc.p(x, y))
    -- Layout:setContentSize(cc.size(width, height))
    -- self:addChild(Layout)


    -- local videoPlayer = ccui.VideoPlayer:create()
    -- local function onVideoEventCallback(sener, eventType)
    --     if eventType == ccui.VideoPlayerEvent.PLAYING then
    --     elseif eventType == ccui.VideoPlayerEvent.PAUSED then
    --     elseif eventType == ccui.VideoPlayerEvent.STOPPED then
    --     elseif eventType == ccui.VideoPlayerEvent.COMPLETED then
    --         videoPlayer:stop()
    --         videoPlayer:runAction(cc.Sequence:create(cc.RemoveSelf:create()))
    --     end
    -- end

    -- videoPlayer:setContentSize(cc.size(width,height))
    -- videoPlayer:setAnchorPoint(cc.p(0.5, 0.5))
    -- videoPlayer:setPosition(cc.p(width/2, height/2))
    -- videoPlayer:addEventListener(onVideoEventCallback)
    -- -- videoPlayer:setFullScreenEnabled(true)
    -- videoPlayer:setFileName(videoFullPath)
    -- videoPlayer:play()
    -- Layout:addChild(videoPlayer)
end

return MainView

