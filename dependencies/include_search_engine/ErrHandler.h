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

#ifndef ERRHANDLER_H
#define ERRHANDLER_H

#include <stdio.h>
#include <stdlib.h>

// SOURCE 
#define SYSTEM_OK 0

// FILE HANDLER
#define ERR_FILE_NOT_FOUND -1

// DATA STRUCTURES
#define ERR_PRIORITY_QUEUE_REMOVAL -2

void Err(const char* msg, const int errCode);
#endif