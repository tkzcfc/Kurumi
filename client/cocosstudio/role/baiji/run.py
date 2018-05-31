#!/usr/bin/python  
#-*-coding:utf-8-*-  
#!python     
import os,sys  
from xml.etree import ElementTree    
from PIL import Image    
   
#匹配字符串末尾是包含某个字符串    
def endWith(s,*endstring):  
    # endswith()匹配字符串的开头或末尾是否包含一个字符串。匹配开头是startswith()  
    # map()是 Python 内置的高阶函数，它接收一个函数 f 和一个 list，并通过把函数 f 依次作用在 list 的每个元素上，得到一个新的 list 并返回。     
    array = map(s.endswith,endstring)     
    if True in array:     
        return True     
    else:     
        return False     
        
# Get the all files & directories in the specified directory (path).     
def get_recursive_file_list(path):  
    current_files = os.listdir(path)    
    all_files = []     
    for file_name in current_files:     
        full_file_name = os.path.join(path, file_name)    
        if endWith(full_file_name,'.plist'):     
            full_file_name = full_file_name.replace('.plist','')    
            # append() 方法向列表的尾部添加一个新的元素。只接受一个参数。  
            all_files.append(full_file_name)     
     
        if os.path.isdir(full_file_name):     
            next_level_files = get_recursive_file_list(full_file_name)     
            # extend()方法只接受一个列表作为参数，并将该参数的每个元素都添加到原有的列表中。  
            all_files.extend(next_level_files)    
    return all_files    
        
def tree_to_dict(tree):    
    d = {}    
    #enumerate会将数组或列表组成一个索引序列。使我们再获取索引和索引内容的时候更加方便  
    for index, item in enumerate(tree):    
        if item.tag == 'key':    
            if tree[index+1].tag == 'string':    
                d[item.text] = tree[index + 1].text    
            elif tree[index + 1].tag == 'true':    
                d[item.text] = True    
            elif tree[index + 1].tag == 'false':    
                d[item.text] = False    
            elif tree[index+1].tag == 'dict':    
                d[item.text] = tree_to_dict(tree[index+1])    
    return d    
    
def gen_png_from_plist(plist_filename, png_filename):    
    file_path = plist_filename.replace('.plist', '') #这样做是为了顺便创建一个文件夹   
    # 判断是否为目录  
    if not os.path.isdir(file_path):    
        os.mkdir(file_path) #创建目录  
  
    big_image = Image.open(png_filename)  #打开图片，获取句柄  
    #解析节点  
    root = ElementTree.fromstring(open(plist_filename, 'r').read())    
    plist_dict = tree_to_dict(root[0])    
    to_list = lambda x: x.replace('{','').replace('}','').split(',')    
    for k,v in plist_dict['frames'].items():    
        rectlist = to_list(v['frame'])    
        # 嗯，不是很懂这样的写法，所以用and or写了  
        # width = int( rectlist[3] if v['rotated'] else rectlist[2] )    
        # height = int( rectlist[2] if v['rotated'] else rectlist[3] )    
        width = int(v['rotated'] and rectlist[3] or rectlist[2])  
        height = int(v['rotated'] and rectlist[2] or rectlist[3])  
        box=(     
            int(rectlist[0]),    
            int(rectlist[1]),    
            int(rectlist[0]) + width,    
            int(rectlist[1]) + height,    
        )      
        rect_on_big = big_image.crop(box)  #裁剪图片，并获取句柄region   
        # 这个旋转之后很奇怪，只有中间部分图片，其他的都是空白，不知道是什么原因  
        # if v['rotated']:    
        #     rect_on_big = rect_on_big.rotate(90)    
    
        # 创建一个新的图片  
        sizelist = [width, height]  
        result_image = Image.new('RGBA', sizelist, (0,0,0,0))    
        result_box=(0, 0, width, height)  
  
        result_image.paste(rect_on_big, result_box, mask = 0)   
        # 图片旋转  
        if v['rotated']:  
            # result_image = result_image.rotated(90) 没有这个方法？？  
            result_image =result_image.transpose(Image.ROTATE_90)  
  
        # 文件路径修改  
        testPath = file_path.replace("\\", "/")   
        position = k.find("/")  #这里还有一个文件夹  
        if position != -1:  
            catalogue = testPath + "/" + k[0:position]  
            if not os.path.isdir(catalogue):  
                os.mkdir(catalogue)  
        outfile = (testPath+'/' + k).replace('gift_', '')    
        print outfile, "generated"    
        result_image.save(outfile)    
    
if __name__ == '__main__':   
    currtenPath = os.getcwd()   #该函数不需要传递参数，它返回当前工作目录  
    allPlistArray = get_recursive_file_list(currtenPath)    
    print allPlistArray     #数组可以直接输出的  
    for plist in allPlistArray:    
        filename = plist    
        plist_filename = filename + '.plist'    
        png_filename = filename + '.png'    
        if (os.path.exists(plist_filename) and os.path.exists(png_filename)):    
            gen_png_from_plist( plist_filename, png_filename )    
        else:    
            print "make sure you have boith plist and png files in the same directory"   