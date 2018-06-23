#include "File.h"
#include "Folder.h"
#include "helpFunctions.h"
#include <unistd.h>

int main()
{
	Folder* root = new Folder("V");
	Folder* currantFolder = root;
	Folder *srchFolder;
	Folder *srchFolder1;

	File* srchFile;

	string action,fileName="",path,destinationPath,destinationFileName;
	int num;
	char c;
	size_t pos;

	pair<int,char> p;

	do
	{
		//cout << currantFolder->getPath() << currantFolder->getFolderName()+"/: ";
		cin >> action; //get action
		getline(cin,fileName); //get the rest of the line.
		if(fileName!="")
			fileName = fileName.substr(1); //delete space from start.
		try{
			switch(hashFunction(action))
			{
			case READ: //read specific char from text file.
				getPathAndFileName(path, fileName);
				srchFolder = currantFolder->findFolder(path);
				pos = fileName.find(" ");
				num = mySTOI(fileName.substr(pos+1, fileName.length())); //change number from string to int
				fileName = fileName.substr(0, pos);
				srchFile = srchFolder->findFile(fileName); //search the file
				cout <<(*srchFile)[num] << endl; //print char from the index "num"
				break;
			case WRITE: //write specific char to text file.
				getPathAndFileName(path, fileName);
				srchFolder = currantFolder->findFolder(path);
				pos = fileName.find(" ");
				action = fileName.substr(pos+1, fileName.length());
				fileName = fileName.substr(0, pos);
				pos = action.find(" ");
				num = mySTOI(action.substr(0, pos));
				c = action.at(pos+1);
				srchFile = srchFolder->findFile(fileName);
				p.first = num;
				p.second = c;
				(*srchFile)[p];
				break;
			case TOUCH: //update time signture if file exists, else open the file.
				getPathAndFileName(path, fileName);
				try{
					srchFolder = currantFolder->findFolder(path);
					srchFile = srchFolder->findFile(fileName);
					srchFile->touch();
				}
				catch(PathIsNotExistsException& e)
				{
					cerr << e.what();
				}
				catch(FileNotFoundExcaption& e)
				{
					srchFolder->createFile(fileName);
				}
				break;
			case COPY:
				pos = fileName.find_last_of(" ");
				destinationFileName = fileName.substr(pos+1, fileName.length());
				fileName = fileName.substr(0, pos);
				getPathAndFileName(path, fileName);
				getPathAndFileName(destinationPath, destinationFileName);
				srchFolder = currantFolder->findFolder(path);
				srchFolder1 = currantFolder->findFolder(destinationPath);
				srchFile = srchFolder->findFile(fileName);
				srchFolder1->addFile(srchFile->copy(destinationFileName));
				break;
			case MOVE:
				pos = fileName.find_last_of(" ");
				destinationFileName = fileName.substr(pos+1, fileName.length());
				fileName = fileName.substr(0, pos);
				getPathAndFileName(path, fileName);
				if(destinationFileName[destinationFileName.length()-1]!='/')
					destinationFileName.append("//");
				getPathAndFileName(destinationPath, destinationFileName);
				srchFolder = currantFolder->findFolder(path);
				srchFolder1 = currantFolder->findFolder(destinationPath);
				srchFile = srchFolder->findFile(fileName);
				srchFolder1->addFile(srchFile);
				srchFolder->eraseFile(fileName);
				break;
			case REMOVE:
				getPathAndFileName(path, fileName);
				srchFolder = currantFolder->findFolder(path);
				srchFile = srchFolder->findFile(fileName);
				srchFolder->eraseFile(fileName);
				srchFile->remove();
				break;
			case CAT:
				getPathAndFileName(path, fileName);
				srchFolder = currantFolder->findFolder(path);
				srchFile = srchFolder->findFile(fileName);
				srchFile->cat();
				break;
			case WC:
				getPathAndFileName(path, fileName);
				srchFolder = currantFolder->findFolder(path);
				srchFile = srchFolder->findFile(fileName);
				srchFile->wc();
				break;
			case LN:
				pos = fileName.find_last_of(" ");
				destinationFileName = fileName.substr(pos+1, fileName.length());
				fileName = fileName.substr(0, pos);
				getPathAndFileName(path, fileName);
				getPathAndFileName(destinationPath, destinationFileName);
				srchFolder = currantFolder->findFolder(path);
				srchFolder1 = currantFolder->findFolder(destinationPath);
				srchFile = srchFolder->findFile(fileName);
				srchFolder1->addFile(srchFile->ln(destinationFileName));
				break;
			case MKDIR:
				getPathAndFileName(path, fileName);
				srchFolder = currantFolder->findFolder(path);
				srchFolder->mkdir(fileName);
				break;
			case CHDIR:
				srchFolder = currantFolder->findFolder(path);
				path = fileName;
				c = path[path.length()-1];
				if(c!='/')
					path.append("/");
				destinationFileName = root->getFolderName()+"/";
				if(strcmp(path.substr(0, 2).c_str(),destinationFileName.c_str())==0)
					currantFolder = root->chdir(path);
				else
					currantFolder = currantFolder->chdir(path);
				break;
			case RMDIR:
				num = fileName.length();
				if(fileName[num-1]=='/')
					fileName = fileName.substr(0, num-1);
				if(fileName==root->getFolderName())
				{
					cout << "Cannot delete main folder." << endl;
					break;
				}
				getPathAndFileName(path, fileName);
				srchFolder = currantFolder->findFolder(path);
				srchFolder->rmdir(fileName);
				break;
			case LS:
				if(currantFolder->printFolders()+currantFolder->printFiles()>0)
					cout << endl;
				break;
			case LPROOT:
				root->lproot();
				break;
			case PWD:
				cout << currantFolder->getPath() << currantFolder->getFolderName()+"/" << endl;
				break;
			case EXIT:
				break;
			default:
				cerr << "wrong action." << endl;
				cout << "Possible actions: read, write, touch, copy, ";
				cout << "remove, move, cat, wc, ln, mkdir, chdir, rmdir, ls, lproot, pwd, exit" << endl;
			}
		}
		catch (exception& e) {
			cerr << e.what();
		}
		fileName="";
	}
	while(action!="exit");

	return 0;
}
