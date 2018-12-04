import csv
import os
g_current_folder = os.path.dirname(__file__)
g_output_folder = os.path.join(g_current_folder, '../res/localize')


def create_folder_if_not_exist(folder):
    if not os.path.exists(folder):
        os.makedirs(folder)


def write_file_in_folder(file_name, folder_name, data):
    file_path = os.path.join(folder_name, file_name)

    file_write = open(file_path, 'w')
    file_write.write(data)
    file_write.close()


def export_to_lang(file_path, out_dir):
    create_folder_if_not_exist(out_dir)
    with open(file_path, 'rb') as f:
        reader = csv.reader(f)
        data = {}
        index = 0
        length = 0
        for row in reader:
            if index == 0:
                header = row
                length = len(header)
                for k in range(1, len(header)):
                    data[header[k]] = ''
                if len(header[len(header)-1]) == 0:
                    length -= 1
            else:
                if row[0].find('//') == -1:
                    print row[0]
                    for i in range(1, length):
                        text = row[i]
                        data[header[i]] = data[header[i]] + row[0] + '    ="' + text + '"\n'
            index += 1
        for i in range(1, length):
            write_file_in_folder(header[i], out_dir, data[header[i]])

export_to_lang('localize_text/lang.csv', g_output_folder)

