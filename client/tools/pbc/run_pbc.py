# -*- coding: UTF-8 -*- 
import os
import sys
import shutil

def proto2pb(name):
	return name[:-6] + '.pb'

def write_data(file_path, data):
    dir_, file_ = os.path.split(file_path)
    if dir_ and not os.path.exists(dir_):
        os.makedirs(dir_)
    fp = open(file_path, "w")
    if not fp:
        print("open file : %s failed" % file_path)
        return None
    fp.write(data)
    fp.close()
    return True

def publishPbc(protoPath, outPath):
	current_path = os.path.abspath(__file__)
	exePath = os.path.abspath(os.path.dirname(current_path) + "\\proto_tool\\protoc.exe")

	# 清除之前的输出目录
	if os.path.exists(outPath):
		shutil.rmtree(outPath)
	os.makedirs(outPath)

	# 获取所有proto文件
	fileList = []
	for file in os.listdir(protoPath):
		if file.endswith("proto"):
			fileList.insert(0, file)

	# 导出pb文件
	for name in fileList:
		outName		= os.path.abspath(outPath + proto2pb(name))
		protoName 	= os.path.join(protoPath, name)

		cmd = "{0} -I {1} -o {2} {3}".format(exePath, protoPath, outName, protoName)
		os.system(cmd)

	# 导出pb列表
	script = "return {\n"
	for name in fileList:
		script = script + "    '{0}',\n".format(proto2pb(name))
	script = script + "}"
	write_data(os.path.join(outPath, "pblist.lua"), script)


def run():
	current_path = os.path.abspath(__file__)
	current_path = os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".")
	temp_dir = current_path + "./pb/"

	proto_path = os.path.abspath(current_path + "/proto/")

	publishPbc(proto_path, temp_dir)

	out_dir = os.path.abspath(os.path.dirname(current_path) + "../../kurumi/src/pb")
	if os.path.exists(out_dir):
		shutil.rmtree(out_dir)
	shutil.copytree(temp_dir, out_dir)
	shutil.rmtree(temp_dir)
	
if __name__=='__main__':
	print("    ->start")
	run()
	print("    ->succeed")
	# os.system("pause")
