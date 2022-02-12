-- @Author: fangcheng
-- @Date:   2019-06-06 22:08:00
-- @remark: 音频管理器
-- @ref: http://www.cocos2d-lua.org/doc/audio/index.md

local AudioManager = class("AudioManager", import(".BaseManager"))


function AudioManager:override_onInit()
    AudioManager.super.override_onInit(self)

    self.storage = G_Class.StorageObject.new("audio.set")
    -- 音乐开关
    self.storage:setDefault("bIsOpenMusic", true)
    -- 音效开关
    self.storage:setDefault("bIsOpenEffect", true)
    --背景音量
    self.storage:setDefault("fMusicVolume", 1.0)
    --音效音量
    self.storage:setDefault("fEffectVolume", 1.0)
end

-- @brief 播放背景音乐
-- @param forceReplay 如果正在播放是否强制重新播放
function AudioManager:playBackMusic(file_name, loop, forceReplay)
    if not self.storage.bIsOpenMusic then return end

    if loop == nil then loop = true end
    assert(cc.FileUtils:getInstance():isFileExist(file_name), string.format("AudioManager:找不到背景音乐%s", file_name))

    if self.sBGMusicName == file_name then
        if not forceReplay then return end
    end
    self.sBGMusicName = file_name

    audio.loadFile(file_name, function(pn, isSuccess)
        if isSuccess then
            self:stopBackMusic()
            audio.playBGM(file_name, loop)
            audio.setBGMVolume(self.storage.fMusicVolume)
        end
    end)
end

-- @brief 停止播放背景音乐
function AudioManager:stopBackMusic()
    audio.stopBGM()
    self.sBGMusicName = nil
end

-- @brief 播放音效
function AudioManager:playSound(file, loop)
    audio.playEffectSync(file, loop)
end

-- @brief 停止所有音效
function AudioManager:stopAllSounds()
    audio.stopEffect()
end

-- @brief 停止背景音乐和所有音效
function AudioManager:stopAll()
    audio.stopAll()
end

-- @brief 暂停背景音乐和所有音效
function AudioManager:pauseAll()
    audio.pauseAll()
end

-- @brief 恢复背景音乐和所有音效
function AudioManager:resumeAll()
    audio.resumeAll()
end

-- @brief 音效资源加载
function AudioManager:preload(file, func)
    audio.loadFile(file, func)
end

-- @brief 音效资源释放
function AudioManager:uncache(file)
    audio.unloadFile:uncache(file)
end



---------------------------------------------------------------------------------------------------------------------------

-- @brief 背景音乐开关
function AudioManager:turnOnBackMusic(turnOn)
    self.storage.bIsOpenMusic = turnOn
end

-- @brief 音效开关
function AudioManager:turnOnSound(turnOn)
    self.storage.bIsOpenEffect = turnOn
end

-- @brief 背景音量设置
function AudioManager:setBackgroundVolume(volume)
    audio.setBGMVolume(volume)
    self.storage.fMusicVolume = volume
end

function AudioManager:getBackgroundVolume()
    return self.storage.fMusicVolume
end

function AudioManager:getEffectVolume()
    return self.storage.fEffectVolume
end

-- @brief 音效音量设置
function AudioManager:setEffectVolume(volume)
    audio.setEffectVolume(volume)
    self.storage.fEffectVolume = volume
end

return AudioManager
