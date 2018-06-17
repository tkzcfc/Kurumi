local MapConfig = {}

MapConfig["map1"] = 
{
    filepath = "map/map1/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "4ceng",
    minPosY = 95,
}

MapConfig["map2"] = 
{
    filepath = "map/map2/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 90,
}

MapConfig["map3"] = 
{
    filepath = "map/map3/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 100,
}

MapConfig["map4"] = 
{
    filepath = "map/map4/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "5ceng",
    minPosY = 55,
}

MapConfig["map5"] = 
{
    filepath = "map/map5/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 100,
}

MapConfig["map6"] = 
{
    filepath = "map/map6/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 55,
}

MapConfig["map7"] = 
{
    filepath = "map/map7/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 80,
}

MapConfig["map8"] = 
{
    filepath = "map/map8/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 70,
}

MapConfig["map9"] = 
{
    filepath = "map/map9/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 105,
}

MapConfig["map10"] = 
{
    filepath = "map/map10/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "",
    minPosY = 70,
}

MapConfig["map11"] = 
{
    filepath = "map/map11/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "5ceng",
    minPosY = 70,
}

MapConfig["map12"] = 
{
    filepath = "map/map12/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "5ceng",
    minPosY = 55,
}

MapConfig["map13"] = 
{
    filepath = "map/map13/m.json",
    actorNodeName = "3ceng",
    fixNodeName = "",
    minPosY = 70,
}

MapConfig["map14"] = 
{
    filepath = "map/map14/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "6ceng",
    minPosY = 55,
}

MapConfig["map15"] = 
{
    filepath = "map/map15/m.json",
    actorNodeName = "2ceng",
    fixNodeName = "5ceng",
    minPosY = 65,
}

function MapConfig:loadMap(word, mapKey)
    local c = self[mapKey]
    word:loadMapFile(c.filepath, c.actorNodeName, c.fixNodeName)
    word:setMinPosY(c.minPosY)
    return word
end

return MapConfig