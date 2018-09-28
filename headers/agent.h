#ifndef AGENT_H
#define AGENT_H

#include "SimulationCore.h"
#include "SearchEngine.h"
#include "world.h"

#include <vector>

class agent : public Object{
    public:

    world* _world;
    ivec position;
    ivec targetPosition;
    int agentId;
    char code;

    agent(Object* _world, int agentId);
    ~agent();

    void start() override;
    void update() override;
};

#endif