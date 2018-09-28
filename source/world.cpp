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
