

local CURRENT_MODULE_NAME = ...
local PACKAGE_NAME = string.sub(CURRENT_MODULE_NAME, 1, -6)

-- quick改动了一些东西导致官方版的API用不了，这儿分成两个分支
if true then
	PACKAGE_NAME = PACKAGE_NAME .. ".quick"
else
	PACKAGE_NAME = PACKAGE_NAME .. ".cocos"
end

require(PACKAGE_NAME .. ".ScrollViewEx")

G_Class.PanZoomLayer 	= require(PACKAGE_NAME .. ".PanZoomLayer")
G_Class.CycleListView 	= require(PACKAGE_NAME .. ".CycleListView")
G_Class.ScrollItem 		= require(PACKAGE_NAME .. ".ScrollItem")
G_Class.TableViewEx 	= require(PACKAGE_NAME .. ".TableViewEx")
G_Class.TyperLabel 		= require(PACKAGE_NAME .. ".TyperLabel")
G_Class.RichLabel 		= require(PACKAGE_NAME .. ".rich.RichLabel")
G_Class.Alignment 		= require(PACKAGE_NAME .. ".Alignment")
G_Class.PseudoRichText	= require(PACKAGE_NAME .. ".PseudoRichText")



