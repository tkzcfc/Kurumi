-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 初始化manager文件下的所有管理器

_MyG.arrManagers        = {}

_MyG.SysSetManager      = require("app.manager.SysSetManager").new()
_MyG.InputManager       = require("app.manager.InputManager").new()
_MyG.HttpManager        = require("app.manager.HttpManager").new()
_MyG.NetManager         = require("app.manager.NetManager").new()
_MyG.AudioManager       = require("app.manager.AudioManager").new()
_MyG.LangManager        = require("app.manager.LangManager").new()
_MyG.ShaderManager      = require("app.manager.ShaderManager").new()
_MyG.PlayerManager      = require("app.manager.PlayerManager").new()
_MyG.GlobalManager      = require("app.manager.GlobalManager").new()
_MyG.ScenesManager      = require("app.manager.ScenesManager").new()
_MyG.NotifiNodeManager  = require("app.manager.NotifiNodeManager").new()
_MyG.KeyBackManager     = require("app.manager.KeyBackManager").new()
_MyG.LoginManager       = require("app.manager.LoginManager").new()

G_SysEventEmitter:on("event_appWillExit", function()
    for k,v in pairs(_MyG.arrManagers) do
        v:destroy()
    end
    _MyG.arrManagers = {}
end, _MyG)

G_SysEventEmitter:on("event_restartApp", function()
    for k,v in pairs(_MyG.arrManagers) do
        v:destroy()
    end
    _MyG.arrManagers = {}
end, _MyG)
