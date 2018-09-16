local LeiShenConfig = 
{
	ExportJson = "monster/boss5_leishen/boss5_leishen.ExportJson",
	Armature = "boss5_leishen",

	StateConfig = 
	{
		State_Stand = {"fstand"},
		State_Run = {"frun_1", "frun_2"},
		State_Brake = {"fbrake"},
		State_Hit = {"hit"},
		State_Kill1 = {"skill1_1"},
		State_Kill2 = {"skill2_1"},
		State_Kill3 = {"skill3_1", "skill3_2"},
		State_Kill4 = {"skill4_1"},
		State_Kill5_1 = {"skill5_1"},
		State_Kill5_2 = {"skill5_2"},
		State_Kill6_Begin = {"skill6_1"},
		State_Kill6_Run = {"skill6_2"},
		State_Kill6_Finish = {"skill6_3"},
		State_Turn = {"fturn_1", "fturn_2"},
		State_Collapase_EndToStand = {"collapse_1", "collapse_7"},
		State_Collapase_EndToDead = {"collapse_1", "dead_1", "dead_2"},
		State_Dead	= {"collapse_1", "dead_1", "dead_2"},
	}
}

-- 基础属性配置
LeiShenConfig.BaseConfig = 
{
	-- 移动速度
	MoveVelocity = 500.0 / PIXEL_TO_METER,

	-- 受到攻击时冲力
	HitImpluse = -150.0 / PIXEL_TO_METER,

	-- 受到攻击并向后抛 
	-- 抛起冲力(瞬间冲力)
	CollapseYImpluse = 500.0 / PIXEL_TO_METER,

	-- 向后冲力
	CollapseXImpluse = -100.0 / PIXEL_TO_METER,

}

--跟随配置
LeiShenConfig.FOLLOW_CONFIG = 
{
	--状态切换最小间隔时间
	STATE_CHAGE_MIN_TIME = 0.4,
	--状态切换最大间隔时间
	STATE_CHAGE_MAX_TIME = 1.0,

	--跟随最大值
	FOLLOW_MAX = 1000,
	--跟随最小值
	FOLLOW_MIN = 400,
	
	--小于最小值时的配置
	FOLLOW_L_MIN = 
	{
		--切换方向最小间隔时间
		updateOriMinTime = 0.2,
		--切换方向最大间隔时间
		updateOriMaxTime = 0.3,
		--移动状态下权重
		changeOriWidget = {
			FOLLOW = 3,	--跟随
			BACK   = 4,	--后退
			NONE   = 1, --不做任何操作（休息）
		},
		--状态权重
		STATE_WEIGHT = 
		{
			SLEEP = 0,
			MOVE  = 1,
			OTHER = 10
		},
	},
	--大于最大值时的配置
	FOLLOW_G_MAX = 
	{
		updateOriMinTime = 0.2,
		updateOriMaxTime = 0.4,
		changeOriWidget = {
			FOLLOW = 2,
			BACK   = 2,
			NONE   = 3,
		},
		STATE_WEIGHT = 
		{
			SLEEP = 2,
			MOVE  = 8,
			OTHER = 12
		},
	},
	--最大值和最小值之间
	FOLLOW_E_RANGE = 
	{
		updateOriMinTime = 0.2,
		updateOriMaxTime = 0.3,
		changeOriWidget = {
			FOLLOW = 4,
			BACK   = 2,
			NONE   = 1,
		},
		STATE_WEIGHT = 
		{
			SLEEP = 0,
			MOVE  = 6,
			OTHER = 10
		},
	},
}

return LeiShenConfig