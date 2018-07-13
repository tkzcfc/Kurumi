local GameSceneSwither = class("GameSceneSwither")

function GameSceneSwither:ctor()
	self.preSceneID = nil
	self.curSceneID = nil
end

function GameSceneSwither:enterScene(sceneID, transition, time, more, args)

	if _MyG.SCENE_MAP[sceneID] == nil then
		print("[EEROR]:<1>不存在场景ID", sceneID)
		return
	end

	local function doResourceScene()
		self.preSceneID = self.curSceneID
		self.curSceneID = SCENE_ID_LOAD_RESOURCE
	
		local loadResourceScene = self:runScene(_MyG.SCENE_ID_LOAD_RESOURCE, transition, time, more)
		loadResourceScene:setNextSceneInfo(sceneID, transition, time, more, args)
	end


	if _MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc == nil then
	    if self.curSceneID ~= nil and _MyG.SCENE_MAP[self.curSceneID] ~= nil then
	    	if _MyG.SceneResourceLoadConfig[self.curSceneID].ReleaseResourceFunc then
	    		doResourceScene()
	    	else
	    		self:runScene(sceneID, transition, time, more, args)
	    	end
	    else
			self:runScene(sceneID, transition, time, more, args)
	    end
	else
		doResourceScene()
	end
end

function GameSceneSwither:runScene(sceneID, transition, time, more, args)

	if sceneID ~= _MyG.SCENE_ID_LOAD_RESOURCE then
		self.preSceneID = self.curSceneID
		self.curSceneID = sceneID
	end

	if _MyG.SCENE_MAP[sceneID] == nil then
		print("[EEROR]:<2>不存在场景ID", sceneID)
		return
	end

	return _MyG.APP:enterScene(_MyG.SCENE_MAP[sceneID], transition, time, more, args)
end

function GameSceneSwither:getCurSceneID()
	return self.curSceneID
end

function GameSceneSwither:getPreSceneID()
	return self.preSceneID
end

return GameSceneSwither