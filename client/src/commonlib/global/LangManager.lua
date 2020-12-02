-- @Author : fangcheng
-- @Date   : 2020-04-08 20:53:45
-- @remark : 多语言管理

local LangManager = class("LangManager")

local Lang = nil

local LANGUAGE = {}
LANGUAGE.EN = "en"
LANGUAGE.CN = "cn"

local LANG_NAME = {}
LANG_NAME[LANGUAGE.CN] = "简体中文"
LANG_NAME[LANGUAGE.EN] = "English"

LangManager.LANGUAGE = LANGUAGE
LangManager.LANG_NAME = LANG_NAME

local curLanguage

function LangManager:ctor()
end

function LangManager:initWithTextRoot(langFile, defaultLang)
	Lang = require(langFile)
	self.initTag = true
	self.firstStartTag = true

	local langValue = cc.UserDefault:getInstance():getStringForKey("lang")
	if langValue == nil or #langValue == 0 then
		if defaultLang then
			langValue = defaultLang
		else
			local lang_code = cc.Application:getInstance():getCurrentLanguage()
			langValue = LangManager.getLangByCode(lang_code)
		end
	else
		self.firstStartTag = false
	end
	
	self:setLang(langValue)
end

function LangManager:getLang()
	return self.language
end

function LangManager:setLang(lang)
	assert(self.initTag)
	
	self.language = lang
	curLanguage = lang

	cc.UserDefault:getInstance():setStringForKey("lang", lang)
end

function LangManager:isFirstStart()
	return self.firstStartTag
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
	return self.LANG_NAME[self.language]
end

function LangManager:getLangByName(languageName)
	for k, v in pairs(self.LANG_NAME) do
		if v == languageName then
			return k
		end
	end
	error(languageName .. "不存在")
end

function LangManager:setLangByName(languageName)
	for k, v in pairs(self.LANG_NAME) do
		if v == languageName then
			self:setLang(k)
			return
		end
	end
	error(languageName .. "不存在")
end

------------------------------------------------------------------------------------------------
local returnValue = nil
if G_MAC.DEBUG then
	cc.exports.STR = function(key)
		assert(curLanguage)
		returnValue = Lang.getItem(key, curLanguage)
		if returnValue == nil then
			print(string.format("警告：语言%q未定义", curLanguage))
			return tostring(key)
		end
		return returnValue
	end
else
	cc.exports.STR = function(key)
		returnValue = Lang.getItem(key, curLanguage)
		if returnValue == nil then
			return tostring(key)
		end
		return returnValue
	end
end

return LangManager
