/*
 * Folder.cpp
 *
 *  Created on: 13 באפר׳ 2018
 *      Author: Omer
 */

#include "Folder.h"


Folder& Folder::operator =(const Folder& otherFolder) {
	files = otherFolder.files;
	folders = otherFolder.folders;
	name = otherFolder.name;
	path = otherFolder.path;
	return *this;
}


Folder::~Folder() {
	for(vector<File*>::iterator fileIt = files.begin(); fileIt!=files.end(); ++fileIt)
		delete *fileIt;
	for(vector<Folder*>::iterator folderIt = folders.begin(); folderIt!=folders.end(); ++folderIt)
		delete *folderIt;
}

/*
 * Recursive function get path to folder, search the folder in the folder system
 * and return a pointer to it if found, else throws exception.
 */
Folder* Folder::findFolder(string folderName) throw(PathIsNotExistsException) {
	folderName = eraseCurrantFolderFromPath(folderName);
	if(folderName=="/") //tnai atsira
		return this;
	size_t pos = folderName.find("/");
	if(pos!=string::npos) //if "/" found - folderName contains path.
	{
		string currentFolder = folderName.substr(0, pos);
		string otherPath;
		if(pos == folderName.length()-1)
			otherPath = "/";
		else
			otherPath = folderName.substr(pos+1, folderName.length());
		for(vector<Folder*>::iterator it = folders.begin();it!=folders.end();it++)
		{
			if((*it)->name==currentFolder) //folder found -> begin recursive search
				return (*it)->findFolder(otherPath);
		}
	}
	else //if "/" not found - no path and need to search folder in this folder.
	{
		for(vector<Folder*>::iterator it = folders.begin();it!=folders.end();it++)
			if((*it)->name==folderName)
				return *it;
	}
	throw PathIsNotExistsException();
	return NULL;
}

/*
 * Function make a new direction if not exist in the path given. else throw exception.
 */
void Folder::mkdir(string folderName) throw(FolderAlradyExistsExcaption) {
	folderName = eraseCurrantFolderFromPath(folderName);
	string tmpFolderName = folderName;
	char c= tmpFolderName[folderName.length()-1];
	if(c!='/')
		tmpFolderName.append("/"); //add "/" so findFolder can work.
	try{
		findFolder(tmpFolderName);
	}
	catch (PathIsNotExistsException& e) { //happen if folder not found.
		folders.push_back(new Folder(folderName,path+this->name+"/"));
		return;
	}
	throw FolderAlradyExistsExcaption();
}

/*
 * Function get path and change currant working folder.
 */
Folder* Folder::chdir(string path) throw(PathIsNotExistsException){
	Folder* f =  this->findFolder(path);
	return f;
}

/*
 * Function get folder name and remove it from folder system if found. else throw exception.
 */
bool Folder::rmdir(string folderName) throw (PathIsNotExistsException) {
	for(vector<Folder*>::iterator it = folders.begin();it!=folders.end();it++)
		if((*it)->name==folderName)
		{
			delete *it; //delete the folder
			folders.erase(it); //erase folder from folder system.
			return true;
		}
	throw PathIsNotExistsException();
	return false;
}

/*
 * Function display all folders and files in this folder.
 */
void Folder::ls() {
	for(vector<Folder*>::iterator it = folders.begin();it!=folders.end();it++)
		cout << *(**it) <<" ";
	for(vector<File*>::iterator fileIt = files.begin(); fileIt!=files.end(); ++fileIt)
		cout << *(**fileIt) <<" ";
	cout << endl;
}

/*
 * Function call to recursive print for display hierarchy of folders and files.
 */
void Folder::lproot() {
	cout << name << endl;
	string str="\t";
	recTreePrint(str);
}

/*
 * Function search for file in the file system of this folder and return
 * a pointer to it if found, else throw exception.
 */
File* Folder::findFile(string fileName) throw(FileNotFoundExcaption) {
	for(vector<File*>::iterator fileIt = files.begin(); fileIt!=files.end(); ++fileIt)
		if(*(**fileIt)==fileName)
			return *fileIt;
	throw FileNotFoundExcaption();
	return NULL;
}

/*
 * Function create a new file by file name and add it to thee file system of this folder.
 */
File& Folder::createFile(string fileName) {
	fstream* io = new fstream(fileName,ios::out);
	io->close();
	File* nwFile = new File(fileName,*io);
	files.push_back(nwFile);
	return *nwFile;
}

/*
 * Function get path and delete from start the folder name if
 * i'm the folder at the start of the path.
 */
string Folder::eraseCurrantFolderFromPath(string path) const {
	string nwPath;
	size_t pos = path.find("/");
	if(path.substr(0, pos)==name)
	{
		nwPath = path.substr(pos+1,path.length());
		if(nwPath.length()==0)
			return "/";
		return path.substr(pos+1,path.length());
	}
	return path;
}

/*
 * Function print recursivly the content of the folders.
 */
void Folder::recTreePrint(string str) {
	for(vector<Folder*>::iterator it = folders.begin();it!=folders.end();it++)
	{
		cout <<str<< *(**it) << endl;
		(*it)->recTreePrint(str+"\t");
	}
	for(vector<File*>::iterator fileIt = files.begin(); fileIt!=files.end(); ++fileIt)
	{
		cout << str << *(**fileIt) << " -> " <<(*fileIt)->getRefCount() << endl;
	}
}

/*
 * Function print all folders in this folder's folder system.
 */
bool Folder::printFolders() {
	if(!folders.empty())
	{
		for(vector<Folder*>::iterator folderIt = folders.begin(); folderIt!=folders.end(); ++folderIt)
			cout << (*folderIt)->getFolderName() << " ";
		return true;
	}
	return false;
}

/*
 * Function print all files in this folder's file system.
 */
bool Folder::printFiles() {
	if(!files.empty())
	{
		for(vector<File*>::iterator fileIt = files.begin(); fileIt!=files.end(); ++fileIt)
			cout << *(**fileIt) << " ";
		return true;
	}
	return false;
}

/*
 * Function get file name and remve the file from file system if found.
 */
void Folder::eraseFile(string fileName) {
	for(vector<File*>::iterator fileIt = files.begin(); fileIt!=files.end(); ++fileIt)
		if(*(**fileIt)==fileName)
		{
			files.erase(fileIt);
			return;
		}
}

/*
 * Function insert file to the file system.
 */
void Folder::addFile(File* file) {
	files.push_back(file);
}
