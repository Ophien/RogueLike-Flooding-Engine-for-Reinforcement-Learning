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

#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H

// System includes for data structures
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<queue>
#include<list>

// Local includes
#include "Algebra.h"
#include "NodeGrid.h"
#include "HeuristicType.h"
#include "SearchEngineDeff.h"
#include "NodePriorityQueue.h"
#include "ErrHandler.h"

using namespace std;
using namespace Algebra;
using namespace FileHandler;

namespace searchEngine {
	// Helper func.
	void getPath(node* leaf, vector<ivec>& path);
	void getPath(node* leaf, vector<ivec>& path);

	// Heuristics
	double calculateHeuristic(ivec& position, ivec& target, const int& heuristic);

	// Search methods
	void iterativeDeepeningDepthFirstSearch(ngrid& map, ivec& startPoint, ivec& endPoint, vector<ivec>& path, bool& hack);
	void uniformCostSearch(ngrid& map, ivec& startPoint, ivec& endPoint, vector<ivec>& path);
	void bestFirstSearch(ngrid& map, ivec& startPoint, ivec& endPoint, vector<ivec>& path, int heuristic);
	void AStar(ngrid& map, ivec& startPoint, ivec& endPoint, vector<ivec>& path, int heuristic);
	void depthFirstSearch(ngrid& map, ivec& startPoint, ivec& endPoint, vector<ivec>& path);

	// Search interfaces
	void IDS(ngrid *gridMap, ivec &start, ivec &end, bool console, vector<int> &outTime, vector<int> &outOpenList, vector<int> &outClosedList);
	void BFS(ngrid *gridMap, ivec &start, ivec &end, int heuristic, bool console, vector<int> &outTime, vector<int> &outOpenList, vector<int> &outClosedList);
	void UCS(ngrid *gridMap, ivec &start, ivec &end, bool console, vector<int> &outTime, vector<int> &outOpenList, vector<int> &outClosedList);
	void ASTAR(ngrid *gridMap, ivec &start, ivec &end, int heuristic, bool console, vector<int> &outTime, vector<int> &outOpenList, vector<int> &outClosedList);
	void generateMeanVecAndErr(
		vector<int> &IDS,
		vector<int> &BFS,
		vector<int> &UCS,
		vector<int> &ASTAR,
		vector<int> &ASTARO,
		vector<double> &mean,
		vector<double> &var,
		vector<double> &deviation);
	void saveCSV(const char *path, vector<double> mean, vector<double> var, vector<double> dev);
	void performBenchmark(char *path, char *mapTestDataPath, int maxSamples);
	void terminalIDS(char *map, ivec startPos, ivec endPos);
	void terminalUCS(char *map, ivec startPos, ivec endPos);
	void terminalBFS(char *map, ivec startPos, ivec endPos, int heuristic);
	void terminalASTAR(char *map, ivec startPos, ivec endPos, int heuristic);
	void terminalInterface(int argc, char *argv[]);

	// Generic depth first search
	void _depthFirstSearch(ngrid& map, stack<node*>& states, stack<node*>& out_border, node* lowCost, node* root, ivec& startPoint, ivec& endPoint, vector<ivec>& outputNodes, int& allowedDepth, bool& returnFirstFound);
}

#endif
