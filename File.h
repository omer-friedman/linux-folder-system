/*
 * File.h
 *
 *  Created on: 10 באפר׳ 2018
 *      Author: omerfri1
 */

#ifndef FILE_H_
#define FILE_H_
#include <cstring>
#include <iostream>
#include <time.h>
#include "Exceptions.h"
#include <fstream>

class File {
public:
	File(string fileName, fstream& nwFile):value(new fileValue(fileName,nwFile)),myFileName(fileName){};
	File(const File& nwFile):value(nwFile.value){++value->refCount;};
	~File();
	const char operator[](fstream::pos_type) const throw(OutOfLimitException);
	File& operator=(const File&);
	void operator[](pair<size_t,char>);
	void touch();
	File* copy(string targetFile) throw(WriteToFileException);
	string operator*() const{return myFileName;}
	void remove();
	bool move(string targetFile);
	void cat() const;
	void wc() const;
	File* ln(string) const;
	fstream* getStream() const{return value->file;}
	string getFileName() const{return value->fileName;}
	size_t getFileLength() const{return value->fileLength;}
	int getRefCount() const{return value->refCount;}
	void setMyFileName(string mfName){myFileName=mfName;}

private:
	struct fileValue{
		int refCount;
		fstream* file;
		string fileName;	//text file itself
		size_t fileLength;
		fileValue(string fName,fstream& nwFile):refCount(1),file(&nwFile),fileName(fName),fileLength(0){};
		~fileValue(){
			file->close();
			delete file;
		}
	};
	fileValue* value;
	string myFileName; 		//MyFile name (how it display in the folder system)
};

#endif /* FILE_H_ */
