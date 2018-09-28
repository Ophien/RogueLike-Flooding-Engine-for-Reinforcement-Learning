/*
 * Copyright(C) 2018 Alysson Ribeiro da Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see<https://www.gnu.org/licenses/>.
 *
*/

#ifndef FILEREADER_H
#define FILEREADER_H

// GLOBAL INCLUDES
#include<stdio.h> // standard IO, printf, fprintf...
#include<vector>
#include<algorithm>
#include<cctype>
#include<string.h>

// LOCAL INCLUDES
#include "FileUtilsDeff.h" // my definitions

using namespace std;

namespace FileHandler {
	bool checkContent(char& c, char* arr, const int& arrSize);
	bool readNext(FILE* file, char* output, const int& buffSize, int& readedCount, char& delim, char* skipArray, const int& skipArrSize);
	void simpleSplit(char* input, const char* delimn, std::vector<char*>& splited);
}
#endif
