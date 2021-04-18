# -*- coding: UTF-8 -*- 
import os
import os.path
import sys
import shutil
import re
import traceback

def filter(file):
	# 忽略文件列表
	ignoreList = [
		"Msg_Server.proto"
	]
	for v in ignoreList:
		if v == file:
			return False
	return True


def writeFile(filePath, content):
	fo = open(filePath, "wb")
	fo.write(content)
	fo.close()

def readFile(filePath):
	fo = open(filePath, "rb")
	content = fo.read()
	fo.close()
	return content


def clearLine(line):
	line = line.replace('\t', '')
	line = line.replace(' ', '')
	line = line.replace('\r\n', '')
	line = line.replace('\r', '')
	line = line.replace('\n', '')
	return line


# 获取消息ID映射
def getMsgIdMap(filePath):
	dic = {}
	cfg = open(filePath)

	pattern = re.compile(r'(\w+)=(\d+)')

	line = cfg.readline()
	while line:
		line = clearLine(line)

		if len(line) > 2 and line[0:2] != "//":
			result = pattern.findall(line)
			if len(result) == 1 and len(result[0]) == 2:
				info = result[0]
				dic[info[0]] = info[1]
		line = cfg.readline()  
	cfg.close()
	return dic

# 获取所有消息
def getMsgMap(root, fileList):
	dic = {}

	pkgPattern = re.compile(r'\s*package\s+(\w+);')
	msgPattern = re.compile(r'\s*message\s+(\w+)')

	for name in fileList:
		fullpath = root + name
		content = readFile(fullpath)

		# 查找package
		pkgName = ""
		pkgR = pkgPattern.findall(content)
		if len(pkgR) >= 1:
			pkgName = pkgR[0] + "."
		# 查找message
		msgR = msgPattern.findall(content)
		
		for msg in msgR:
			dic[pkgName + msg] = name
	return dic

def getCmd(filePath, allMsgDict, allMsgIdDict):
	dic = {}

	# re.MULTILINE 启用多行匹配
	# 每行以\s*开头才算合法
	pattern = re.compile(r'^\s*(\w+)\s*=\s*([\w\.]+)', flags = re.MULTILINE)
	content = readFile(filePath)
	result = pattern.findall(content)
	for info in result:
		msgId 	= info[0]
		msgName = info[1]

		if not allMsgIdDict.has_key(msgId):
			print("invalid msgId '{0}'".format(msgId))
			continue
		if not allMsgDict.has_key(msgName):
			print("invalid msg '{0}'".format(msgName))
			continue
		dic[allMsgIdDict[msgId]] = msgName
	return dic

def proto2pb(name):
	return name[:-6] + '.pb'

def dictKey(dic, value):
	for key in dic:
		if dic[key] == value:
			return key

def publishPbc(path, targetDir):
	exePath 	= path + "\\proto_tool\\protoc.exe" 
	outPath 	= path + "\\pb\\"
	protoPath 	= path + '\\proto\\'

	# 清除之前的输出目录
	if os.path.exists(outPath):
		shutil.rmtree(outPath)
	os.makedirs(outPath)

	# 获取所有proto文件
	fileList = []
	for file in os.listdir(protoPath):
		if file.endswith("proto") and filter(file):
			fileList.insert(0, file)

	# 所有消息
	allMsgDict = getMsgMap(protoPath, fileList)
	# 所有消息ID
	allMsgIdDict = getMsgIdMap(protoPath + "Msg_ID.proto")
	# 通过cmd.cfg文件读取相应的消息映射
	cmdDict = getCmd(protoPath + "cmd.cfg", allMsgDict, allMsgIdDict)

	# 导出pb文件
	for name in fileList:
		outName		= outPath + proto2pb(name)
		protoName 	= protoPath + name

		cmd = "{0} -I {1} --descriptor_set_out {2} {3}".format(exePath, protoPath, outName, protoName)
		os.system(cmd)

	# 清单文件写入
	manifestFile = "local M = {}\n"


	# cmd
	manifestFile = manifestFile + "M.CMD = {\n"

	for msgId in cmdDict:
		pbMsg 	= cmdDict[msgId]
		pbFile 	= proto2pb(allMsgDict[pbMsg])
		msgName	= dictKey(allMsgIdDict, msgId)

		line = "\t[{0}] = {{file = '{1}', name = '{2}', msg = '{3}'}},\n".format(msgId, pbFile, msgName, pbMsg)
		manifestFile = manifestFile + line
	
	manifestFile = manifestFile + "}\n"

	# pb list
	manifestFile = manifestFile + "M.pb = {\n"

	for name in fileList:
		name = proto2pb(name)
		manifestFile = manifestFile + "\t'{0}',\n".format(name)

	manifestFile = manifestFile + "}\n"

	manifestFile = manifestFile + "\n"
	manifestFile = manifestFile + "if cc then\n"
	manifestFile = manifestFile + "    cc.exports.MessageID = {}\n"
	manifestFile = manifestFile + "else\n"
	manifestFile = manifestFile + "    MessageID = {}\n"
	manifestFile = manifestFile + "end\n"
	manifestFile = manifestFile + "for k, v in pairs(M.CMD) do\n"
	manifestFile = manifestFile + "    MessageID[v.name] = k\n"
	manifestFile = manifestFile + "end\n"
	manifestFile = manifestFile + "\n"
	manifestFile = manifestFile + "return M"
	
	# 清单文件写入
	writeFile(outPath + "manifest.lua", manifestFile)

	if os.path.exists(targetDir):
		shutil.rmtree(targetDir)
	shutil.copytree(outPath, targetDir)

def run():
	current_path = os.path.abspath(__file__)
	current_path = os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".")
	publishPbc(current_path, current_path + "./../../client/res/pb/")
	
if __name__=='__main__':
	print("    ->start")
	run()
	print("    ->succeed")
	os.system("pause")
