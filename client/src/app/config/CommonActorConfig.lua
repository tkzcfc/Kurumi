local CommonActorConfig = {}

--玩家跳跃高度
CommonActorConfig.playerJumpHeight = 350

--玩家跳跃时间
CommonActorConfig.playerJumpTime = 0.45



--角色受到攻击时后退速度
CommonActorConfig.playerHitBackSpeed = {x = -30, y = 0}



--角色移动速度
CommonActorConfig.playerMoveSpeed = {x = 900, y = 0}



--角色向后倒移动速度
CommonActorConfig.playerCollapseMovePower = {x = -200, y = 0}

--角色向后倒抛起高度
CommonActorConfig.playerCollapseJumpHeight = 300

--角色向后倒抛起时间
CommonActorConfig.playerCollapseJumpTime = 0.4


return CommonActorConfig