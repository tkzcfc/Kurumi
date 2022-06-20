#pragma once

#include "pb/Msg_ID.pb.h"
#include "pb/C2Fight.pb.h"
#include "pb/C2Game.pb.h"
#include "pb/C2Gate.pb.h"
#include "pb/C2Gate.pb.h"
#include "pb/Msg_Server.pb.h"
#include "pb/Msg_Err.pb.h"

#define SEND_PB_MSG(sender, sessionID, msg) { \
	std::string sdata; \
	if (msg.SerializeToString(&sdata)) \
	{\
		sender->sendMsg(sessionID, decltype(msg)::Id, (char*)sdata.c_str(), sdata.size());\
	}\
	else\
	{\
		LOG(ERROR) << "Serialize Msg '"<< msg.GetTypeName() << "'Failed, File:" << __FILE__ << ", Line:" << __LINE__;\
	}\
}

#define SEND_PB_MSG_EX(sender, sessionID, msgID, msg) { \
	std::string sdata; \
	if (msg.SerializeToString(&sdata)) \
	{\
		sender->sendMsg(sessionID, msgID, (char*)sdata.c_str(), sdata.size());\
	}\
	else\
	{\
		LOG(ERROR) << "Serialize Msg '"<< msg.GetTypeName() << "'Failed, File:" << __FILE__ << ", Line:" << __LINE__;\
	}\
}

#define SEND_PB_MSG_NO_SESSION(sender, msg) { \
	std::string sdata; \
	if (msg.SerializeToString(&sdata)) \
	{\
		sender->sendMsg(decltype(msg)::Id, (char*)sdata.c_str(), sdata.size());\
	}\
	else\
	{\
		LOG(ERROR) << "Serialize Msg '"<< msg.GetTypeName() << "'Failed, File:" << __FILE__ << ", Line:" << __LINE__;\
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


#define ON_PB_MSG_CLASS_CALL(pNoticeCenter, msgType, funcName) pNoticeCenter->addListener(this, StringUtils::msgKey(msgType::Id), [=](uint32_t sessionID, char* data, uint32_t len) {\
	##msgType msg;\
	PARSE_PB_MSG_RETURN(msg, data, len);\
	this->##funcName(sessionID, msg);\
	})

