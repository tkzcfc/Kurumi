--
-- <DIV> 标签解析
--

local function div_createlabel(self, word, fontname, fontsize, fontcolor)
	if word == "" then return
	end
	local label = cc.Label:createWithTTF(word, fontname, fontsize)
	if not label then 
		self:printf("<div> - create label failed")
		return
	end
	label:setColor(fontcolor)
	return label
end

local function div_parseshadow(self, shadow)
	if not shadow then return
	end
	-- 标准的格式：shadow=10,10,10,#ff0099
	-- (offset_x, offset_y, blur_radius, shadow_color)
	local params = self:split(shadow, ",")
	if #params~=4 then
		self:printf("parser <div> property shadow error")
		return nil
	end
	local offset_x = tonumber(params[1]) or 0
	local offset_y = tonumber(params[2]) or 0
	params.offset = cc.size(offset_x, offset_y)
	params.blurradius = tonumber(params[3]) or 0
	params.color = self:convertColor(params[4]) or cc.c4b(255,255,255,255)
	return params
end

local function div_parseoutline(self, outline)
	if not outline then return
	end
	-- 标准格式: outline=1,#ff0099
	-- (outline_size, outline_color)
	local params = self:split(outline, ",")
	if #params~=2 then
		self:printf("parser <div> property outline error")
		return nil
	end
	params.size = tonumber(params[1]) or 0
	params.color = self:convertColor(params[2]) or cc.c4b(255,255,255,255)
	return params
end 

local function div_parseunderline(self, underline)
	if not underline then return
	end
	-- 标准格式: underline = 2, #ff0099  
	-- (underline_size, underline_color)
	local params = self:split(underline, ",")
	if #params~=2 then
		self:printf("parser <div> property underline error")
		return nil
	end
	params.size = tonumber(params[1]) or 2
	params.color = self:convertColor(params[2]) or cc.c4b(255,255,255,255)
	for k, v in pairs(params.color) do
		params.color[k] = params.color[k] / 255
	end
	return params
end 

local function div_parseglow(self, glow)
	if not glow then return
	end
	-- 标准格式: glow=#ff0099	
	-- (glow_color)
	local color = self:convertColor(glow) or cc.c4b(255,255,255,255)
	return {["color"]=color}
end

--
-- <div> Parser
--
-- return function (self, params, default)
-- 	-- 将字符串拆分成一个个字符
-- 	local content = params.content
-- 	if content then
-- 		params.charlist = self:stringToChars(content)
-- 	end
-- 	-- 必须返回表，表中包含要显示的精灵
-- 	local charlist = params.charlist
-- 	local labellist = {}
-- 	if not charlist then return labellist
-- 	end

-- 	-- 获得要设置的属性
-- 	local fontname = params.fontname or default.fontName
-- 	local fontsize = params.fontsize or default.fontSize
-- 	local fontcolor = self:convertColor(params.fontcolor) or default.fontColor
-- 	-- label effect
-- 	local shadow = params.shadow
-- 	local shadow_params = div_parseshadow(self, shadow)
-- 	local outline = params.outline
-- 	local outline_params = div_parseoutline(self, outline)
-- 	local glow = params.glow
-- 	local glow_params = div_parseglow(self, glow)

-- 	for index, char in pairs(charlist) do
-- 		local label = div_createlabel(self, char, fontname, fontsize, fontcolor)
-- 		if label then
-- 			if shadow then 
-- 				label:enableShadow(shadow_params.color, shadow_params.offset, shadow_params.blurradius)
-- 			end
-- 			if outline then
-- 				label:enableOutline(outline_params.color, outline_params.size)
-- 			end
-- 			if glow then
-- 				label:enableGlow(glow_params.color)
-- 			end
-- 			table.insert(labellist, label)
-- 		end
-- 	end
-- 	return labellist
-- end

local function handleTextRenderer(self, params)
	local contents = self:split(params.content, "\n")
	local contentNum = #contents
	local labellist = {}


	if self._isAutoAdjustWidth then
		for k, content in ipairs(contents) do
			local label = div_createlabel(self, content, params.fontname, params.fontsize, params.fontcolor)
			if label then
				if params.shadow then 
					label:enableShadow(params.shadow_params.color, params.shadow_params.offset, params.shadow_params.blurradius)
				end
				if params.outline then
					label:enableOutline(params.outline_params.color, params.outline_params.size)
				end
				if params.glow then
					label:enableGlow(params.glow_params.color)
				end

				table.insert(labellist, label)
				if params.underline then
					local draw = cc.DrawNode:create(params.underline_params.size)
		        	label:addChild(draw, 1)
		        	--draw a line
		        	draw:drawLine(cc.p(0,0), cc.p(label:getBoundingBox().width, 0), params.underline_params.color)
				end

				if contentNum ~= k then
					label.autoBreakLine = true
				end
			end
		end

		return labellist
	end

	local curHandler 
	curHandler = function (self, params)
		local content = params.curContent
		local label = div_createlabel(self, content, params.fontname, params.fontsize, params.fontcolor)
		if label then
			if params.shadow then 
				label:enableShadow(params.shadow_params.color, params.shadow_params.offset, params.shadow_params.blurradius)
			end
			if params.outline then
				label:enableOutline(params.outline_params.color, params.outline_params.size)
			end
			if params.glow then
				label:enableGlow(params.glow_params.color)
			end

			local addLabel = function ()
				table.insert(labellist, label)
				if params.underline then
					local draw = cc.DrawNode:create(params.underline_params.size)
		        	label:addChild(draw, 1)
		        	--draw a line
		        	draw:drawLine(cc.p(0,0), cc.p(label:getBoundingBox().width, 0), params.underline_params.color)
				end

				if contentNum ~= params.curIndex then
					label.autoBreakLine = true
				end
			end

			--print("curHandler == ", content, label, params.curIndex)
			local contetSize = label:getBoundingBox()
			local originalLeftSpaceWidth = self._leftSpaceWidth
			local leftSpaceWidth = self._leftSpaceWidth - contetSize.width
			self._leftSpaceWidth = leftSpaceWidth
			if leftSpaceWidth < 0 then 
				local overstepPercent = (-leftSpaceWidth) / contetSize.width
		        local curText = content 
		        local stringLength = self:getCharacterCountInUTF8String(curText)
		        --local leftLength = math.floor(stringLength * (1 - overstepPercent))	
		        --print("leftLength", leftLength, stringLength ,overstepPercent, stringLength * (1 - overstepPercent))
		        -- The adjustment of the new line position	
		        local trueleftLength = stringLength * (1 - overstepPercent)	
		        local leftLength = math.floor(trueleftLength)	
		     	if leftLength < 1 then
		     		leftLength = 1
		     	end

		        local leftStr = self:getSubStringOfUTF8String(curText, 1, leftLength)	      
		        label:setString(leftStr)
		        local leftWidth = label:getBoundingBox().width

		        --print("leftStr", leftStr, leftLength, leftWidth, originalLeftSpaceWidth)
		        if originalLeftSpaceWidth < leftWidth then
		            -- Have protruding
		            while true do
		                leftLength = leftLength - 1
		                --print("leftLength", leftLength , 1, originalLeftSpaceWidth, leftWidth)
		                leftStr = self:getSubStringOfUTF8String(curText, 1, leftLength)
		                label:setString(leftStr)
		                leftWidth = label:getBoundingBox().width
		                if leftWidth <= originalLeftSpaceWidth then
		                    break
		                elseif leftLength <= 0 then
		                    break
		                end
		            end
		        elseif leftWidth < originalLeftSpaceWidth then
		            -- A wide margin
		            while true do
		                leftLength = leftLength + 1
		                --print("leftLength", leftLength , 2)
		                leftStr = self:getSubStringOfUTF8String(curText, 1, leftLength)
		                label:setString(leftStr)
		                leftWidth = label:getBoundingBox().width
		                if originalLeftSpaceWidth < leftWidth then
		                    leftLength = leftLength - 1
		                   -- print("leftLength", leftLength , 3)
		                    break          
		                elseif stringLength <= leftLength then
		                    break
		                end
		            end
		        end
		        --print("0 == leftLength ", leftLength)
		        --The minimum cut length is 1, otherwise will cause the infinite loop.
		        --if 0 == leftLength then leftLength = 1 end
		        local leftWords, curIndex
		        local cutWords
		        if leftLength < 1 then
		        	leftStr = self:getSubStringOfUTF8String(curText, 1, 1)
		            label:setString(leftStr)
		            leftWidth = label:getBoundingBox().width
		            if leftWidth > self._maxWidth then
			        	leftWords, curIndex = self:getSubStringOfUTF8String(curText, 1, 1)
			        	cutWords = self:getSubStringOfUTF8String(curText, curIndex, stringLength - 1)
			        else
			        	leftWords, curIndex = ""
			        	cutWords = curText
			        end
		        else
			        leftWords, curIndex = self:getSubStringOfUTF8String(curText, 1, leftLength)
			        --print("leftLength", leftLength , stringLength)
			        cutWords = self:getSubStringOfUTF8String(curText, curIndex, stringLength - leftLength)
			    end
				--print("leftWords, cutWords", leftWords, cutWords, leftLength)
			    --if leftLength > 0 then
	            local leftRenderer = nil       
	            --leftRenderer = div_createlabel(self, self:getSubStringOfUTF8String(leftWords, 1, leftLength), params.fontname, params.fontsize, params.fontcolor)
	            leftRenderer = div_createlabel(self, leftWords, params.fontname, params.fontsize, params.fontcolor)
				if leftRenderer then
					if params.shadow then 
						leftRenderer:enableShadow(params.shadow_params.color, params.shadow_params.offset, params.shadow_params.blurradius)
					end
					if params.outline then
						leftRenderer:enableOutline(params.outline_params.color, params.outline_params.size)
					end
					if params.glow then
						leftRenderer:enableGlow(params.glow_params.color)
					end
				end

	            if leftRenderer then
	                table.insert(labellist, leftRenderer)
	                if params.underline then
						local draw = cc.DrawNode:create(params.underline_params.size)
			        	leftRenderer:addChild(draw, 1)
			        	--draw a line
			        	draw:drawLine(cc.p(0,0), cc.p(leftRenderer:getBoundingBox().width, 0), params.underline_params.color)
					
			        	if contentNum ~= params.curIndex then
							leftRenderer.autoBreakLine = true
						end
					end
	            end
		        --end

		        self:addNewLine()
		        --handleTextRenderer(self, params)
		        params.curContent = cutWords
		        curHandler(self, params)
			else
				addLabel()
			end

			return label
		end
	end

	for k, content in ipairs(contents) do
		params.curContent = content
		params.curIndex = k
		if k > 1 then
		    self:addNewLine()
		end
		curHandler(self, params)
	end

	 -- for k, v in pairs(labellist) do
	 -- 	print("labellist == ", v.autoBreakLine)
	 -- end

	return labellist
end

return function (self, params, default)
	local curParams = {
		-- 获得要设置的属性
		fontname = params.fontname or default.fontName,
		fontsize = params.fontsize or default.fontSize,
		fontcolor = self:convertColor(params.fontcolor) or default.fontColor,
		--label effect
		shadow = params.shadow,
		shadow_params = div_parseshadow(self, params.shadow),
		outline = params.outline,
		outline_params = div_parseoutline(self, params.outline),
		underline = params.underline,
		underline_params = div_parseunderline(self, params.underline),
		glow = params.glow,
		glow_params = div_parseglow(self, params.glow),

	 	content = params.content or "",
	}

	return handleTextRenderer(self, curParams)
end