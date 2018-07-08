local msgViewBase = require("app.common.msgViewBase")
local GameMain = class("GameMain", msgViewBase)

local RoleConfig = require("app.config.RoleConfig")

local loadAllRole = false
local playerRole = "hero_shizhuak_dao"
local otherRole = {"hero_shizshuishoufu_dao"}--, "hero_shizmaonv_dao", "hero_shizhuak_dao"}

function GameMain:onCreate()

    self.super.onCreate(self)

    local mapConfig = require("app.config.MapConfig")

    local word = GameWord:create()
    mapConfig:loadMap(word, "map3")
	self:addChild(word)

    self.word = word

    local uiPage = _MyG.loadStudioFile("HomeSceneUI", self)
    self:addChild(uiPage.root)

    

    local ss = cc.SpriteFrameCache:getInstance():getSpriteFrameByName("rect_attack_a.png")
    if ss == nil then
        print("rect attack png is nil")
    else
        print("rect attack png is not nil")
    end
    cc.SpriteFrameCache:getInstance():addSpriteFrames("rect_collide.plist")
    print(cc.TextureCache:getInstance():getDescription())
    print(cc.TextureCache:getInstance():getCachedTextureInfo())
    print("begin-------------------------------------------------\n\n\n\n")


    self:onClickLoad(nil)
end

function GameMain:loadFinish()
    local hero = require("app.actor.role.Hero_dao"):create()
    self.word:addActor(hero)
    self.word:setLocalPlayer(hero)

    _MyG.PlayerController:setPlayer(hero)

    self.hero = hero
    hero:changeRole(playerRole)


    local winSize = cc.Director:getInstance():getVisibleSize()

    local controlUI = require("app.ui.ControlUI"):create()
    self.word:addChild(controlUI, 1)

    local ss = cc.SpriteFrameCache:getInstance():getSpriteFrameByName("rect_attack_a.png")
    if ss == nil then
        print("rect attack png is nil")
    else
        print("rect attack png is not nil")
    end

    -- for i = 1, 1 do
    -- local MS = require("app.actor.monster.Monster_Shengbo"):create()
    -- MS:setActorPosition(200, 0)
    -- self.word:addActor(MS)
    -- end

    for i = 1, 1 do
    local MS = require("app.actor.monster.Monster_LeiShen"):create()
    MS:setActorPosition(200, 0)
    self.word:addActor(MS)
    end
end

return GameMain