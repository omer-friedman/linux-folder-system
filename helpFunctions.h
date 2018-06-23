/*
 * helpFunctions.h
 *
 *  Created on: 14 באפר׳ 2018
 *      Author: Omer
 */

#ifndef HELPFUNCTIONS_H_
#define HELPFUNCTIONS_H_

#include <string>
#include <cmath>
using namespace std;

typedef enum{READ,WRITE,TOUCH,COPY,REMOVE,MOVE,CAT,WC,LN,MKDIR,CHDIR,RMDIR,LS,LPROOT,PWD,EXIT,WRONG=-1}command;
command hashFunction(string);
void getPathAndFileName(string&,string&);
int mySTOI(string);

#endif /* HELPFUNCTIONS_H_ */
