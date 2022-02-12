#pragma once

#include "GMapLayer_Custom.h"
#include "GMapLayer_Parallax.h"

NS_G_BEGIN

#if 1
typedef GMapLayer_Custom GMapLayer;
#else
typedef GMapLayer_Parallax GMapLayer;
#endif

NS_G_END

