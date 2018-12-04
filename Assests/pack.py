import json
import os
import shutil

g_scale = 1
g_max_width = 2048
g_max_height = 2048
g_use_rgba_4444 = False
g_current_folder = os.path.dirname(__file__)
g_texture_output_folder = os.path.join(g_current_folder, '../res/high')
g_common_output_folder = os.path.join(g_current_folder, '../res/common')
g_data_code_folder = os.path.join(g_current_folder, '../src/data')

animation_resource_class_temp = ""
g_list_data = []


class AnimationData:
    def __init__(self):
        self.id = ""
        self.path = ""


def load_template():
    global animation_resource_class_temp
    animation_resource_class_temp = open('temp/ResourceAnimation.temp').read()


def write_file_in_folder(file_name, folder_name, data):
    file_path = os.path.join(folder_name, file_name)
    file_write = open(file_path, 'w')
    file_write.write(data)
    file_write.close()


def create_folder_if_not_exist(folder):
    if not os.path.exists(folder):
        os.makedirs(folder)


def pack_atlas_folder(path):
    base_name = os.path.basename(path)

    if len(base_name) > 5:
        if path[-5:] == '_root':
            file_name_out = base_name[0:-5] + '_{n}'
            print file_name_out
            texturepacker(path, g_texture_output_folder, file_name_out, g_scale, g_max_width, g_max_height, g_use_rgba_4444)
            return
    for name in os.listdir(path):
        file_path = os.path.join(path, name)
        if os.path.isdir(file_path):
                pack_atlas_folder(file_path)


def pack_dragon_bone_folder(folder):
    print "pack_dragon_bone_folder"
    texture_folder = os.path.join(folder, "texture")
    texture_out_folder = os.path.join(g_texture_output_folder, folder)
    texturepacker(texture_folder, texture_out_folder, "texture", g_scale, g_max_width, g_max_height, g_use_rgba_4444)
    skeleton_out_folder = os.path.join(g_common_output_folder, folder)
    create_folder_if_not_exist(skeleton_out_folder)
    shutil.copyfile(os.path.join(folder, "skeleton.xml"), os.path.join(skeleton_out_folder, "skeleton.xml"))


def find_and_pack_dragon_bone(folder):
    if not os.path.isdir(folder):
        return
    global g_list_data
    for folder_child in os.listdir(folder):
        folder_path = os.path.join(folder, folder_child)
        file_xml = os.path.join(folder_path, "skeleton.xml")
        print file_xml
        if os.path.exists(file_xml):
            data = AnimationData()
            data.id = folder_child
            data.path = folder_path.replace('\\', '/')
            g_list_data.append(data)
            pack_dragon_bone_folder(folder_path)
        else:
            find_and_pack_dragon_bone(folder_path)


def write_animation_resource():
    key_data = ""
    path_data = ""
    for data in g_list_data:
        key_data += '\n'
        key_data += data.id
        key_data += ': "'
        key_data += data.id
        key_data += '",'

        path_data += '\n'
        path_data += data.id
        path_data += ': "'
        path_data += data.path
        path_data += '",'

    buf = animation_resource_class_temp
    buf = buf.replace('@list_ani_id@', key_data[:(len(key_data)-1)])
    buf = buf.replace('@list_ani@', path_data[:(len(path_data)-1)])
    print buf
    create_folder_if_not_exist(g_data_code_folder)
    file_out = os.path.join(g_data_code_folder, 'ResourceAnimation.js')
    file_write = open(file_out, 'w')
    file_write.write(buf)
    file_write.close()


def texturepacker(folder_in, folder_out, file_name_out, scale, max_width, max_height, use_rgba_4444):
    cmd = 'texturepacker --border-padding 1 --shape-padding 1 --multipack'
    if use_rgba_4444:
        cmd += '--opt RGBA4444 --dither-fs-alpha '
    cmd = '%s --scale %f --max-width %s --max-height %s' % (cmd, scale, max_width, max_height)
    cmd = '%s --data %s/%s.plist --format cocos2d' % (cmd, folder_out, file_name_out)
    cmd = '%s --sheet %s/%s.png %s' % (cmd, folder_out, file_name_out, folder_in)
    if os.system(cmd) != 0:
        raise Exception("Texture packer " + file_name_out + " fails!")

#------------Main-------------------

#import_skills_from_old('old_heroes', 'test')anh T
#import_time_cast_from_ani('heroes')
load_template()
find_and_pack_dragon_bone("game")
write_animation_resource()
#pack_atlas_folder('pack_root')

#------------test-------------------
   #test_packer()


def test_packer():
    texturepacker("C:\Users\GSN\Desktop/hero_1", 'C:\Users\GSN\Desktop', "abc", 0.5, "2048", "2048", False)