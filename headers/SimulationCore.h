#ifndef CORE_H
#define CORE_H

#include <map>
#include <vector>

#include "Object.h"

namespace simulationCore
{
class core{
    private:
        void cleanTrash();
        int genId();

    public:   
        unsigned int _ids;
        std::vector<Object *> objects;
        std::vector<Object *> trash;
        std::vector<unsigned int> freeIds;
        bool _stop;

        core();
        ~core();
        void load();
        void run();
        void stop();
        void restart();
        void addObject(Object** obj);
        void removeObject(Object** obj);
        void removeObject(unsigned int id);
        void eraseObject(Object** obj);
        Object *getObject(unsigned int id);

        void _force_removeObject(Object** obj);
        void _force_removeObject(unsigned int id);
};
} // namespace simulationCore

#endif