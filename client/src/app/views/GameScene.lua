local msgViewBase = require("app.common.msgViewBase")
local GameScene = class("GameScene", msgViewBase)

function GameScene:onCreate(args)
	print("args.mapID = ", args.mapID)
    GameScene.super.onCreate(self, args)


    local mapConfig = require("app.config.MapConfig")

    local word = GameWord:create()
    mapConfig:loadMap(word, args.mapID)
	self:addChild(word)

    self.word = word

    local uiPage = _MyG.loadStudioFile("HomeSceneUI", self)
    self:addChild(uiPage.root)



	local hero = require("app.actor.role.Hero_dao"):create()
    -- print("hero = ", tostring(hero))
    self.word:addActor(hero)
    self.word:setLocalPlayer(hero)

    _MyG.PlayerController:setPlayer(hero)

    self.hero = hero
    hero:changeRole("hero_xiuluo_dao")

    local controlUI = require("app.ui.ControlUI"):create()
    self.word:addChild(controlUI, 1)

    self.leishenCount = 0
    self.shengboCount = 2
    self.curShengbo = 0
    self.curLeiShen = 0

    local scheduler=cc.Director:getInstance():getScheduler()
    self.scriptEntryID = scheduler:scheduleScriptFunc(function(time) self:createMonster(time) end,1 / 20.0,false)
end

function GameScene:onExit()
    GameScene.super.onExit(self)
    self:stopScheduler()
end

function GameScene:onKeyBackReleased()
	_MyG.MessageBox:showBox("返回城镇？", function() 
		_MyG.GameSceneSwither:enterScene(_MyG.SCENE_ID_MAIN)
	end, function() end)
end

function GameScene:createMonster()

    if self.curShengbo < self.shengboCount then
        self.curShengbo = self.curShengbo + 1
        local MS = require("app.actor.monster.Monster_Shengbo"):create()
        MS:setActorPosition(200 * self.curShengbo, 0)
        self.word:addActor(MS)
        return
    end

    if self.curLeiShen < self.leishenCount then
        self.curLeiShen = self.curLeiShen + 1
        local MS = require("app.actor.monster.Monster_LeiShen"):create()
        MS:setActorPosition(500 * self.curLeiShen, 0)
        self.word:addActor(MS)
        return
    end

    if self.curShengbo >= self.shengboCount and 
        self.curLeiShen >= self.leishenCount then
        self:stopScheduler()
    end
end

function GameScene:stopScheduler()
    if self.scriptEntryID ~= nil then
        local scheduler=cc.Director:getInstance():getScheduler()
        scheduler:unscheduleScriptEntry(self.scriptEntryID)
    end
    self.scriptEntryID = nil
end

return GameScene

