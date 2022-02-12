#include "GLogService.h"


// 模板.cpp 

uint32_t GLogService::onInit()
{
	G_CHECK_SERVICE(GHttpService);
	G_CHECK_SERVICE(GConfigService);

	auto appName = GApplication::getInstance()->getAppName();

	auto ini = m_serviceMgr->getService<GConfigService>()->iniReader();
	m_logRoot = ini.Get(appName, "logRoot", "luaLog/");

	m_logRoot = StringUtils::replaceString(m_logRoot, "\\", "/");
	if (m_logRoot.back() != '/')
	{
		m_logRoot.append("/");
	}

	if (!GFileSystem::isDirectoryExist(m_logRoot))
	{
		if (!GFileSystem::createDirectory(m_logRoot))
		{
			LOG(ERROR) << "Failed to create directory: " << m_logRoot;
			return SCODE_START_FAIL_EXIT_APP;
		}
	}

	init_Http();

	return SCODE_START_SUCCESS;
}

void GLogService::init_Http()
{
	auto httpSvice = m_serviceMgr->getService<GHttpService>();

	httpSvice->getPathNoticeCenter()->addListener(this, "/test", [](const net_uv::HttpRequest& request, net_uv::HttpResponse* response)
	{
		response->setStatusCode(net_uv::HttpResponse::k200Ok);

		std::string content;

		content.append(StringUtils::format("method : %s\n", request.methodString()));
		content.append(StringUtils::format("query : %s\n", request.query().c_str()));
		content.append(StringUtils::format("path : %s\n", request.path().c_str()));

		content.append("header:\n");
		for (auto& it : request.headers())
		{
			content.append(StringUtils::format("\t%s : %s\n", it.field.c_str(), it.value.c_str()));
		}

		content.append("params:\n");
		for (auto& it : request.params())
		{
			content.append(StringUtils::format("\t%s : %s\n", it.first.c_str(), it.second.c_str()));
		}

		response->setBody(content);
	});

	httpSvice->noticeCenter(HTTP_POST)->addListener(this, "/lua_err", [=](const net_uv::HttpRequest& request, net_uv::HttpResponse* response)
	{
		response->setStatusCode(net_uv::HttpResponse::k200Ok);
		this->onHttpRequest_LUA_TRACKBACK(request, response);
	});
}

void GLogService::onStopService()
{
	this->stopServiceFinish();

	m_serviceMgr->getService<GHttpService>()->delListener(this);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GLogService::onHttpRequest_LUA_TRACKBACK(const net_uv::HttpRequest& request, net_uv::HttpResponse* response)
{
	std::string user = request.getParam("user", "");
	std::string platform = request.getParam("platform", "");
	std::string err = request.getHeader("err_log");

	if (user.empty())
	{
		user = "ghost";
	}
	if (platform.empty())
	{
		platform = "unknown";
	}

	user = StringUtils::replaceString(user, " ", "_");
	platform = StringUtils::replaceString(platform, " ", "_");

	std::string dirName = m_logRoot + user;

	do
	{
		if (err.empty())
		{
			LOG(ERROR) << "Empty error, user: " << user;
			break;
		}

		// 文件夹创建
		if (!GFileSystem::isDirectoryExist(dirName) && !GFileSystem::createDirectory(dirName))
		{
			LOG(ERROR) << "Failed to create directory: " << dirName;
			break;
		}

		// hash
		SHA1 checksum;
		checksum.update(err);
		const string hash = checksum.final();

		// 当前时间
		time_t t;
		struct tm * lt;
		time(&t);
		lt = localtime(&t);
		auto strTime = StringUtils::format("\n#### %d/%d/%d %d:%d:%d platform:%s\n", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec, platform.c_str());


		std::string fileName = dirName + "/" + hash + ".txt";
		if (GFileSystem::isFileExist(fileName))
		{
			FILE* fp = fopen(fileName.c_str(), "a+");
			if (fp)
			{
				fseek(fp, 0, SEEK_END);
				fwrite(strTime.c_str(), strTime.size(), 1, fp);
				fclose(fp);
			}
		}
		else
		{
#define DECODE_USE_BASE64 1

#if DECODE_USE_BASE64
			auto size = base64::decoded_size(err.size());
			if (size <= 0) break;

			// base64解码
			char* buf = (char*)malloc(size * 2);
			memset(buf, 0, size * 2);

			auto decodeSize = base64::decode(buf, err.c_str(), err.size());
			if (decodeSize.first <= 0)
			{
				LOG(ERROR) << "Decode base64 error, user: " << user;
				LOG(ERROR) << "base64:" << err;
				free(buf);
				break;
			}

			FILE* fp = fopen(fileName.c_str(), "wb");
			if (fp)
			{
				fwrite(buf, decodeSize.first, 1, fp);
				fwrite(strTime.c_str(), strTime.size(), 1, fp);
				fclose(fp);
			}

			free(buf);
#else
			FILE* fp = fopen(fileName.c_str(), "wb");
			if (fp)
			{
				fwrite(err.c_str(), err.size(), 1, fp);
				fwrite(strTime.c_str(), strTime.size(), 1, fp);
				fclose(fp);
			}
#endif
		}
	} while (false);

	response->setBody("{\"code\":0,\"msg\":\"ok\"}");
}

