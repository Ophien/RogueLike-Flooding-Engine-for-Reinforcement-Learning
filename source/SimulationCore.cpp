#include "SimulationCore.h"
//---------------------------------------------------------------------------------------------------------
simulationCore::core::core()
{
    _ids = 0;
}
//---------------------------------------------------------------------------------------------------------
simulationCore::core::~core()
{
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::load()
{
    _stop = false;

    for (unsigned int i = 0; i < objects.size(); i++)
        objects[i]->start();
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::run()
{
    while (true)
    {
        for (unsigned int i = 0; i < objects.size(); i++)
        {
            Object *obj = objects[i];
            if (obj->getActive())
                obj->preupdate();
        }

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            Object *obj = objects[i];
            if (obj->getActive())
                obj->update();
        }

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            Object *obj = objects[i];
            if (obj->getActive())
                obj->posupdate();
        }

        // Remove unused objects
        cleanTrash();

        // Check process killing flag
        if (_stop)
            break;
    }
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::stop()
{
    _stop = true;
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::addObject(Object **_obj)
{
    Object *obj = (*_obj);
    unsigned int id = obj->getId();

    // put a reference for this object
    obj->setSimulationCore(this);

    // set id if it does not exist
    if (id == 0)
    {
        unsigned int generatedId = genId();
        obj->setId(generatedId);

        if(generatedId < objects.size())
            objects[generatedId] = obj;
        else
            objects.push_back(obj);
    }
    else
    {
        objects[id] = obj;
    }
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::removeObject(Object **_obj)
{
    Object *obj = (*_obj);
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        if (obj == objects[i])
        {
            trash.push_back(objects[i]);
            return;
        }
    }
}
//-simulationCore-------------------------------------------------------------------------------------------------------
void simulationCore::core::removeObject(unsigned int id)
{
    if (id < objects.size())
    {
        if (objects[id] != 0x0)
            trash.push_back(objects[id]);
    }
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::cleanTrash()
{
    for (unsigned int i = 0; i < trash.size(); i++)
    {
        // object to be handled
        Object *obj = trash[i];

        // operate only if the object reference in the memory is available
        if (obj != 0x0)
        {
            // recover obj id to be used later
            unsigned int id = obj->getId();
            freeIds.push_back(id);

            // permanently erase objects
            eraseObject(&obj);

            // set its position to 0x0
            objects[id] = 0x0;
        }
    }

    // clean trash
    trash.clear();
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::eraseObject(Object **_obj)
{
    Object *obj = (*_obj);
    unsigned int id = obj->getId();

    // free memory
    delete obj;
    obj = 0x0;
}
//---------------------------------------------------------------------------------------------------------
Object *simulationCore::core::getObject(unsigned int id)
{
    if (id < objects.size())
        if (objects[id] != 0x0)
            return objects[id];
}
//---------------------------------------------------------------------------------------------------------
int simulationCore::core::genId()
{
    unsigned int id = -1;
    if (freeIds.size() > 0)
    {
        id = freeIds.back();
        freeIds.pop_back();
    }
    else
    {
        id = _ids;
        _ids++;
    }

    return id;
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::_force_removeObject(Object **_obj)
{
    Object *obj = (*_obj);
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        if (obj == objects[i])
        {
            freeIds.push_back(i);
            eraseObject(&objects[i]);

            objects[i] = 0x0;
            return;
        }
    }
}
//---------------------------------------------------------------------------------------------------------
void simulationCore::core::_force_removeObject(unsigned int id)
{
    if (id < objects.size())
    {
        if (objects[id] != 0x0)
        {
            freeIds.push_back(id);
            eraseObject(&objects[id]);
            objects[id] = 0x0;
        }
    }
}
//---------------------------------------------------------------------------------------------------------