-- @Author : fangcheng
-- @Date   : 2020-03-22 14:25:59
-- @remark : 游戏宏定义

local G_MAC = {}

-- 三个平台判断
local TARGET_PALTFORM = cc.Application:getInstance():getTargetPlatform()

G_MAC.TARGET_PALTFORM = TARGET_PALTFORM
G_MAC.IS_IOS = TARGET_PALTFORM == cc.PLATFORM_OS_IPHONE or TARGET_PALTFORM == cc.PLATFORM_OS_IPAD or TARGET_PALTFORM == cc.PLATFORM_OS_MAC 
G_MAC.IS_ANDROID = TARGET_PALTFORM == cc.PLATFORM_OS_ANDROID
G_MAC.IS_WINDOWS = TARGET_PALTFORM == cc.PLATFORM_OS_WINDOWS
G_MAC.IS_PC = TARGET_PALTFORM == cc.PLATFORM_OS_WINDOWS or TARGET_PALTFORM == cc.PLATFORM_OS_MAC

G_MAC.DEBUG = G_MAC.IS_PC

return G_MAC
