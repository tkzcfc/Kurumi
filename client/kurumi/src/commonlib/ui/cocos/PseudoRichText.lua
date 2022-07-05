-- @Author : fc
-- @Date   : 2021-12-02 10:13:10
-- @remark : 伪富文本实现
-- 使用格式 <font color=#FF0000>我是红色文本</font>  <font>我是默认颜色文本</font> <font color=#0000FF>我是蓝色文本</font>

local FONT_MATCH = {
    ["all"] = "<%s-font.->.-</%s-font%s->",
    ["color"] = "color%s-=%s-#%w%w%w%w%w%w%s-",
    ["content"] = "<%s-font.->(.*)</%s-font%s->",
}

-- @brief 默认颜色
local defaultRichColor = cc.c4b(255, 255, 255, 255)
-- @brief 白色
local whiteColor = cc.c4b(255, 255, 255, 255)

-- @brief 十六进制转颜色
-- 0xffffff -> cc.c3b(255, 255, 255)
local function HexToRgb(xstr)
    if #xstr >= 6 then
        local R = tonumber(string.sub(xstr, -6, -5), 16) 
        local G = tonumber(string.sub(xstr, -4, -3), 16)
        local B = tonumber(string.sub(xstr, -2, -1), 16)
        return cc.c3b(R, G, B)
    else
        return defaultRichColor
    end
end



local Parser = {}

-- @brief 设置默认颜色
function Parser:setdefaultRichColor(color)
    defaultRichColor = color
end

-- @brief 开始解析
function Parser:parse(text)
    local labels = {}
    local items = {}

    local st = 0
    local en = 0

    while true do
        st, en = string.find(text, FONT_MATCH["all"], st + 1)
        if not st then
            break
        end
        local label = string.sub(text, st, en)

        table.insert(labels, label)
        st = en
    end

    --解析文本标签
    for i,v in ipairs(labels) do
        table.insert(items, self:parseText(v))
    end

    return items
end

-- @brief 解析文本标签
function Parser:parseText(text)
    local item = {}

    -- 文本内容解析
    item.str = string.match(text, FONT_MATCH["content"])
    
    -- 颜色解析
    local matchColor = string.match(text, FONT_MATCH["color"])
    if matchColor then
        item.color = HexToRgb(matchColor)
    end
    if item.color == nil then item.color = defaultRichColor end

    return item
end









local PseudoRichText = {}

-- @brief 设置富文本内容
-- @param label cc.Label
-- @param text 富文本内容
-- @param color 默认文本颜色
function PseudoRichText:setString(label, text, color)
    -- 兼容普通文本
    if not string.find(text, "^<%s-font") then
        label:setString(text)
        return
    end
    label:setTextColor(whiteColor)


    local oldColor = defaultRichColor
    if color then
        Parser:setdefaultRichColor(color)
    end

    -- 富文本解析
    local items = Parser:parse(text)

    -- 获取全部显示内容
    local str = ""
    for k, v in pairs(items) do
        str = str .. v.str
    end

    -- 设置内容
    label:setString(str)

    -- 设置颜色
    local index = 0
    for k, v in pairs(items) do
        local len = string.utf8len(v.str)
        for i = 1, len do
            local letter = label:getLetter(index)
            if letter then
                letter:setColor(v.color)
            end
            index = index + 1
        end
    end

    -- 还原默认颜色
    Parser:setdefaultRichColor(oldColor)
end

return PseudoRichText