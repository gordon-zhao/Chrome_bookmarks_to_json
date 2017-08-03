# Chrome bookmarks to json
Convert exported chrome bookmarks to JSON

## Usage
  * python html2json.py path_to_bookmark.html path_to_save_json.json
  * (Add sudo if writting to a path that needs root permissions)
  * Or python html2json.py, enter the path to exported bookmark, then enter the path for saving the json file
  
## Known Issue
  Because Chrome does not count "Other bookmarks" as a bookmark folder in the exported html file, the folders under "Other bookmarks" will be under "Bookmarks" folder
  
## Json Structure:
  * "Bookmarks":
      * {
          * \["Folder A"]: {"Folder A_A":{}, "link":'[[bookmark_name, bookmark_link]]'}
          * \["Folder B"]: {"Folder B_A":{}, "link":'[[bookmark_name, bookmark_link]]'}
          * "link":[[bookmark_name, bookmark_link]]
      * }
