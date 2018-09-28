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

#ifndef NODEPQUEUE_H
#define NODEPQUEUE_H

#include<vector>

#include "NodeGrid.h"
#include "ErrHandler.h"

using namespace std;

class NodePriorityQueue
{
	public:
		NodePriorityQueue();
		~NodePriorityQueue();
		vector<node*> pQueue;
		unsigned int size();
		void push(node* ptr);
		node* pop();
		node* top();
		void remove(node* ptr);
};
#endif