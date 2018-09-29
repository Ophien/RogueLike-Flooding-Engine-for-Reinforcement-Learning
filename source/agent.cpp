/*MIT License
*
*Copyright (c) 2018 Alysson Ribeiro da Silva
*
*Permission is hereby granted, free of charge, to any person obtaining a copy 
*of this software and associated documentation files (the "Software"), to deal 
*in the Software without restriction, including *without limitation the rights 
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
*copies of the Software, and to permit persons to whom the Software is furnished 
*to do so, subject *to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *IN NO EVENT SHALL THE AUTHORS 
*OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
*AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
*THE *SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "agent.h"

agent::agent(Object *_world, int agentId) : Object()
{
    this->_world = (world *)_world;
    this->agentId = agentId;
}

agent::~agent()
{
}

void agent::start()
{
    position = _world->testingPoints[agentId].first;
    targetPosition = _world->testingPoints[agentId].second;
}

void agent::update()
{
    // perform A_star
    vector<ivec> path;

    // Call algorithm
    AStar(*_world->map, position, targetPosition, path, HEURISTIC_TYPE_EUCLIDEAN);

    // reset grid toperform a new Astar
    resetNGrid(_world->map);

    // move agent to the next available position on its path
    if (path.size() > 0)
    {
        if (path.size() >= 2)
            position = path[path.size() - 2];

        // print this agent vision
        printPath(*_world->map, path);
    }else{
        printGrid(*_world->map);
    }
     
    // pause simulation
    getc(stdin);
}
