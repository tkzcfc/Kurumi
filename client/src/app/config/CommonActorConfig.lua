local CommonActorConfig = {}

--角色向后倒抛起高度
CommonActorConfig.playerCollapseJumpHeight = 800

--角色向后倒抛起时间
CommonActorConfig.playerCollapseJumpTime = 0.4







-- 移动速度
CommonActorConfig.MoveVelocity = 900.0 / PIXEL_TO_METER

-- 刹车速度
CommonActorConfig.BrakVelocity = 600.0 / PIXEL_TO_METER

-- 跳跃冲力
CommonActorConfig.JumpImpulse = 900.0 / PIXEL_TO_METER

-- 跳跃时移动速度
CommonActorConfig.JumMoveVelocity = 300.0 / PIXEL_TO_METER

-- 二段跳冲力
CommonActorConfig.AirHikeImpulse = 700.0 / PIXEL_TO_METER

-- 在空中最多允许跳跃最大次数
CommonActorConfig.MAX_JUMP_COUNT_IN_AIR = 2

-- 在空中最多允许攻击最大次数
CommonActorConfig.MAX_ATTACK_COUNT_IN_AIR = 1

-- 空中攻击时角色的下落速度
CommonActorConfig.AttackInAirDescentVelocity = 200.0 / PIXEL_TO_METER

-- 空中攻击时的移动速度
CommonActorConfig.AttackInAirMoveVelocity = 80.0 / PIXEL_TO_METER


return CommonActorConfig