-- 平台定义
PLATFORM_ANDROID = "android"
PLATFORM_IOS 	 = "ios"
PLATFORM_WINDOWS = "windows"
PLATFORM_MAC 	 = "mac"
PLATFORM_LINUX 	 = "linux"

--http://47.75.218.200:1000/91/PKDir/

local M = {}

-- 加密用到的sign
M["encryptsign"] = "v9UpiNlR"

-- 加密用到的key
M["encryptkey"] = "8hQlU84hSbDa"

-- 资源版本（重要，关系到是否更不更新）
M["version"] = "0.0.1"

local dirName = "v_" .. string.gsub(M["version"], "%.", "_")

-- 要下载具体内容的地址
M["packageUrl"] = string.format("http://127.0.0.1:7878/%s/", dirName)

-- 远程的配置清单文件地址
M["remoteManifestUrl"] = string.format("http://127.0.0.1:7878/%s/project_dev.manifest", dirName)

-- 远程版本文件地址
M["remoteVersionUrl"] = string.format("http://127.0.0.1:7878/%s/version_dev.manifest", dirName)

-- 更新描述
M["updateDescription"] = [[1:修复bug
2:增加功能
]]

-- 强更新版本(如果客户端版本小于当前版本，则客户端进行弹框提示，用户确认跳转至新版本下载地址)
M["strongUpdateVer"] = {}
-- 平台PLATFORM_ANDROID强更新版本
M["strongUpdateVer"][PLATFORM_ANDROID] 	= 0
-- 平台PLATFORM_IOS强更新版本
M["strongUpdateVer"][PLATFORM_IOS] 		= 0
--...

-- 强更新下载地址
M["strongUpdateURL"] = {}
M["strongUpdateURL"][PLATFORM_ANDROID] 	= "www.baidu.com"
M["strongUpdateURL"][PLATFORM_IOS] 		= "www.google.com"

-- 强更新描述
M["strongUpdateDes"] = {}
M["strongUpdateDes"][PLATFORM_ANDROID] 	= "Android我是强更新描述"
M["strongUpdateDes"][PLATFORM_IOS] 		= "IOS我是强更新描述"


-- 重启等级
-- 说明：0->不需要重启 1->程序自动重启 2->用户手动重启
M["restartLevel"] = 1


-- 引擎版本（无关紧要）
M["engineVersion"] = "3.x dev"

-- 搜索路径
-- 格式
-- M["searchPaths"] = 
-- {
-- 	"res/b",
-- 	"res/img",
-- }
M["searchPaths"] = {}


-- 需要解压的压缩文件列表(在下载资源完毕后需要解压的zip文件)
-- 格式
-- M["compressedFileList"] = 
-- {
-- 	"Image/a.zip",
-- 	"Image/b.zip",
-- 	"c.zip"
-- }
M["compressedFileList"] = {}

-- 忽略文件列表
-- 格式
-- M["ignoreFileList"] = 
-- {
-- 	"Image/a.zip",
-- 	"Image/b.zip",
-- 	"c.zip"
-- }
M["ignoreFileList"] = 
{
}

-- 资源文件目录
M["resourceDir"] = lfs.currentdir().."/../../client/"

return M
