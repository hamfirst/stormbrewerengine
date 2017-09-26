
#include "Foundation/Common.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Server/ServerTypesJson.h"
#include "Server/ServerTypesNet.h"
#include "Server/ServerObject/ServerObjectRegistrationMacros.h"
#include "Server/ServerObject/ServerObjectMetaFuncs.h"
#include "Server/ServerObject/ServerObjectSystem.h"
#include "Server/ServerObject/ServerObjectUpdate.h"
#include "Server/ServerObject/ServerObjectSerialzie.h"

#include "Game/ServerObjects/PlayerServerObject.refl.h"
#include "Game/ServerObjects/PlayerServerObject.refl.meta.h"

REGISTER_SERVER_OBJECT_WITH_INIT_DATA(PlayerServerObject, PlayerServerObjectInitData, ServerObject);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(PlayerServerObjectInitData);