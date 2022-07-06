-- @Author : fangcheng
-- @Date   : 2020-06-30 13:49:06
-- @remark : 实现打字机效果

local TyperLabel = {}


local kTyperActionTag = 0xffee
local emptyFunc = function() end

-- @brief 将一段文字拆分成集合
-- 		  经过测试,这个方法效率要高于使用正则表达式的方法
local function splitString(str)
	local bytes = #str
	local chars = {}
	local char

	for i = 1, bytes do
		local curByte = string.byte(str, i)
        local byteCount = 0
        if curByte>0 and curByte<=127 then
            byteCount = 1
        elseif curByte>=192 and curByte<223 then
            byteCount = 2
        elseif curByte>=224 and curByte<239 then
            byteCount = 3
        elseif curByte>=240 and curByte<=247 then
            byteCount = 4
        end
        if byteCount > 0 then  
            char = string.sub(str, i, i + byteCount - 1)  
            i = i + byteCount - 1  
            chars[#chars + 1] = char
        end
	end

	return chars
end

-- --@brief 将一段文字拆分成集合
-- local function splitString(s)
--     local tb = {}
--     --[[
--     UTF8的编码规则：
--     1. 字符的第一个字节范围： 0x00—0x7F(0-127),或者 0xC2—0xF4(194-244); UTF8 是兼容 ascii 的，所以 0~127 就和 ascii 完全一致
--     2. 0xC0, 0xC1,0xF5—0xFF(192, 193 和 245-255)不会出现在UTF8编码中
--     3. 0x80—0xBF(128-191)只会出现在第二个及随后的编码中(针对多字节编码，如汉字)
--     ]]
--     for utfChar in string.gmatch(s, "[%z\1-\127\194-\244][\128-\191]*") do
--         table.insert(tb, utfChar)
--     end
--     return tb
-- end


-- @brief 执行打字机效果,调用此函数将会给 lable 对象添加一个 showAll 函数
-- @param label 要执行打字机效果的 label 对象
-- @param interval 文字间隔时间
-- @param finishCall 完成后的回调
function TyperLabel.doTyper(label, interval, finishCall)
	interval = interval or 0.1

	local str = label:getString()
	local strlen = select(2, string.gsub(str, "[^\128-\193]", ""))

	if strlen <= 0 then
		-- 添加函数 showAll
		label.showAll = emptyFunc
		if finishCall then
			finishCall()
		end
		return
	end

	-- 获取真实的 cc.Label
	local render = label
	local cocoType = tolua.type(label)
	if cocoType == "ccui.Text" or cocoType  == "ccui.TextBMFont" then
		render = label:getVirtualRenderer()
	end

	-- 支持 getLetter 函数的,将letter放入单元集合
	local units = {}
	for i = 0, strlen - 1 do
		local letter = render:getLetter(i)
		if letter == nil then
			if i == 0 then
				break
			end
		else
			letter:setOpacity(0)
			units[#units + 1] = letter
		end
	end

	local curIdx, mode, curString, action = 1, 0, ""

	-- 不支持 getLetter 函数的使用文字分割方式
	if #units <= 0 then
		mode  = 1
		units = splitString(str)
		label:setString(curString)
	end

	-- 文字分割也失败了,正常情况下不可能失败
	if #units <= 0 then
		-- 添加函数 showAll
		label.showAll = emptyFunc
		if finishCall then
			finishCall()
		end
		return
	end

	-- timer
	action = label:schedule(function()
		if mode == 0 then
			units[curIdx]:setOpacity(255)
		else
			curString = curString .. units[curIdx]
			label:setString(curString)
		end
		curIdx = curIdx + 1
		if curIdx > #units then
			label:stopAction(action)
			if finishCall then
				finishCall()
			end
		end
	end, interval)

	action:setTag(kTyperActionTag)

	-- 添加函数 showAll
	label.showAll = function()
		local action = label:getActionByTag(kTyperActionTag)
		if action then
			label:stopAction(action)
			if mode == 0 then
				for i = curIdx, #units do
					units[i]:setOpacity(255)
				end
			else
				label:setString(str)
			end
		end
	end
end

return TyperLabel


