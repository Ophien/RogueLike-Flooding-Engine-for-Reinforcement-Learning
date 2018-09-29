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

#include "world.h"

world::world(char *mapPath, char *testingPointsPath, int floodType, double counter_step, double activationThreshold) : Object()
{
    this->mapPath = mapPath;
    this->testingPointsPath = testingPointsPath;

    this->floodType = floodType;

    this->flood_activation_threshold = activationThreshold;

    this->counter_step = counter_step;

    floodingEnabled = false;
}

void world::setFlood(bool value)
{
    floodingEnabled = value;
}

void world::reloadMap()
{
    delete map;
    map = 0x0;

    // loading map
    map = createMap(mapPath);

    // load testing points for this map
    loadTestingFile(testingPointsPath, testingPoints);

    floodingRadious = 0;

    counter = 0.0;
}

void world::ping_interval_flood(ivec &point)
{
    int width = map->width;
    int height = map->height;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if ((point.x - x) * (point.x - x) + (point.y - y) * (point.y - y) <= floodingRadious * floodingRadious)
            {
                map->grid[x][y]->col = COLLIDER_HAZARD_AREA;
            }
        }
    }

    floodingRadious++;
}

void world::down_horizontal_flood()
{
    int width = map->width;
    int height = map->height;

    for (int x = 0; x < width; x++)
    {
        int y = height - 1 - floodingRadious;
        map->grid[x][y]->col = COLLIDER_HAZARD_AREA;
    }

    floodingRadious++;
}

void world::up_horizontal_flood()
{
    int width = map->width;
    int height = map->height;

    for (int x = 0; x < width; x++)
    {
        int y = floodingRadious;
        map->grid[x][y]->col = COLLIDER_HAZARD_AREA;
    }

    floodingRadious++;
}

void world::right_vertical_flood()
{
    int width = map->width;
    int height = map->height;

    for (int y = 0; y < height; y++)
    {
        int x = width - 1 - floodingRadious;
        map->grid[x][y]->col = COLLIDER_HAZARD_AREA;
    }

    floodingRadious++;
}

world::~world()
{
}

void world::start()
{
}

void world::update()
{
    if (floodingEnabled)
    {
        counter += counter_step;

        if (counter > flood_activation_threshold)
        {
            // reset counter
            counter = 0.0;

            switch (floodType)
            {
            case FLOOD_DOWN:
            {
                down_horizontal_flood();
                break;
            }
            case FLOOD_PING:
            {
                int width = map->width;
                int height = map->height;

                ivec floodingPoint = ivec(width / 2, height / 2);

                ping_interval_flood(floodingPoint);
                break;
            }
            case FLOOD_RIGHT_UPPER_PING:
            {
                int width = map->width;
                int height = map->height;

                ivec floodingPoint = ivec(width - 1, 0);

                ping_interval_flood(floodingPoint);
                break;
            }
            case FLOOD_RIGHT_BOTTOM_PING:
            {
                int width = map->width;
                int height = map->height;

                ivec floodingPoint = ivec(width - 1, height - 1);

                ping_interval_flood(floodingPoint);
                break;
            }
            case FLOOD_BOTTOM_PING:
            {
                int width = map->width;
                int height = map->height;

                ivec floodingPoint = ivec(width / 2, height - 1);

                ping_interval_flood(floodingPoint);
                break;
            }
            case FLOOD_TOP_PING:
            {
                int width = map->width;
                int height = map->height;

                ivec floodingPoint = ivec(width / 2, 0);

                ping_interval_flood(floodingPoint);
                break;
            }
            case FLOOD_RIGHT_PING:
            {
                int width = map->width;
                int height = map->height;

                ivec floodingPoint = ivec(width - 1, height / 2);

                ping_interval_flood(floodingPoint);
                break;
            }
            case FLOOD_RIGHT:
            {
                right_vertical_flood();
                break;
            }
            case FLOOD_UP:
            {
                up_horizontal_flood();
                break;
            }
            case FLOOD_NONE:
            {

                break;
            }
            }
        }
    }
}
