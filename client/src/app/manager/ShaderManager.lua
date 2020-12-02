-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: shader管理

local ShaderManager = class("ShaderManager", import(".BaseManager"))

ShaderManager.EKey = 
{
	default = 1,
	brightness_2_5 = 2,
	brightness_2 = 3,
	brightness_1_5 = 4,
	brightness_0_5 = 5,
}

local fileUtiles = cc.FileUtils:getInstance()

function ShaderManager:override_onInit()
	ShaderManager.super.override_onInit(self)
	self.shaderAll = {}
end

function ShaderManager:getShader(key)
    if self.shaderAll[key] == nil then
        self:loadShader(key)
    end
    return self.shaderAll[key]
end

function ShaderManager:getProgramState(key)
    local glprogram = self:getShader(key)
    if glprogram == nil then
    	logE("创建shader失败", key)
    	return
    end
    return cc.GLProgramState:getOrCreateWithGLProgram(glprogram)
end

function ShaderManager:loadShader(key)
    local ret = nil

    if key == ShaderManager.EKey.default then --默认
		local vertSource = fileUtiles:getStringFromFile("shader/ccShader_PositionTextureColor_noMVP.vert")
		local fragSource = fileUtiles:getStringFromFile("shader/default.frag")
		ret = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
	elseif key == ShaderManager.EKey.brightness_2_5 then --亮度(2.5)
		local vertSource = fileUtiles:getStringFromFile("shader/ccShader_PositionTextureColor_noMVP.vert")
		local fragSource = fileUtiles:getStringFromFile("shader/wd_brightness_2_5.frag")
		ret = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
	elseif key == ShaderManager.EKey.brightness_2 then --亮度(2)
		local vertSource = fileUtiles:getStringFromFile("shader/ccShader_PositionTextureColor_noMVP.vert")
		local fragSource = fileUtiles:getStringFromFile("shader/wd_brightness_2.frag")
		ret = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
	elseif key == ShaderManager.EKey.brightness_1_5 then --亮度(1.5)
		local vertSource = fileUtiles:getStringFromFile("shader/ccShader_PositionTextureColor_noMVP.vert")
		local fragSource = fileUtiles:getStringFromFile("shader/wd_brightness_1_5.frag")
		ret = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
	elseif key == ShaderManager.EKey.brightness_0_5 then --亮度(0.5)--变暗
		local vertSource = fileUtiles:getStringFromFile("shader/ccShader_PositionTextureColor_noMVP.vert")
		local fragSource = fileUtiles:getStringFromFile("shader/wd_brightness_0_5.frag")
		ret = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
	end

	self.shaderAll[key] = ret
end

return ShaderManager