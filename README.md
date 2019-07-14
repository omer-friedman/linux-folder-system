# Mini-Terminal
## virtual hierarchical folder and file system that supports actions as listed below
the terminal allows user to create, edit add and remove files and folders in a virtual hierarchical space. the files are the only object actually created and are held in the folder where the program is ran.  

### supported actions:
* ```read <file-name> <position>```*returns character at given position*
* ```write <file-name> <position> <character>``` *writes character to given position*
* ```touch <file-name>```   *creates file*
* ```copy <source-file-name> <target-file-name>``` *copies file*
* ```remove <file-name>``` *removes file*
* ```move <source-file-name> <target-file-name>``` *moves file from source to target*
* ```cat <file-name>``` *prints file content to standard output stream*
* ```wc <file-name>```  *prints word, character and line count in file to standard output stream*
* ```ln <target-file-name> <link-name>``` *hard links given file to new name*
* ```mkdir <folder-name>``` *create directory*
* ```rmdir <folder-name>``` *remove directory*
* ```ls <folder-name>```    *list folders and files in folder*
* ```lproot```  *show all folders and files hierarchical build*
* ```pwd``` *prints folders path from home directory to standard output stream*
* ```--help```  *prints command options to standard output stream*
* ```exit```  *exits program*

## example
```
 Type --help to view commands
 omerfr@miniterminal:~/V$ touch foo.dat
 omerfr@miniterminal:~/V$ write foo.dat 0 a                        
 omerfr@miniterminal:~/V$ read foo.dat 0               
 a
 omerfr@miniterminal:~/V$ copy foo.dat bar.txt
 omerfr@miniterminal:~/V$ ls .
 foo.dat
 bar.txt
 omerfr@miniterminal:~/V$ remove foo.dat      
 omerfr@miniterminal:~/V$ ls .
 bar.txt
 omerfr@miniterminal:~/V$ mkdir MyFolder
 omerfr@miniterminal:~/V$ move bar.txt MyFolder
 omerfr@miniterminal:~/V$ chdir MyFolder
 omerfr@miniterminal:~/V/MyFolder$ pwd
 V/MyFolder/
 omerfr@miniterminal:~/V/MyFolder$ exit 
```
