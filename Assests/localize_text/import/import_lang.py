import csv
import os
import re


def write_file_in_folder(file_name, folder_name, data):
    file_path = os.path.join(folder_name, file_name)

    file_write = open(file_path, 'w')
    file_write.write(data)
    file_write.close()


def find_last_not_of(str_source, text):
    source_len = len(str_source)
    str_len = len(text)
    if str_len > source_len:
        return -1

    i = source_len - 1
    while i >= 0:
        result = False
        for k in range(0, str_len, 1):
            if text[k] == str_source[i]:
                result = True
                break
        if result:
            i -= 1
        else:
            return i
    return -1


def find_first_not_of(str_source, text):
    source_len = len(str_source)
    str_len = len(text)
    i = 0
    while i < source_len - 1:
        result = False
        for k in range(0, str_len, 1):
            if text[k] == str_source[i]:
                result = True
                break
        if result:
            i += 1
        else:
            return i

    return -1


def import_to_lang(list_file, out_file):

    list_data = {}
    list_key = []
    for i in range(0, len(list_file), 1):

        with open(list_file[i]) as f:
            content = f.read().splitlines()
            for line in content:
                if line.find('/*') == -1 and line.find('//') == -1 and line.find('*/') == -1:
                    valid_pos = line.find('=', 0)
                    if valid_pos != -1:
                        key_str = line[0:valid_pos - 1]
                        sub_str = line[valid_pos + 1:len(line) - 1]

                        pos = find_first_not_of(key_str, ' \t')
                        if pos > -1:
                           key_str = key_str[pos:]

                        pos = find_last_not_of(key_str, ' \t')
                        if pos > -1:
                           key_str = key_str[:pos + 1]

                        pos = find_first_not_of(sub_str, ' \t')
                        sub_str = sub_str[pos:]
                        pos = find_last_not_of(sub_str, ' \t')
                        sub_str = sub_str[:pos + 1]

                        pos = find_first_not_of(sub_str, '\"')
                        sub_str = sub_str[pos:]

                        position = find_last_not_of(sub_str, '\"') + 1
                        sub_str = sub_str[:position]

                        if list_data.has_key(key_str):
                            data = list_data[key_str]
                        else:
                            data = []
                            list_data[key_str] = data
                        if len(data) <= i:
                            data.append(sub_str)
                        else:
                            data[i] = sub_str
                        if i == 0:
                            list_key.append(key_str)
    list_export = []
    header_row = ['Key']
    for name in list_file:
        base_name = os.path.basename(name)
        header_row.append(base_name)
    list_export.append(header_row)
    for name in list_key:
        row_data = []
        row_data.append(name)
        for element in list_data[name]:
            row_data.append(element)
        list_export.append(row_data)

    with open('lang.csv', 'wb') as f:
        writer = csv.writer(f)
        for row in list_export:
            writer.writerow(row)

list_file = ['Localized_vn', 'Localized_en', 'Localized_indo']
import_to_lang(list_file, '')