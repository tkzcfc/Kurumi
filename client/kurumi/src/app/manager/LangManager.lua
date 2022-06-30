-- @Author: fangcheng
-- @Date:   2021-05-16 13:44:49
-- @remark: 多语言管理


local LangManager = class("LangManager", import(".BaseManager"))

local LANGUAGE = {}
LANGUAGE.EN = "en"
LANGUAGE.CN = "cn"

local LANG_NAME = {}
LANG_NAME[LANGUAGE.CN] = "简体中文"
LANG_NAME[LANGUAGE.EN] = "English"

LangManager.LANGUAGE = LANGUAGE
LangManager.LANG_NAME = LANG_NAME

local Lang = nil
local curLanguage

function LangManager:override_onInit()
    LangManager.super.override_onInit(self)

    self:initWithTextRoot("config.Lang", LANGUAGE.CH)
end

function LangManager:initWithTextRoot(langFile, defaultLang)
    Lang = require(langFile)

    local langValue = _MyG.SysSetManager:getStorage().strLang
    if langValue == nil or langValue == "" then
        if defaultLang then
            langValue = defaultLang
        else
            local lang_code = cc.Application:getInstance():getCurrentLanguage()
            langValue = LangManager.getLangByCode(lang_code)
        end
    end
    
    self:setLang(langValue)
end

function LangManager:getLang()
    return self.language
end

function LangManager:setLang(lang)
    self.language = lang
    curLanguage = lang

    _MyG.SysSetManager:getStorage().strLang = lang
end

function LangManager.getLangByCode(lang_code)
    local lang_str = "cn"
    -- if lang_code == cc.LANGUAGE_ENGLISH then
    --     lang_str = "en"
    -- elseif lang_code == cc.LANGUAGE_CHINESE then
    --     lang_str = "cn"
    -- end
    return lang_str
end

function LangManager:getLanguageName()
    return LANG_NAME[self:getLang()]
end

function LangManager:getLangByName(languageName)
    for k, v in pairs(LANG_NAME) do
        if v == languageName then
            return k
        end
    end
    error(languageName .. "不存在")
end

function LangManager:setLangByName(languageName)
    for k, v in pairs(LANG_NAME) do
        if v == languageName then
            self:setLang(k)
            return
        end
    end
    error(languageName .. "不存在")
end

------------------------------------------------------------------------------------------------
local returnValue = nil
if G_MACROS.DEBUG then
    global.STR = function(key)
        assert(curLanguage)
        returnValue = Lang.getItem(key, curLanguage)
        if returnValue == nil then
            print(string.format("警告：语言%q未定义", curLanguage))
            return tostring(key)
        end
        return returnValue
    end
else
    global.STR = function(key)
        returnValue = Lang.getItem(key, curLanguage)
        if returnValue == nil then
            return tostring(key)
        end
        return returnValue
    end
end

return LangManager
