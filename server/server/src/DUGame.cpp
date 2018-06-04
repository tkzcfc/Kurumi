#include "DUGame.h"

#define GLOG_NO_ABBREVIATED_SEVERITIES 
#include "glog/logging.h"


BOOL StringToWString(const std::string &str, std::wstring &wstr)
{
	int nLen = (int)str.length();
	wstr.resize(nLen, L' ');

	int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

	if (nResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}
//wstring高字节不为0，返回FALSE
BOOL WStringToString(const std::wstring &wstr, std::string &str)
{
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');

	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);

	if (nResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}

DUGame* DUGame::instance = NULL;

DUGame::DUGame()
{
	m_lastUpdate = std::chrono::steady_clock::now();
	m_nextDeltaTimeZero = true;
	m_deltaTime = 0.0f;

	m_animationInterval.QuadPart = 0;
	setInterval(1 / 40.0f);
	m_scheduler = DUScheduler::getInstance();

	m_luaState = luaL_newstate();

	initGLog();
}

DUGame::~DUGame()
{
	google::ShutdownGoogleLogging();
	lua_close(m_luaState);
}

DUGame* DUGame::getInstance()
{
	if (instance == NULL)
	{
		instance = new DUGame();
	}
	return instance;
}

void DUGame::destroy()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

void DUGame::initGLog()
{
	wchar_t szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);//得到应用程序的全路径   

	std::wstring path = szPath;
	auto pos = path.find_last_of(L"\\");
	std::wstring curPath = path.substr(0, pos);

	curPath.append(L"\\log");

	DWORD dwAttrib = GetFileAttributes(curPath.c_str());
	bool isDirExist = INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

	if (!isDirExist)
	{
		CreateDirectory(curPath.c_str(), NULL);
	}

	std::string str;
	WStringToString(curPath, str);

	FLAGS_log_dir = str;
	//日志实时输出   
	FLAGS_logbufsecs = 0;
	//最大日志文件大小 10M  
	FLAGS_max_log_size = 10;
	//输出到控制台
	FLAGS_alsologtostderr = true;
	google::InitGoogleLogging("gamelog");
}

bool DUGame::isFileExist(const char* filename)
{
	if (filename == NULL || strlen(filename) <= 0)
		return false;
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		return false;
	}
	fclose(fp);
	return true;
}

void DUGame::setInterval(float interval)
{
	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	m_animationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

void DUGame::run()
{
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceCounter(&nLast);
	
	while (true)
	{
		QueryPerformanceCounter(&nNow);
		if (nNow.QuadPart - nLast.QuadPart > m_animationInterval.QuadPart)
		{
			nLast.QuadPart = nNow.QuadPart - (nNow.QuadPart % m_animationInterval.QuadPart);
			this->mainLoop();
		}
		else
		{
			Sleep(1);
		}
	}
}

void DUGame::mainLoop()
{
	calculateDeltaTime();
	m_scheduler->update(m_deltaTime);
}

void DUGame::calculateDeltaTime()
{
	auto now = std::chrono::steady_clock::now();

	if (m_nextDeltaTimeZero)
	{
		m_deltaTime = 0;
		m_nextDeltaTimeZero = false;
	}
	else
	{
		m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - m_lastUpdate).count() / 1000000.0f;
		m_deltaTime = DU_MAX(0, m_deltaTime);
	}

	m_lastUpdate = now;
}

