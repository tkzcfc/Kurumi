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
	MoveVelocity = 500.0 / BOX2D_PIXEL_TO_METER,

	-- 受到攻击时冲力
	HitImpluse = -150.0 / BOX2D_PIXEL_TO_METER,

	-- 受到攻击并向后抛 
	-- 抛起冲力(瞬间冲力)
	CollapseYImpluse = 500.0 / BOX2D_PIXEL_TO_METER,

	-- 向后冲力
	CollapseXImpluse = -100.0 / BOX2D_PIXEL_TO_METER,

}

-- AI
LeiShenConfig.AI_CONFIG = 
{
	ATTACK_MIN_RANGE = 700,
	ATTACK_INTERVAL = 1.0,
}

return LeiShenConfig