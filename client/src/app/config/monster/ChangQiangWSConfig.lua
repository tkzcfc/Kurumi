local ChangQiangWSConfig = 
{
	ExportJson = "monster/changqianws/changqianws.ExportJson",
	Armature = "changqianws",

	StateConfig = 
	{
		State_Stand = {"fstand"},
		State_Run = {"frun_1", "frun_2"},
		State_Turn = {"fturn_1", "fturn_2"},
		State_Hit = {"hit"},
		State_JumpUp = {"fjumpup_1", "fjumpup_2"},
		State_JumpDown = {"fjumpup_3", "fjumpdown_1"},
		State_JumpDownEnd = {"fjumpdown_2"},
		State_Attack = {"attack"},
		State_Kill1 = {"skill"},
		State_Kill2 = {"skill_2"},
	}
}

return ChangQiangWSConfig