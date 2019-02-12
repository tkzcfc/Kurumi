local CommonActorConfig = {}


-- 移动冲力
CommonActorConfig.MoveImpulse = 900.0 / BOX2D_PIXEL_TO_METER

-- 刹车速度
CommonActorConfig.BrakVelocity = 600.0 / BOX2D_PIXEL_TO_METER

-- 跳跃冲力(瞬间冲力)
CommonActorConfig.JumpImpulse = 1000.0 / BOX2D_PIXEL_TO_METER

-- 二段跳冲力(瞬间冲力)
CommonActorConfig.AirHikeImpulse = 700.0 / BOX2D_PIXEL_TO_METER

-- 跳跃时移动速度
CommonActorConfig.JumMoveImpulse = 600.0 / BOX2D_PIXEL_TO_METER

-- 在空中最多允许跳跃最大次数
CommonActorConfig.MAX_JUMP_COUNT_IN_AIR = 2

-- 在空中最多允许攻击最大次数
CommonActorConfig.MAX_ATTACK_COUNT_IN_AIR = 1

-- 空中攻击时角色的下落速度
CommonActorConfig.AttackInAirDescentVelocity = 200.0 / BOX2D_PIXEL_TO_METER

-- 空中攻击时的移动速度
CommonActorConfig.AttackInAirMoveVelocity = 80.0 / BOX2D_PIXEL_TO_METER

-- 普通攻击1移动冲力(瞬时冲力)
CommonActorConfig.Attacl_1_MoveImpulse = 100.0 / BOX2D_PIXEL_TO_METER

-- 普通攻击1移动冲力(持续冲力)
CommonActorConfig.Attacl_2_MoveImpulse = 130.0 / BOX2D_PIXEL_TO_METER

-- 普通攻击1移动冲力(持续冲力)
CommonActorConfig.Attacl_3_MoveImpulse = 100.0 / BOX2D_PIXEL_TO_METER

-- 普通攻击1移动冲力(瞬时冲力)
CommonActorConfig.Attacl_4_MoveImpulse = 250.0 / BOX2D_PIXEL_TO_METER

-- 上冲攻击冲力(持续冲力)
CommonActorConfig.Upcut_Impulse = 120.0 / BOX2D_PIXEL_TO_METER

-- 上冲攻击完毕跳跃冲力(瞬间冲力)
CommonActorConfig.Upcut_JumpImpulse = 800.0 / BOX2D_PIXEL_TO_METER

-- 下段攻击移动冲力
CommonActorConfig.DownCutImpulse = 400.0 / BOX2D_PIXEL_TO_METER

-- 受到攻击时冲力(瞬间冲力)
CommonActorConfig.HitImpluse = -100.0 / BOX2D_PIXEL_TO_METER

-- 受到攻击并向后抛 
-- 抛起冲力(瞬间冲力)
CommonActorConfig.CollapseYImpluse = 800.0 / BOX2D_PIXEL_TO_METER 

-- 向后冲力
CommonActorConfig.CollapseXImpluse = -100.0 / BOX2D_PIXEL_TO_METER 

-- 技能1持续时间
CommonActorConfig.SKill_01_DurationTime = 0.9

-- 技能1移动冲力
CommonActorConfig.SKill_01_Impulse = 500.0 / BOX2D_PIXEL_TO_METER

-- 技能10持续时间
CommonActorConfig.SKill_10_DurationTime = 1.5


return CommonActorConfig