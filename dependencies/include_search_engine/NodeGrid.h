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

#ifndef NODEGRID
#define NODEGRID

#include <vector>

#include <string>
#include "NodeGridDeff.h"
#include "SearchEngineDeff.h"
#include "HeuristicType.h"
#include "FileReader.h"
#include "Algebra.h"

using namespace Algebra;

	class node {
	public:
		// Collider
		int col;

		// Holds the node status
		int status;

		// Holds the node type as a ivec2D
		ivec value;

		// Holds the node depth
		int depth;

		// Holds any kind of value that helps in performing a search algorithm or heuristic
		double aux;

		// Holds any kind of value that helps in performing a search algorithm or heuristic
		double aux2;

		// Reference for backtracking
		node* parent;

		// Default constructor
		node() {
			col = COLLIDER_FREESPACE;
			status = STATUS_AVAILABLE;
			depth = 0;
			parent = 0x0;
		}

		// Default constructor
		node(ivec position, int status, int col) {
			value = position;
			this->col = col;
			this->status = status;
			depth = 0;
			parent = 0x0;
		}
	};

	class nodeGEQ_comparator
	{
	public:
		bool operator()(node* n1, node* n2) {
			return n1->aux < n2->aux;
		}
	};

	class nodeLEQ_comparator
	{
	public:
		bool operator()(node* n1, node* n2) {
			return n1->aux > n2->aux;
		}
	};

	class ngrid
	{
	public:
		node*** grid;
		int width;
		int height;

		ngrid();
		ngrid(int width, int height);
		~ngrid();
	};

	void resetNGrid(ngrid* grid);
	double discreteUnitMoveCost(ivec& currentPos, ivec& targetPos);
	void gridStatistics(ngrid& grid, int& openListCount, int& closedListCount, int& availableSpaceCount, int& walkingSurfaceCount, int& wallCount);
	void printPath(const char* filepath, ngrid& grid, vector<ivec>& path);
	void printGrid(ngrid& grid);
	void printPath(ngrid& grid, vector<ivec>& path);
	void reversePath(vector<ivec>& path, bool assertCost);
	void savePathToFile(const char* filepath, vector<ivec>& path, bool printInTerminal);
	void generateTestingFile(char* gridPath, char* path, int dataSize);
	void loadTestingFile(const char* path, vector<pair<ivec,ivec> >& data);
	ngrid* createMap(const char* path);
	void availablePositions2D(ngrid &grid, ivec &source, std::vector<ivec> &ret, std::vector<int> &code);
	void availablePositions2D(ngrid& grid, ivec& source, vector<ivec>& positions);
	bool checkBounds2D(int& width, int& height, ivec& position);
	bool checkColision2D(ngrid& grid, ivec& position, int colisionValue);
	bool checkStatus(ngrid& grid, ivec& position, int status);
	void availablePositions2D(ngrid& grid, ivec& source, vector<ivec>& ret);
	void clearNodeStatus(ngrid& grid, vector<node*>& visitedNodes);
#endif

