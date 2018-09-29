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

#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "SimulationCore.h"
#include "SearchEngine.h"
#include "NodeGrid.h"

using namespace searchEngine;
using namespace std;

#define FLOOD_UP 1
#define FLOOD_RIGHT 2
#define FLOOD_DOWN 3
#define FLOOD_PING 4
#define FLOOD_RIGHT_UPPER_PING 5
#define FLOOD_RIGHT_BOTTOM_PING 6
#define FLOOD_BOTTOM_PING 7
#define FLOOD_TOP_PING 8
#define FLOOD_RIGHT_PING 9
#define FLOOD_NONE 10

class world : public Object{
    public:
        ngrid* map;
        vector<pair<ivec,ivec>> testingPoints;

    double counter;
    double counter_step;
    int floodType;
    int floodingRadious;
    double flood_activation_threshold;
    bool floodingEnabled;

    char* mapPath;
    char* testingPointsPath;

    world(char* mapPath, char* testingPointsPath, int floodType, double counter_step, double flood_activation_threshold);
    ~world();
 
    void setFlood(bool value);
    void ping_interval_flood(ivec& point);
    void down_horizontal_flood();
    void up_horizontal_flood();
    void right_vertical_flood();

    void reloadMap();

    void start() override;
    void update() override;
};

#endif
