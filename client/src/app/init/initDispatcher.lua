local inputDispatcherKey = {}

inputDispatcherKey["CONTROL_X"] = 0
inputDispatcherKey["CONTROL_Y"] = 0
inputDispatcherKey["CONTROL_CANCEL"] = 0
inputDispatcherKey["CONTROL_ATTACK_NORMAL"] = 0
inputDispatcherKey["CONTROL_JUMP"] = 0
inputDispatcherKey["CONTROL_DOWN_CUT"] = 0
inputDispatcherKey["CONTROL_SKILL_1"] = 0
inputDispatcherKey["CONTROL_SKILL_10"] = 0

for k,v in pairs(inputDispatcherKey) do
	inputDispatcherKey[k] = string.lower(k)
end

_MyG.INPUT_KEY = inputDispatcherKey


_MyG.PlayerDispatcher = require("app.common.dispatcher"):new()
_MyG.InputDispatcher = require("app.common.dispatcher"):new()
_MyG.PlayerController = require("app.common.PlayerController"):new()

