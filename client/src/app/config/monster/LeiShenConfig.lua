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
		State_Kill6 = {"skill6_1", "skill6_2"},
		State_Kill6_Finish = {"skill6_3"},
		State_Turn = {"fturn_1", "fturn_2"},
		State_Collapase_EndToStand = {"collapse_1", "collapse_7"},
		State_Collapase_EndToDead = {"collapse_1", "dead_1", "dead_2"},
		State_Dead	= {"collapse_1", "dead_1", "dead_2"},
	}
}

--跟随配置
LeiShenConfig.FOLLOW_CONFIG = 
{
	--状态切换最小间隔时间
	STATE_CHAGE_MIN_TIME = 0.5,
	--状态切换最大间隔时间
	STATE_CHAGE_MAX_TIME = 1.5,

	--跟随最大值
	FOLLOW_MAX = 800,
	--跟随最小值
	FOLLOW_MIN = 100,
	
	--小于最小值时的配置
	FOLLOW_L_MIN = 
	{
		--切换方向最小间隔时间
		updateOriMinTime = 0.5,
		--切换方向最大间隔时间
		updateOriMaxTime = 0.8,
		--移动状态下权重
		changeOriWidget = {
			FOLLOW = 3,	--跟随
			BACK   = 3,	--后退
			NONE   = 1, --不做任何操作（休息）
		},
		--状态权重
		STATE_WEIGHT = 
		{
			SLEEP = 0,
			MOVE  = 1,
			OTHER = 6
		},
	},
	--大于最大值时的配置
	FOLLOW_G_MAX = 
	{
		updateOriMinTime = 0.3,
		updateOriMaxTime = 0.5,
		changeOriWidget = {
			FOLLOW = 2,
			BACK   = 2,
			NONE   = 3,
		},
		STATE_WEIGHT = 
		{
			SLEEP = 2,
			MOVE  = 8,
			OTHER = 0
		},
	},
	--最大值和最小值之间
	FOLLOW_E_RANGE = 
	{
		updateOriMinTime = 0.3,
		updateOriMaxTime = 0.5,
		changeOriWidget = {
			FOLLOW = 4,
			BACK   = 2,
			NONE   = 1,
		},
		STATE_WEIGHT = 
		{
			SLEEP = 0,
			MOVE  = 6,
			OTHER = 3
		},
	},
}

return LeiShenConfig