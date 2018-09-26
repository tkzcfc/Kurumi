local RoleConfig = {}

local CommonStateConfig = 
{
	State_Stand = {"fstand"},
	State_Run = {"frun_1"},
	State_Run2 = {"frun_2"},
	State_Brak = {"fbrake"},
	State_Replace = {"replace_1", "replace_2", "replace_3"},
	State_JumpUp = {"fjumpup_1", "fjumpup_2"},
	State_JumpDown = {"fjumpup_3", "fjumpdown_1"},
	State_JumpDownEnd = {"fjumpdown_2"},
	State_JumpUp_2 = {"fjumpup_2"},
	State_Attack1 = {"attack1_1", "attack1_2"},
	State_Attack2 = {"attack2_1", "attack2_2"},
	State_Attack3 = {"attack3_1", "attack3_2"},
	State_Attack4 = {"attack4_1", "attack4_2"},
	State_JumpAttack1 = {"kattack1_1", "kattack1_2"},
	State_JumpAttack2 = {"kattack2_1", "kattack2_2"},
	State_JumpAttack3 = {"kattack2_1", "kattack2_2", "kattack3_1", "kattack3_2"},
	State_Hit = {"hit"},
	State_Collapse1 = {"collapse_1"},
	State_Collapse2 = {"collapse_2"},
	State_Collapse3 = {"collapse_3"},
	State_Upcut = {"upcut_1", "upcut_2"},
	State_DownCut = {"downcut_1", "downcut_2"},
	State_KAttack4_Begin = {"kattack4_1", "kattack4_2"},
	State_KAttack4_End = {"kattack4_3"},
	State_Skill2_Begin = {"skill2_1", "skill2_2"},
	State_Skill2_End = {"kattack4_3"},
	State_Skill3_Begin = {"skill3_0", "skill3_1"},
	State_Skill3_End = {"skill3_2"},
}

local CommonSoundConfig = 
{
	State_Stand 			= nil,
	State_Run 				= nil,
	State_Run2 				= nil,
	State_Brak 				= "audio/brake.ogg",
	State_Replace 			= nil,
	State_JumpUp 			= nil,
	State_JumpDown 			= nil,
	State_JumpDownEnd 		= nil,
	State_JumpUp_2 			= nil,
	State_Attack1 			= "audio/baiji_atk_1.ogg",
	State_Attack2 			= "audio/baiji_atk_2.ogg",
	State_Attack3 			= "audio/baiji_atk_3.ogg",
	State_Attack4 			= "audio/baiji_atk_4.ogg",
	State_JumpAttack1 		= nil,
	State_JumpAttack2 		= nil,
	State_JumpAttack3 		= nil,
	State_Hit 				= nil,
	State_Collapse1 		= nil,
	State_Collapse2 		= nil,
	State_Collapse3 		= nil,
	State_Upcut 			= "audio/baiji_atk_xulizhan.ogg",
	State_DownCut 			= "audio/baiji_atk_xiazhan.ogg",
	State_KAttack4_Begin 	= nil,
	State_KAttack4_End 		= nil,
	State_Skill2_Begin 		= nil,
	State_Skill2_End 		= nil,
	State_Skill3_Begin 		= nil,
	State_Skill3_End 		= nil,
}

RoleConfig["hero_lanse_dao"] = 
{
	ExportJson = "role/baiji/hero_lanse_dao.ExportJson",
	Armature = "hero_lanse_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}

RoleConfig["hero_xiuluo_dao"] = 
{
	ExportJson = "role/baiji/hero_xiuluo_dao.ExportJson",
	Armature = "hero_xiuluo_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}

RoleConfig["hero_shizxianzi_dao"] = 
{
	ExportJson = "role/baiji/hero_shizxianzi_dao.ExportJson",
	Armature = "hero_shizxianzi_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}

RoleConfig["hero_shizwushikaijia_dao"] = 
{
	ExportJson = "role/baiji/hero_shizwushikaijia_dao.ExportJson",
	Armature = "hero_shizwushikaijia_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_shizwushi_dao"] = 
{
	ExportJson = "role/baiji/hero_shizwushi_dao.ExportJson",
	Armature = "hero_shizwushi_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}

RoleConfig["hero_shizshuishoufu_dao"] = 
{
	ExportJson = "role/baiji/hero_shizshuishoufu_dao.ExportJson",
	Armature = "hero_shizshuishoufu_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_shizshenyin_dao"] = 
{
	ExportJson = "role/baiji/hero_shizshenyin_dao.ExportJson",
	Armature = "hero_shizshenyin_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_shiznvpu_dao"] = 
{
	ExportJson = "role/baiji/hero_shiznvpu_dao.ExportJson",
	Armature = "hero_shiznvpu_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_shizmaonv_dao"] = 
{
	ExportJson = "role/baiji/hero_shizmaonv_dao.ExportJson",
	Armature = "hero_shizmaonv_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_shizhuak_dao"] = 
{
	ExportJson = "role/baiji/hero_shizhuak_dao.ExportJson",
	Armature = "hero_shizhuak_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_shizconglin_dao"] = 
{
	ExportJson = "role/baiji/hero_shizconglin_dao.ExportJson",
	Armature = "hero_shizconglin_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_luocha_dao"] = 
{
	ExportJson = "role/baiji/hero_luocha_dao.ExportJson",
	Armature = "hero_luocha_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}


RoleConfig["hero_baiji_dao"] = 
{
	ExportJson = "role/baiji/hero_baiji_dao.ExportJson",
	Armature = "hero_baiji_dao",

	StateConfig = CommonStateConfig,
	SoundConfig = CommonSoundConfig,
}

return RoleConfig