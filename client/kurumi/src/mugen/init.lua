-- @Author : fc
-- @Date   : 2022-02-04 19:52:57
-- @remark : 

local IS_TEST_MODE = _MyG == nil

local M = {}

function M.G_GetComponent(entity, componentName, componentType)
	local component = entity:getComponent(componentName)
	return tolua.cast(component, componentType or componentName)
end

function M.onMugenAudioPlay(audioName)
	audioName = audioName .. ".ogg"
	print("play:", audioName)
	if IS_TEST_MODE then
		local audio = require("framework.audio")
		audio.playEffectSync(audioName)
	else
		_MyG.AudioManager:playSound(audioName)
	end
end


if cc and cc.exports then
	for k, v in pairs(M) do
		cc.exports[k] = v
	end
else
	for k, v in pairs(M) do
		_G[k] = v
	end
end
