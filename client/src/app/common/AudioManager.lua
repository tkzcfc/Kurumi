
-- 全局音频管理器

local AudioManager = class("AudioManager")

function AudioManager:ctor()
    self._backMusicID = nil -- 背景音乐id

    self._backMusicOn = nil -- 音乐开关
    self._soundOn = nil -- 音效开关

    self._soundIds = nil -- 音效id集合

    self._backMusicVolume = nil--背景音量
    self._effectVolume = nil--音效音量

    self._background_music_name = nil--背景音乐

    self:init()
end

function AudioManager:init()
    ccexp.AudioEngine:lazyInit()

    self._backMusicOn = cc.UserDefault:getInstance():getBoolForKey("IsBackMusicOn", true)
    self._soundOn = cc.UserDefault:getInstance():getBoolForKey("IsSoundOn", true)

    self._backMusicVolume = cc.UserDefault:getInstance():getFloatForKey("backMusicVolume", 1.0)
    self._effectVolume = cc.UserDefault:getInstance():getFloatForKey("effectVolume", 1.0)

    self._soundIds = {}

    return true
end

function AudioManager:playBackMusic(file_name, loop, delay)
    if not self._backMusicOn then return end
    self:stopBackMusic()

    self._background_music_name = file_name

    loop = loop or false
    delay = delay or 0

    assert(cc.FileUtils:getInstance():isFileExist(file_name), string.format("AudioManager:找不到背景音乐配置%s的文件:%s", configName, file_name))

    if delay > 0 then
        delayCall(function ()
            self._backMusicID = ccexp.AudioEngine:play2d(file_name, loop, self._backMusicVolume)
        end, delay)
    else
        self._backMusicID = ccexp.AudioEngine:play2d(file_name, loop, self._backMusicVolume)
    end

    return true
end

function AudioManager:stopBackMusic()
    if not self._backMusicOn then return end

    if self._backMusicID then
        ccexp.AudioEngine:stop(self._backMusicID)
        self._backMusicID = nil
    end
    self._background_music_name = nil
end

function AudioManager:getBackMusicName()
    return self._background_music_name
end

function AudioManager:pauseBackMusic()
    if not self._backMusicOn then return end

    if self._backMusicID then
        ccexp.AudioEngine:pause(self._backMusicID)
    end
end

function AudioManager:resumeBackMusic()
    if not self._backMusicOn then return end

    if self._backMusicID then
        ccexp.AudioEngine:resume(self._backMusicID)
    end
end

function AudioManager:playSound(file, loop)
    loop = loop or false
    local id = ccexp.AudioEngine:play2d(file, loop, self._effectVolume)
    ccexp.AudioEngine:setFinishCallback(id, function (c1, c2)
        self._soundIds[c1] = nil
    end)
    self._soundIds[id] = file
    return
end

function AudioManager:stopSound(soundId)
    if not self._soundOn then return end

    ccexp.AudioEngine:stop(soundId)

    self._soundIds[soundId] = nil
end

function AudioManager:pauseSound(soundId)
    if not self._soundOn then return end

    ccexp.AudioEngine:pause(soundId)
end

function AudioManager:resumeSound(soundId)
    if not self._soundOn then return end

    ccexp.AudioEngine:resume(soundId)
end

function AudioManager:stopAllSounds()
    if not self._soundOn then return end

    for k, v in pairs(self._soundIds) do
        self:stopSound(k)
    end
end

function AudioManager:pauseAllSounds()
    if not self._soundOn then return end

    for k, v in pairs(self._soundIds) do
        self:pauseSound(k)
    end
end

function AudioManager:resumeAllSounds()
    if not self._soundOn then return end

    for k, v in pairs(self._soundIds) do
        self:resumeSound(k)
    end
end

function AudioManager:turnOnBackMusic(turnOn)
    self._backMusicOn = turnOn
    cc.UserDefault:getInstance():setBoolForKey("back_music_on", turnOn)
    cc.UserDefault:getInstance():flush()
end

function AudioManager:turnOnSound(turnOn)
    self._soundOn = turnOn
    cc.UserDefault:getInstance():setBoolForKey("sound_on", turnOn)
    cc.UserDefault:getInstance():flush()
end

function AudioManager:setBackgroundVolume(volume)
    if volume > 1.0 then volume = 1.0 end
    if volume < 0.0 then volume = 0.0 end

    if self._backMusicVolume == volume then return end

    self._backMusicVolume = volume

    if self._backMusicID then
        ccexp.AudioEngine:setVolume(self._backMusicID, volume)
    end
end

function AudioManager:getBackgroundVolume()
    return self._backMusicVolume
end

function AudioManager:getEffectVolume()
    return self._effectVolume
end

function AudioManager:preload(file, func)
    ccexp.AudioEngine:preload(file, func)
end

function AudioManager:uncache(file)
    ccexp.AudioEngine:uncache(file)
end

function AudioManager:setEffectVolume(volume)
    if volume > 1.0 then volume = 1.0 end
    if volume < 0.0 then volume = 0.0 end

    if self._effectVolume == volume then return end

    self._effectVolume = volume

    for k, v in pairs(self._soundIds) do
        if v ~= nil then
            ccexp.AudioEngine:setVolume(k, volume)
        end
    end
end

function AudioManager:saveVolumeToFile()
    cc.UserDefault:getInstance():setFloatForKey("backMusicVolume", self._backMusicVolume)
    cc.UserDefault:getInstance():setFloatForKey("effectVolume", self._effectVolume)
    cc.UserDefault:getInstance():flush()
end

return AudioManager
