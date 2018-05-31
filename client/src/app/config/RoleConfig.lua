local RoleConfig = {}

RoleConfig["hero_lanse_dao"] = 
{
	ExportJson = "role/baiji/hero_lanse_dao.ExportJson",
	Armature = "hero_lanse_dao",

	StateConfig = 
	{
		State_Stand = {"fstand"},
		State_Run = {"frun_1", "frun_2"},
		State_Replace = {"replace_1", "replace_2", "replace_3"},
		State_JumpUp = {"fjumpup_1", "fjumpup_2"},
		State_JumpDown = {"fjumpup_3", "fjumpdown_1"},
		State_JumpDownEnd = {"fjumpdown_2"},
		State_Attack1 = {"attack1_1", "attack1_2"},
		State_Attack2 = {"attack2_1", "attack2_2"},
		State_Attack3 = {"attack3_1", "attack3_2"},
		State_Attack4 = {"attack4_1", "attack4_2"},
		State_JumpAttack1 = {"kattack1_1", "kattack1_2"},
		State_JumpAttack2 = {"kattack2_1", "kattack2_2"},
		State_JumpAttack3 = {"kattack2_1", "kattack2_2", "kattack3_1", "kattack3_2"},
		State_Hit = {"hit"},
	}
}

-- RoleConfig["hero_lanse_dao"] = 
-- {
-- 	ExportJson = "role/baiji/hero_lanse_dao.ExportJson",
-- 	Armature = "hero_lanse_dao",

-- 	StateConfig = 
-- 	{
-- 		fstand 		= "fstand",
-- 		frun_1 		= "frun_1",
-- 		frun_2 		= "frun_2",
-- 		fbrake 		= "fbrake",
-- 		fturn_1		= "fturn_1",
-- 		fturn_2		= "fturn_2",
-- 		pull		= "pull",
-- 		regain 		= "regain",
-- 		fjumpup_1	= "fjumpup_1",
-- 		fjumpup_2 	= "fjumpup_2",
-- 		fjumpup_3	= "fjumpup_3",
-- 		fjumpdown_1	= "fjumpdown_1",
-- 		fjumpdown_2	= "fjumpdown_2",
-- 		replace_1	= "replace_1",
-- 		replace_2	= "replace_2",
-- 		replace_3	= "replace_3",
-- 		hit			= "hit",
-- 		collapse_1	= "collapse_1",
-- 		collapse_2	= "collapse_2",
-- 		collapse_3	= "collapse_3",
-- 		attack1_1	= "attack1_1",
-- 		attack1_2	= "attack1_2",
-- 		attack2_1	= "attack2_1",
-- 		attack2_2	= "attack2_2",
-- 		attack3_1	= "attack3_1",
-- 		attack3_2	= "attack3_2",
-- 		attack4_1	= "attack4_1",
-- 		attack4_2	= "attack4_2",
-- 		kattack1_1	= "kattack1_1",
-- 		kattack1_2	= "kattack1_2",
-- 		kattack2_1	= "kattack2_1",
-- 		kattack2_2	= "kattack2_2",
-- 		kattack3_1	= "kattack3_1",
-- 		kattack3_2	= "kattack3_2",
-- 	}
-- }


return RoleConfig