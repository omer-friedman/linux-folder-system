/*
 * Folder.h
 *
 *  Created on: 13 באפר׳ 2018
 *      Author: Omer
 */

#ifndef FOLDER_H_
#define FOLDER_H_

#include "Exceptions.h"
#include "File.h"
#include <vector>

class Folder {
public:
	Folder(string folderName,string foldPath=""):name(folderName),path(foldPath){};
	Folder(const Folder& rhs){*this=rhs;}
	Folder& operator=(const Folder&);
	virtual ~Folder();
	void mkdir(string) throw(FolderAlradyExistsExcaption);
	Folder* chdir(string) throw(PathIsNotExistsException);
	bool rmdir(string) throw(PathIsNotExistsException);
	string operator*() const{return name;}
	void ls();
	void lproot();
	Folder* findFolder(string) throw(PathIsNotExistsException);
	File* findFile(string) throw(FileNotFoundExcaption);
	File& createFile(string);
	string eraseCurrantFolderFromPath(string) const;
	bool printFolders();
	bool printFiles();
	string getFolderName() const{return name;}
	string getPath() const{return path;}
	void eraseFile(string);
	void addFile(File*);

	private:
	void recTreePrint(string);
	vector<File*> files;
	vector<Folder*> folders;
	string name;
	string path;
};
#endif /* FOLDER_H_ */
