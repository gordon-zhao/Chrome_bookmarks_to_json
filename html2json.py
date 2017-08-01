# coding: utf-8
import json
import sys
import codecs

python3 = False

if sys.version_info[0] == 3:   #Python 3
    python3 = True
if not python3:
    reload(sys)
    sys.setdefaultencoding("utf-8")
    input = raw_input

def parseHTML(file_path):
    fo = codecs.open(file_path, encoding='utf-8', mode='r+')
    original = fo.read()
    fo.close()
    parsed = {}
    current_location = []
    current_location_name = []
    current_index = 0
    header = original.find("<H1>")
    if header > -1:
        ender = original.find("</H1>")
        parsed[original[header+4:ender]] = {"link":[]}
        folder_begin = original.find("<DL><p>")
        if folder_begin > -1:
            current_location.append(parsed[original[header+4:ender]])
            current_location_name.append(original[header+4:ender])
        original = original[folder_begin+7:]

    block = False
    original_length = len(original)

    while current_index+1<original_length:
        folder_title_header = original.find("<DT><H3", current_index)
        folder_title_ender = original.find("</H3>", current_index)
        folder_header = original.find("<DL><p>", current_index)
        folder_ender = original.find("</DL><p>", current_index)
        bookmark_header = original.find("<DT><A", current_index)
        bookmark_ender = original.find("</A>", current_index)

        lists = [folder_title_header,folder_title_ender,folder_header,folder_ender,bookmark_header,bookmark_ender]
        for i in range(6):
            # Prevent the min() choose the not exists value -1
            if lists[i] == -1:
                lists[i] = original_length + 1

        nearest_element = min(lists)

        if lists[3] + 8 >= original_length:   # If the folder end mark plus its length is equal to the raw file length, then escape the loop, in order to prevent the value -1 returned by find() caused the loop go over again
            break

        if nearest_element == folder_title_header and not block:
            if not folder_title_ender > -1 and not  folder_title_header+1 > original_length:
                block = True
                continue
            folder_title_header = original.find(">",folder_title_header+7)
            upper_folder = current_location[-1]
            upper_folder[original[folder_title_header+1:folder_title_ender]] = {"link": []}
            current_location.append(upper_folder[original[folder_title_header+1:folder_title_ender]])
            current_location_name.append(original[folder_title_header+1:folder_title_ender])
            current_index = folder_title_ender + 5
            print("Working on: {}".format("/".join(current_location_name)))
            continue

        if nearest_element == folder_header:
            current_index = folder_header + 7
            continue

        if nearest_element == folder_ender and folder_ender + 8 < original_length:
            current_location.pop()
            current_location_name.pop()
            current_index = folder_ender + 8
            continue

        if nearest_element == bookmark_header:
            link_header = original.find("HREF=", bookmark_header)
            if link_header > -1:
                link_ender = original.find('"', link_header + 6)
                bookmark_title_header = original.find(">", link_header)
                current_location[-1]["link"].append([original[link_header+6:link_ender], original[bookmark_title_header+1:bookmark_ender]])
                current_index = bookmark_ender + 4
            continue
    print("Finished parsing bookmarks!")
    return parsed.copy()


def writeJSON(result, path_to_save=None, indent=4,encoding = "utf-8", mode="w+"):
    if not path_to_save:
        print("JSON saving path not found! Skipping...")
        return 1
    files = codecs.open(path_to_save,encoding=encoding,mode=mode)
    if not python3:
        files.write(json.dumps(result,indent=indent).decode('unicode-escape'))
    elif python3:
        msg = json.dumps(result, indent=indent)
        msg = bytes(msg, 'utf-8')
        files.write(msg.decode('unicode-escape'))
    files.flush()
    files.close()
    print("JSON file written to path: {}".format(path_to_save))


if __name__=="__main__":
    if len(sys.argv)==3:
        args = [sys.argv[1],sys.argv[2]]
    else:
        args = []
        args.append(input("Path to Exported Bookmark: "))
        args.append(input("Export JSON to: "))
    try:
        result = parseHTML(args[0])
        writeJSON(result, args[1])
    except:
        sys.stderr.write(sys.exc_info())
    finally:
        input("Press [Enter] to continue...")




