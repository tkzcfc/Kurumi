#pragma once

#include "cocos2d.h"
USING_NS_CC;


class GTools
{
public:
	// 判断节点是否被点击
	static bool isInRect(Node* InNode, float InX, float InY);

	// a/b/c/d.txt -> d.txt
	static std::string getBasename(const std::string& path);

	// 解压文件(阻塞)
	static bool decompressZip(const std::string &zip, const std::string outDir, std::string& errorStr, void(*percentCall)(int, int, void*) = NULL, void* data = NULL);

	// 异步解压文件
	static void decompressZipAsync(const std::string& zip, const std::string outDir, bool removeFile, const std::function<void(bool, std::string)>& result, const std::function<void(int, int)>& percent = nullptr);

	// 删除文件
	static bool removeFile(const std::string& filepath);

	// 复制文件
	static bool copyFile(const std::string& filepath, const std::string& newFilepath);

	// 递归更改粒子类型
	static void changeParticleSystemPositionType(Node* root, int type);

	// bit操作相关
	static uint32_t U32_OR(uint32_t src, uint32_t dst);
	static uint32_t U32_AND(uint32_t src, uint32_t dst);
	static uint32_t U32_BIT_SET(uint32_t b, uint32_t flag);
	static uint32_t U32_BIT_GET(uint32_t b, uint32_t flag);
	static uint32_t U32_BIT_REMOVE(uint32_t b, uint32_t flag);
	static bool U32_BIT_EQUAL(uint32_t b, uint32_t flag);
	static bool U32_BIT_NO_EQUAL(uint32_t b, uint32_t flag);
	static uint32_t U32_L_SHIFT(uint32_t src, uint32_t move);
};