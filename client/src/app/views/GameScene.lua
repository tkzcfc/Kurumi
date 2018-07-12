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
    self.word:addActor(hero)
    self.word:setLocalPlayer(hero)

    _MyG.PlayerController:setPlayer(hero)

    self.hero = hero
    hero:changeRole("hero_xiuluo_dao")

    local controlUI = require("app.ui.ControlUI"):create()
    self.word:addChild(controlUI, 1)

    self:initKeyEvent()
end

function GameScene:initKeyEvent()
		 --键盘事件  
    local function onKeyPressed(keyCode, event)
    	if keyCode == 6 then
			_MyG.MessageBox:showBox("返回城镇？", function() 
				_MyG.GameSceneSwither:enterScene(_MyG.SCENE_ID_MAIN)
			end, function() end)
		end
    end
  
    local listener = cc.EventListenerKeyboard:create()  
    listener:registerScriptHandler(onKeyPressed, cc.Handler.EVENT_KEYBOARD_PRESSED)  
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self) 
end

return GameScene

