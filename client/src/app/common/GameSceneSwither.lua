local GameSceneSwither = class("GameSceneSwither")

function GameSceneSwither:ctor()
	self.preSceneID = nil
	self.curSceneID = nil
end

function GameSceneSwither:enterScene(sceneID, transition, time, more, args)

	if _MyG.SCENE_MAP[sceneID] == nil then
		print("[EEROR]:不存在场景ID", sceneID)
		return
	end

	if _MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc == nil then
		self:runScene(sceneID, transition, time, more)
	else
		self.preSceneID = self.curSceneID
		self.curSceneID = SCENE_ID_LOAD_RESOURCE

		local loadResourceScene = self:runScene(SCENE_ID_LOAD_RESOURCE, transition, time, more)
		loadResourceScene:setNextSceneID(sceneID, transition, time, more, args)
	end
end

function GameSceneSwither:runScene(sceneID, transition, time, more)

	self.preSceneID = self.curSceneID
	self.curSceneID = sceneID

	if _MyG.SCENE_MAP[sceneID] == nil then
		print("[EEROR]:不存在场景ID", sceneID)
		return
	end

	_MyG.APP:enterScene(_MyG.SCENE_MAP[sceneID], transition, time, more)
end

function GameSceneSwither:getCurSceneID()
	return self.curSceneID
end

function GameSceneSwither:getPreSceneID()
	return self.preSceneID
end

return GameSceneSwither