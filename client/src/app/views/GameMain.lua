local GameMain = class("GameMain", cc.load("mvc").ViewBase)

local net = require("app.models.net.gameNet"):new()


function GameMain:onCreate()

	local word = GameWord:create()
    word:loadMapFile("map/map3/m.json", "di1ceng")
    word:setMinPosY(100)
	self:addChild(word)

    self.word = word

    local uiPage = _MyG.loadStudioFile("HomeSceneUI", self)
    self:addChild(uiPage.root)

    -- local scheduler = cc.Director:getInstance():getScheduler()  
    -- local schedulerID = nil  
    -- schedulerID = scheduler:scheduleScriptFunc(function(d)  
    --     self:updateLogin(d)
    -- end,0,false)    

    self:onClickLoad(nil)
end

function GameMain:loadFinish()
    local hero = require("app.actor.role.Hero_dao"):create()
    self.word:addActor(hero)
    self.word:setPlayer(hero)

    _MyG.PlayerController:setPlayer(hero)

    self.hero = hero


    local winSize = cc.Director:getInstance():getVisibleSize()

    local controlUI = require("app.ui.ControlUI"):create()
    self.word:addChild(controlUI, 1)


    hero = require("app.actor.role.Hero_dao"):create()
    hero:setActorPosition(400.0, 0)
    hero:setActorType(AT_MONSTER)
    self.word:addActor(hero)
end

function GameMain:onClickLoad(sender)

    _MyG.Loading:showLoading(nil, self)

    print(cc.TextureCache:getInstance():getDescription())

    if self.isLoad then
        return
    end
    self.isLoad = true
    self.printUpdate = true

    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync("role/baiji/hero_lanse_dao.ExportJson", function(jindu)
        print(jindu)
        --print(cc.TextureCache:getInstance():getDescription())
        -- print(cc.TextureCache:getInstance():getCachedTextureInfo())

        if jindu >= 1.0 and self.printUpdate then
            _MyG.Loading:hideLoding()
            self.printUpdate = false
            self:loadFinish()
            --print(cc.TextureCache:getInstance():getDescription())
            -- print(cc.TextureCache:getInstance():getCachedTextureInfo())
        end
    end)
end

function GameMain:updateLogin(delay)
   if self.printUpdate then
        print(delay)
   end 
end

return GameMain