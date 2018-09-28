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