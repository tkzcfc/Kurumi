#pragma once

#include "GLibBase.h"
#include "GameProto.h"

// 账号服务

class GAccountMgrService : public GIService
{
public:

	G_DEFINE_SERVICE(GAccountMgrService);

	virtual uint32_t onInit() override;
	
public:

	bool contain(const std::string& user);

	bool containAccount(const std::string& account);

	int32_t createAccount(const std::string& user, const std::string& pwd, int32_t platform);
	
	err::Code getAccount(const std::string& user, const std::string& pwd, std::string& outAccount);

protected:

	bool readAccount();

private:

	csqliter* m_sqliter;

	struct AccountInfo
	{
		std::string username;
		std::string password;
		std::string account;
		int32_t lastSvr;
	};
	std::vector<AccountInfo> m_allAcountInfo;
};
