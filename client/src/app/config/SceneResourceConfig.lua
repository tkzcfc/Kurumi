local SceneResourceConfig = {}

-- SceneResourceConfig[] = 
-- {
--     loadResourceList = 
--     {
--         exportJson = {
--         },
--         image = {
--         },
--         plist = {
--         },
--     },
--     releaseResourceList = 
--     {
--         exportJson = {
--         },
--         image = {
--         },
--         plist = {
--         },
--     },
-- }

SceneResourceConfig[_MyG.SCENE_ID_LOGIN] = 
{
    loadResourceList = 
    {
        exportJson = {
        },
        image = {
        },
        plist = {
        },
    },
    releaseResourceList = 
    {
        exportJson = {
        "uianimation/land_background_2.ExportJson",
        "uianimation/playgame.ExportJson",
        },
        image = {
        },
        plist = {
        },
    },
}

SceneResourceConfig[_MyG.SCENE_ID_CREATE] = 
{
    loadResourceList = 
    {
        exportJson = {
        "uianimation/baijixiuluo.ExportJson",
        "uianimation/baijiluocha.ExportJson",
        },
        image = {
        "ui/fragment/4-1.jpg",
        },
        plist = {
        },
    },
    releaseResourceList = 
    {
        exportJson = {
        "uianimation/baijixiuluo.ExportJson",
        "uianimation/baijiluocha.ExportJson",
        },
        image = {
        "ui/fragment/4-1.jpg",
        },
        plist = {
        },
    },
}

SceneResourceConfig[_MyG.SCENE_ID_SELECT] = 
{
    loadResourceList = 
    {
        exportJson = {
        "uianimation/fbylz.ExportJson",
        },
        image = {
        "ui/fragment/fbmap01.png",
        "ui/fragment/fbmap02.png",
        "ui/fragment/fbmap03.png",
        "ui/fragment/fbmap04.png",
        "ui/fragment/fbmap05.png",
        "ui/fragment/fbmap06.png",
        "ui/fragment/fbmap07.png",
        "ui/fragment/fbmap08.png",
        "ui/fragment/fbmap09.png",
        "ui/fragment/fbmap10.png",
        "ui/fragment/fbmap11.png",
        "ui/fragment/fbmap12.png",
        "ui/fragment/fbmap13.png",
        "ui/fragment/fbmap14.png",
        "ui/fragment/fbmap15.png",
        "ui/fragment/fbxmap1.png",
        "ui/fragment/fbxmap2.png",
        "ui/fragment/fbxmap3.png",
        "ui/fragment/fbxmap4.png",
        "ui/fragment/fbxmap5.png",
        "ui/fragment/fbxmap6.png",
        "ui/fragment/fbxmap7.png",
        "ui/fragment/fbxmap8.png",
        "ui/fragment/fbxmap9.png",
        "ui/fragment/fbxmap10.png",
        "ui/fragment/fbxmap11.png",
        "ui/fragment/fbxmap12.png",
        "ui/fragment/fbxmap13.png",
        "ui/fragment/fbxmap14.png",
        "ui/fragment/fbxmap15.png",
        },
        plist = {
        },
    },
    releaseResourceList = 
    {
        exportJson = {
        },
        image = {
        "ui/fragment/fbmap01.png",
        "ui/fragment/fbmap02.png",
        "ui/fragment/fbmap03.png",
        "ui/fragment/fbmap04.png",
        "ui/fragment/fbmap05.png",
        "ui/fragment/fbmap06.png",
        "ui/fragment/fbmap07.png",
        "ui/fragment/fbmap08.png",
        "ui/fragment/fbmap09.png",
        "ui/fragment/fbmap10.png",
        "ui/fragment/fbmap11.png",
        "ui/fragment/fbmap12.png",
        "ui/fragment/fbmap13.png",
        "ui/fragment/fbmap14.png",
        "ui/fragment/fbmap15.png",
        "ui/fragment/fbxmap1.png",
        "ui/fragment/fbxmap2.png",
        "ui/fragment/fbxmap3.png",
        "ui/fragment/fbxmap4.png",
        "ui/fragment/fbxmap5.png",
        "ui/fragment/fbxmap6.png",
        "ui/fragment/fbxmap7.png",
        "ui/fragment/fbxmap8.png",
        "ui/fragment/fbxmap9.png",
        "ui/fragment/fbxmap10.png",
        "ui/fragment/fbxmap11.png",
        "ui/fragment/fbxmap12.png",
        "ui/fragment/fbxmap13.png",
        "ui/fragment/fbxmap14.png",
        "ui/fragment/fbxmap15.png",
        },
        plist = {
        },
    },
}


SceneResourceConfig[_MyG.SCENE_ID_MAIN] = 
{
    loadResourceList = 
    {
        exportJson = {
        "zhuc_ldpi/ccjz.ExportJson",    --经商之路
        "zhuc_ldpi/huos.ExportJson",    --地狱（火山）
        "zhuc_ldpi/lhjz.ExportJson",    --轮回
        -- "zhuc_ldpi/mkjz.ExportJson", --魔窟
        "zhuc_ldpi/sdjz.ExportJson",    --商城
        "zhuc_ldpi/sg2.ExportJson",     --特效1
        "zhuc_ldpi/tfspjz.ExportJson",  --神秘商店
        "zhuc_ldpi/youxjz.ExportJson",  --邮箱
        "zhuc_ldpi/yun.ExportJson",     --云 
        "zhuc_ldpi/zhucheng_fengyinshi.ExportJson",  --英雄试炼
        "zhuc_ldpi/zhucheng_gonghui.ExportJson",  --工会
        "zhuc_ldpi/zhucheng_jingjichang.ExportJson",  --竞技场
        "zhuc_ldpi/zhucheng_niaojuchangjing.ExportJson",  --副本入口
        "zhuc_ldpi/zhucheng_paihangbang.ExportJson",  --排行榜
        "zhuc_ldpi/zhucheng_tujian.ExportJson",  --图鉴
        "zhuc_ldpi/zhucheng_yaodaofang.ExportJson",  --珍宝屋
        },
        image = {
        "zhuc_ldpi/cpmapd01.png",
        "zhuc_ldpi/cpmapd02.png",
        "zhuc_ldpi/cpmapd03.png",
        "zhuc_ldpi/cpmapd04.png",
        "zhuc_ldpi/cpmapd05.png",
        "zhuc_ldpi/cpmapd06.png",
        "zhuc_ldpi/cpmapd07.png",
        "zhuc_ldpi/cpmape01.png",
        "zhuc_ldpi/cpmape02.png",
        "zhuc_ldpi/cpmape03.png",
        "zhuc_ldpi/cpmape04.png",
        "zhuc_ldpi/cpmape05.png",
        "zhuc_ldpi/dmmapb01.png",
        "zhuc_ldpi/dmmapb02.png",
        "zhuc_ldpi/dmmapb03.png",
        "zhuc_ldpi/dmmapb04.png",
        "zhuc_ldpi/dmmapb05.png",
        "zhuc_ldpi/dmmapb06.png",
        "zhuc_ldpi/dmmapb07.png",
        "zhuc_ldpi/dmmapb08.png",
        "zhuc_ldpi/dmmapb09.png",
        "zhuc_ldpi/dmmapb10.png",
        "zhuc_ldpi/yhmapc01.png",
        "zhuc_ldpi/yhmapc02.png",
        "zhuc_ldpi/yhmapc03.png",
        "zhuc_ldpi/yhmapc04.png",
        "zhuc_ldpi/yhmapc05.png",
        "zhuc_ldpi/yhmapc06.png",
        "zhuc_ldpi/yhmapc07.png",
        "zhuc_ldpi/yhmapc08.png",
        "zhuc_ldpi/yhmapc09.png",
        "zhuc_ldpi/ysmapa01.png",
        "zhuc_ldpi/ysmapa02.png",
        "zhuc_ldpi/ysmapa03.png",
        "zhuc_ldpi/ysmapa04.png",
        "zhuc_ldpi/ysmapa05.png",
        "zhuc_ldpi/ysmapa06.png",
        "zhuc_ldpi/ysmapa07.png",
        "zhuc_ldpi/ysmapa08.png",
        "zhuc_ldpi/ysmapa09.png",
        },
        plist = {
        },
    },
    releaseResourceList = 
    {
        exportJson = {
        },
        image = {
        "zhuc_ldpi/cpmapd01.png",
        "zhuc_ldpi/cpmapd02.png",
        "zhuc_ldpi/cpmapd03.png",
        "zhuc_ldpi/cpmapd04.png",
        "zhuc_ldpi/cpmapd05.png",
        "zhuc_ldpi/cpmapd06.png",
        "zhuc_ldpi/cpmapd07.png",
        "zhuc_ldpi/cpmape01.png",
        "zhuc_ldpi/cpmape02.png",
        "zhuc_ldpi/cpmape03.png",
        "zhuc_ldpi/cpmape04.png",
        "zhuc_ldpi/cpmape05.png",
        "zhuc_ldpi/dmmapb01.png",
        "zhuc_ldpi/dmmapb02.png",
        "zhuc_ldpi/dmmapb03.png",
        "zhuc_ldpi/dmmapb04.png",
        "zhuc_ldpi/dmmapb05.png",
        "zhuc_ldpi/dmmapb06.png",
        "zhuc_ldpi/dmmapb07.png",
        "zhuc_ldpi/dmmapb08.png",
        "zhuc_ldpi/dmmapb09.png",
        "zhuc_ldpi/dmmapb10.png",
        "zhuc_ldpi/yhmapc01.png",
        "zhuc_ldpi/yhmapc02.png",
        "zhuc_ldpi/yhmapc03.png",
        "zhuc_ldpi/yhmapc04.png",
        "zhuc_ldpi/yhmapc05.png",
        "zhuc_ldpi/yhmapc06.png",
        "zhuc_ldpi/yhmapc07.png",
        "zhuc_ldpi/yhmapc08.png",
        "zhuc_ldpi/yhmapc09.png",
        "zhuc_ldpi/ysmapa01.png",
        "zhuc_ldpi/ysmapa02.png",
        "zhuc_ldpi/ysmapa03.png",
        "zhuc_ldpi/ysmapa04.png",
        "zhuc_ldpi/ysmapa05.png",
        "zhuc_ldpi/ysmapa06.png",
        "zhuc_ldpi/ysmapa07.png",
        "zhuc_ldpi/ysmapa08.png",
        "zhuc_ldpi/ysmapa09.png",
        },
        plist = {
        },
    },
}


function SceneResourceConfig:DefaultLoadFunc(sceneid, resourceScene, args)
    local list = self[sceneid].loadResourceList.exportJson
    for k,v in pairs(list) do
        resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, v)
    end

    list = self[sceneid].loadResourceList.image
    for k,v in pairs(list) do
        resourceScene:addLoadResource(_MyG.RES_TYPE.PNG, v)
    end

    list = self[sceneid].loadResourceList.plist
    for k,v in pairs(list) do
        resourceScene:addLoadResource(_MyG.RES_TYPE.PLIST, v)
    end
end

function SceneResourceConfig:DefaultReleaseFunc(sceneid, resourceScene, args)
    local list = self[sceneid].releaseResourceList.exportJson
    for k,v in pairs(list) do
        resourceScene:addReleaseResource(_MyG.RES_TYPE.EXPORTJSON, v)
    end

    list = self[sceneid].releaseResourceList.image
    for k,v in pairs(list) do
        resourceScene:addReleaseResource(_MyG.RES_TYPE.PNG, v)
    end

    list = self[sceneid].releaseResourceList.plist
    for k,v in pairs(list) do
        resourceScene:addReleaseResource(_MyG.RES_TYPE.PLIST, v)
    end
end

return SceneResourceConfig