require("app.init.initConfig")

----------------------------------------------------------------------------------
require("cocos.cocos2d.json")

require("app.config.SceneResourceLoadConfig")

_MyG.ScenesManager = require("app.common.GameSceneSwither")

_MyG.Net = require("app.models.net.gameNet"):new()

_MyG.Loading = require("app.ui.LoadingUI"):new()
_MyG.Loading:retain()

_MyG.MessageBox = require("app.ui.MessageBoxUI"):new()
_MyG.MessageBox:retain()

_MyG.GlobalMsgRecipient = require("app.common.GlobalMsgRecipient"):new()

_MyG.GlobalDataCache = require("app.common.GlobalDataCache"):new()

require("app.init.initDispatcher")
require("app.init.initFunc")


