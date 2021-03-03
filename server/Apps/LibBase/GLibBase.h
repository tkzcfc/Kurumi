#pragma once

#include "GObject.h"
#include "GSmartPtr.h"
#include "GApplication.h"
#include "Service/GIService.h"
#include "Service/GNetService.h"
#include "Service/GConfigService.h"
#include "Service/GServiceMgr.h"
#include "Service/GMasterNodeService.h"
#include "Service/GSlaveNodeService.h"
#include "GScheduler.h"
#include "GFileSystem.h"
#include "GStringUtils.h"

#define SEND_PB_MSG(sender, sessionID, msgID, msg) { \
	std::string sdata; \
	if (ack.SerializeToString(&sdata)) \
	{\
		sender->sendMsg(sessionID, msgID, (char*)sdata.c_str(), sdata.size());\
	}\
	else\
	{\
		LOG(ERROR) << "Serialize Msg '"<< ack.GetTypeName() << "'Failed, File:" << __FILE__ << ", Line:" << __LINE__;\
	}\
}

#define PARSE_PB_MSG(msg, data, len) {\
	if(!msg.ParsePartialFromArray(data, len)) {\
		LOG(ERROR) << "Parse Msg '"<< msg.GetTypeName() << "'Failed, File:" << __FILE__ << ", Line:" << __LINE__;\
	}\
}

#define PARSE_PB_MSG_RETURN(msg, data, len) {\
	if(!msg.ParsePartialFromArray(data, len)) {\
		LOG(ERROR) << "Parse Msg '"<< msg.GetTypeName() << "'Failed, File:" << __FILE__ << ", Line:" << __LINE__;\
		return;\
	}\
}

#define PARSE_PB_MSG_RETURN_NULL(msg, data, len) {\
	if(!msg.ParsePartialFromArray(data, len)) {\
		LOG(ERROR) << "Parse Msg '"<< msg.GetTypeName() << "'Failed, File:" << __FILE__ << ", Line:" << __LINE__;\
		return NULL;\
	}\
}
