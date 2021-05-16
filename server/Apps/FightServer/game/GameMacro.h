#pragma once

#include "GLibBase.h"

////////////////////////////////////////////////////////////////////////////////////

#ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
#endif
#ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
#endif

//! 在地图中战斗的玩家最大个数
#define G_FIGHT_MAX_PLAYER_COUNT 4

typedef uint32_t GUUID;
#define INVALID_UUID 0U