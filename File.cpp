/*
 * File.cpp
 *
 *  Created on: 12 באפר׳ 2018
 *      Author: Omer
 */

#include "File.h"

File::~File() {
	if(--value->refCount==0)
		delete value;
}

File& File::operator =(const File& otherFile) {
	if(value == otherFile.value)
		return *this;

	if(--value->refCount == 0)
		delete value;

	value = otherFile.value;
	++value->refCount;

	return *this;
}

/*
 * read char from text file in position i given.
 */
const char File::operator [](fstream::pos_type i) const throw(OutOfLimitException){
	if(i > value->fileLength || i<0)
		throw OutOfLimitException();
	char c;
	value->file->open(value->fileName, ios::in);
	value->file->seekg(i);
	value->file->read(&c,1);
	value->file->close();
	return c;
}

/*
 * write char to file in a specific position given.
 */
void File::operator [](pair<size_t,char> posVal) {
	char text[value->fileLength];
	if(posVal.first > value->fileLength)
		throw OutOfLimitException();
	if(posVal.first<value->fileLength) //update already exists char
	{
		value->file->open(value->fileName, ios::in);
		value->file->seekg(0,ios::beg);
		value->file->read(text,value->fileLength); //read file to temorary string
		value->file->close();
		value->file->open(value->fileName, ios::out);
		text[posVal.first]=posVal.second;		//update string
		value->file->write(text, value->fileLength); //write it back to text file
	}
	else
	{
		value->file->open(value->fileName, ios::app); //append char to the end of file.
		*value->file << posVal.second;
		value->file->write(posVal.second.c_str(), 1);
		value->fileLength++; //update file length.
	}
	value->file->close();
}

/*
 * Function update time signeture to the text file
 */
void File::touch(){
	value->file->open(value->fileName); //update time signeture.
	value->file->close();
}

/*
 * function copy an exsisting file to other file name given.
 */
File* File::copy(string targetFile) throw(WriteToFileException){
	fstream* ofs = new fstream(targetFile, ios::out);
	char buff[value->fileLength];
	value->file->open(value->fileName, ios::in);
	value->file->seekg(0);
	value->file->read(buff,value->fileLength); //read text from file
	value->file->close();
	ofs->write(buff, value->fileLength); //write text to target file
	File* nwFile = new File(targetFile,*ofs); //create new files
	ofs->close();
	return nwFile;
}

/*
 * function remove file.
 */
void File::remove() {
	delete this;
}

/*
 * function move file to other location by copy file text
 * and delete the currant.
 */
bool File::move(string targetFile) {
	copy(targetFile);
	remove();
	return true;
}

/*
 * function display content of text file to the console
 */
void File::cat() const {
	string line;
	value->file->seekg(0);
	value->file->open(value->fileName, ios::in);
	while(getline(*(value->file),line)) //print line by line from text
		cout << line << endl;
	value->file->close();
}

/*
 * function count how many lines, words and chars
 * in text file and print it.
 */
void File::wc() const {
	int lineCounter=0;
	int wordCounter=0;
	string line;
	value->file->open(value->fileName,ios::in);
	value->file->seekg(0);
	while(getline(*(value->file),line))
	{
		for(size_t i=0;i<line.length();i++)
		{
			if(isspace(line[i]))
				wordCounter++;
		}
		wordCounter++;
		lineCounter++;
	}
	cout << lineCounter <<" "<<wordCounter<<" "<< value->fileLength<<" "<< value->fileName << endl;
	value->file->close();
}

/*
 * function create hard link to target file
 */
File* File::ln(string targetFile) const {
	File* nwFile = new File(*this);
	nwFile->setMyFileName(targetFile); //the only difference between the files.
	return nwFile;
}
