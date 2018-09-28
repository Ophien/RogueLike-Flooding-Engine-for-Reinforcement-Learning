#include "Object.h"

Object::Object()
{
    // init id
    id = 0;

    // set object active by default
    setActive(true);
}

Object::~Object()
{
}

void Object::start()
{
}

void Object::update()
{
}

void Object::preupdate()
{
}

void Object::posupdate()
{
}

bool Object::getActive()
{
}

void Object::setSimulationCore(simulationCore::core *sim)
{
    this->sim = sim;
}

void Object::setActive(bool val)
{
    active = val;
}

void Object::setId(unsigned int _id)
{
    id = _id;
}

unsigned int Object::getId()
{
    return id;
}