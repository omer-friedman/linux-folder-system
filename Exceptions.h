/*
 * Exceptions.h
 *
 *  Created on: 17 באפר׳ 2018
 *      Author: Omer
 */

#include <exception>
using namespace std;

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

	struct FolderAlradyExistsExcaption : public exception{
		const char* what() const throw() { return "ERROR: Folder already exists.\n"; }};
	struct FileNotFoundExcaption: public exception{
		const char* what() const throw() { return "ERROR: no such filename.\n"; }};
	struct OutOfLimitException: public exception{
		const char* what() const throw() { return "Index out of boundaries.\n"; }};
	struct WriteToFileException: public exception{
		const char* what() const throw() { return "Fail write to file. Please check your path.\n"; }};
	struct PathIsNotExistsException: public exception{
		const char* what() const throw() { return "ERROR: no such folder.\n"; }};


#endif /* EXCEPTIONS_H_ */
