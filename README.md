# Chrome bookmarks to json
Convert exported chrome bookmarks to JSON made by two **silly** Chinese.

## Perequisites

For Python Version:

- Python 2 or higher installed

For C++ Version

- You hand and your device, nothing else...

## Usage

### Python Version
- Run the following Command:
``python html2json.py path_to_bookmark.html path_to_save_json.json``

 - (Add sudo if writting to a path that needs root permissions)
 - Or ``python html2json.py``, enter the **path to exported bookmark**, then enter the **path for saving the json file**
  
### C++ Version

Use it just like a Linux software, call the program with parameters: 

```
-i or --input-file         Specify source file. i.e. Your bookmark HTML file exported from Google Chrome.
-o or --output-file        Specify output file name. i.e. ToadJiangPlusOneSecond.json
```

### Examples

```
  # Python Version
  python html2json.py chromeBookMark.html ToadJiangPlusOneSecond.json

  # C++ Version
  html2json -i chromeBookMark.html -o ToadJiangPlusOneSecond.json
```


## Known Issue
  In Python Version, because Chrome does not count "Other bookmarks" as a bookmark folder in the exported html file, the folders under "Other bookmarks" will be under "Bookmarks" folder.
  
  But this issue could be solved in C++ version. If you need such a feature, just post a issue in this repo so that we can add it.
  
## Json Structure:

```
"Bookmarks":
	{
		"FolderA": 
			{
			"LINK":'BOOKMARK_NAME'
			}
		"FolderB": 
			{
			"LINK":'BOOKMARK_NAME'
			}
		"LINK": 'BOOKMARK_NAME'
	}
```


## Presents

#### C++ Version    : LBYPatrick
#### Python Version : gordon-zhao

<br>

<h1>最後に、東條希最高!</h1>