/*
 * helpFunctions.cpp
 *
 *  Created on: 14 באפר׳ 2018
 *      Author: Omer
 */

#include "helpFunctions.h"
#include <iostream>

/*
 * Function get string and returns its command.
 */
command hashFunction(string act){
	if(act=="read")return READ;
	if(act=="write")return WRITE;
	if(act=="touch")return TOUCH;
	if(act=="copy")return COPY;
	if(act=="remove")return REMOVE;
	if(act=="move")return MOVE;
	if(act=="cat")return CAT;
	if(act=="wc")return WC;
	if(act=="ln")return LN;
	if(act=="mkdir")return MKDIR;
	if(act=="chdir")return CHDIR;
	if(act=="rmdir")return RMDIR;
	if(act=="ls")return LS;
	if(act=="lproot")return LPROOT;
	if(act=="pwd")return PWD;
	if(act=="exit")return EXIT;
	return WRONG;
}

/*
 * Function return the string as a number if it is a number. else return -1
 */
int mySTOI(string s)
{
	int size=s.length();
	char c;
	for(int i=0;i<size-1;i++) //check each digit
	{
		c = s[i];
		if(!isdigit(c))// if its not digit its not number
			return -1;
	}
	return atoi(s.c_str());
}

/*
 * function gets path and filename in "fileName" and seperate it to path and fileName
 * and return it by reference.
 */
void getPathAndFileName(string& path, string& fileName) {
	size_t len = fileName.length();
	size_t pos = fileName.find_last_of("/");

	if(pos == len-1) //has "/" in te end of the string
	{
		fileName= fileName.substr(0, fileName.length()-1);
		pos = fileName.find_last_of("/");
	}

	if(pos==string::npos)
		path="/";
	else
		path = fileName.substr(0, pos+1);

	if(pos!=len-1)
		fileName = fileName.substr(pos+1, fileName.length());
}
