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
