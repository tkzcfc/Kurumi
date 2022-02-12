local ShengBoConfig = 
{
	ExportJson = "monster/shengbo/shengbo.ExportJson",
	Armature = "shengbo",

	StateConfig = 
	{
		State_Stand = {"fstand"},
		State_Run = {"frun_2"},
		State_Turn = {"fturn_1", "fturn_2"},
		State_Hit = {"hit"},
		State_Attack1 = {"attack1"},
		State_Attack2 = {"attack2"},
		State_Kill = {"skill1"},
		
		-- State_Collapase_Up = {"collapse_1", "collapse_2"},
		-- State_Collapase_Down = {"collapse_3", "collapse_4"},
		State_Collapase_Up = {"collapse_1", "collapse_3"},
		State_Collapase_Down = {"collapse_4"},
		
		State_Collapase_EndToStand = {"collapse_5", "collapse_6", "collapse_7"},
		State_Collapase_EndToDead = {"collapse_5", "collapse_6", "dead"},
		State_Dead	= {"collapse_3", "collapse_5", "dead"},
	}
}

-- 基础属性配置
ShengBoConfig.BaseConfig = 
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
ShengBoConfig.AI_CONFIG = 
{
	ATTACK_MIN_RANGE = 400,
	ATTACK_INTERVAL = 1.0,
}

return ShengBoConfig