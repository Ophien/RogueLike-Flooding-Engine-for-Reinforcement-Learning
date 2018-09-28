#include "doubleQLearningAgent.h"
#include <unistd.h>

doubleQLearningAgent::doubleQLearningAgent(FalconAdaptiveQTable &tableA, FalconAdaptiveQTable &tableB, Object *_world, int agentId)
{
    this->_world = (world *)_world;
    this->agentId = agentId;
    this->tableA = &tableA;
    this->tableB = &tableB;
    int numberOfPossibleMovements = 8;
    trials = 0;
    success = 0;
    SetNumberOfActions(numberOfPossibleMovements);
}

doubleQLearningAgent::~doubleQLearningAgent()
{
}

// init variables
void doubleQLearningAgent::_start()
{
    enterExploreMode();

    _world->setFlood(true);

    iteration = 0;

    // tell to the world that i`m read
    _world->reloadMap();

    position = _world->testingPoints[agentId].first;
    previousPosition = position;
    targetPosition = _world->testingPoints[agentId].second;
}

// update the agent`s logic
void doubleQLearningAgent::_update()
{
    // clear variables
    availableActions.clear();
    availableActionsPositions.clear();

    vector<double> environment = getEnvironmentSensor();           // should contain a representation of the environment
    vector<int> availableActions = generateAvailableActionsList(); // should contain the code to all available moving fields

    bool print_Q_table = true;
    bool print_map = true;
    debugPrint(print_Q_table, print_map);

    // check if actions are available, otherwise reset simulation
    if (availableActions.size() == 0)
    {
        double dead_reward = -0.5;
        reset(dead_reward);
        return;
    }

    // perform the Q-learning
    doubleQLearning(environment, availableActions);

    // check if agent is dead
    bool gotByHazzardArea = checkColision2D(*_world->map, position, COLLIDER_HAZARD_AREA);
    if (gotByHazzardArea)
    {
        double dead_reward = -0.5;
        reset(dead_reward);
        return;
    }

    // check if the agent can continue
    if (iteration > 1000)
    {
        double dead_reward = -0.5;
        reset(dead_reward);
        return;
    }

    // check sucess
    if (position == targetPosition)
    {
        success++;
        double success_reward = 1.0;
        reset(success_reward);
        return;
    }

    iteration++;
}

// print the map
void doubleQLearningAgent::debugPrint(bool &print_Q_table, bool &print_Map)
{
    system("clear");

    double rate = 0.0;
    if (trials > 0)
        rate = (double)success / (double)trials;
    printf("QTable A size: %d QTable b size: %d Trial %d Iteration %d Rate: %.4f\n", tableA->neuronCount(), tableB->neuronCount(), trials, iteration, rate);

    printf("Reward: %f\n", calculateReward());
    printf("Epsilon: %.10f\n", getdoubleQEpsilon());

    if (print_Map)
    {
        printf("\n");
        for (int y = 0; y < _world->map->height; y++)
        {
            for (int x = 0; x < _world->map->width; x++)
            {
                if (_world->map->grid[x][y]->col == COLLIDER_HAZARD_AREA)
                    printf("<");
                else
                {
                    if (_world->map->grid[x][y]->col == COLLIDER_WALL)
                    {
                        printf("@");
                    }
                    else
                    {
                        ivec matPos = ivec(x, y);
                        if (position == matPos)
                        {
                            printf("A");
                        }
                        else
                        {
                            if (matPos == targetPosition)
                                printf("K");
                            else
                                printf(".");
                        }
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    // getc(stdin);
    if (print_Q_table)
    {
        for (map<string, double>::iterator it = tableA->neurons.begin(); it != tableA->neurons.end(); it++)
        {
            string action = (*it).first;
            double reward = (*it).second;

            printf("%s | %f\n", action.c_str(), reward);
        }
    }

    //usleep(100000);
}

// reset the state case necessary, can restart the simulation too
void doubleQLearningAgent::reset(double &_resetReward)
{
    doubleUpdateFinalState(_resetReward);

    trials += 1;
    iteration = 0;

    // tell to the world that i`m read
    _world->reloadMap();

    position = _world->testingPoints[agentId].first;
    targetPosition = _world->testingPoints[agentId].second;

    availableActions.clear();
    availableActionsPositions.clear();
}

// generate the environment
vector<double> doubleQLearningAgent::getEnvironmentSensor()
{
    vector<double> env(2);

    int x = position.x;
    int y = position.y;

    if (x < targetPosition.x)
        env[0] = 1.0;

    if (y < targetPosition.y)
        env[1] = 1.0;

    /*if (x > targetPosition.x)
        env[2] = 1.0;

    if (y > targetPosition.y)
        env[3] = 1.0;

    if (x == targetPosition.x)
        env[4] = 1.0;

    if (y == targetPosition.y)
        env[5] = 1.0;

    int mask_radius = 20;

    // simple feature map
    for (int i = x - mask_radius; i < x + mask_radius; i++)
    {
        for (int j = y - mask_radius; j < y + mask_radius; j++)
        {
            ivec sonarPos = ivec(i, j);
            if (checkBounds2D(_world->map->width, _world->map->height, sonarPos))
            {
                if (checkColision2D(*_world->map, sonarPos, COLLIDER_WALL))
                    env.push_back(1.0); // seeing a barrier or a hazard area
                else
                    env.push_back(0.0); // seeing a barrier or a hazard area
            }
            else
            {
                env.push_back(1.0); // seeying border wall
            }
        }
    }

    for (int i = x - mask_radius; i < x + mask_radius; i++)
    {
        for (int j = y - mask_radius; j < y + mask_radius; j++)
        {
            ivec sonarPos = ivec(i, j);
            if (checkBounds2D(_world->map->width, _world->map->height, sonarPos))
            {
                if (checkColision2D(*_world->map, sonarPos, COLLIDER_HAZARD_AREA))
                    env.push_back(1.0); // seeing a barrier or a hazard area
                else
                    env.push_back(0.0); // seeing a barrier or a hazard area
            }
            else
            {
                env.push_back(1.0); // seeying border wall
            }
        }
    }*/

    // keep track of the distance from the target
    //int distance_to_target = position.euclid2D(targetPosition);
    //env.push_back(distance_to_target);

    return env;
}

// generate available actions
vector<int> doubleQLearningAgent::generateAvailableActionsList()
{
    // generate action list for the q-learning, a boolean vector, and also generate the real action table available
    availablePositions2D(*_world->map, position, availableActionsPositions, availableActions);
    return availableActions;
}

// performs the selected action
void doubleQLearningAgent::performAction(int &action)
{
    previousPosition.x = position.x;
    previousPosition.y = position.y;

    position = availableActionsPositions[action];
}

// calculate the reward for performing an action
double doubleQLearningAgent::calculateReward()
{
    // calculate the distance from target here
    double maxDist = ivec(0, 0).euclid2D(ivec(_world->map->width, _world->map->height));

    double dist = position.euclid2D(targetPosition) / maxDist;
    double prevDist = previousPosition.euclid2D(targetPosition) / maxDist;

    double dif = dist - prevDist;

    double reward = 0.0;
    if (dif < 0)
        reward = 0.1;
    else
        reward = -0.4;

    return reward;
}

double doubleQLearningAgent::doubleQLearningPredictQValue(vector<double>& environment, vector<double>& action, int& tableToUse){
    bool learning = false;
    double q_value = 0.0;
    double pred_reward = -1.0;
    switch(tableToUse){
        {
        case 0:
            q_value = tableA->predict(environment, action, pred_reward, learning);
            break;
        }
        {
            case 1:
            q_value = tableB->predict(environment, action, pred_reward, learning);
            break;
        }
    }
    
    return q_value;
}

// predict q-value with any structure you like
double doubleQLearningAgent::doubleQLearningPredictAllTables(vector<double> &environment, vector<double> &action)
{
    double pred_reward = -1.0;
    bool learning = false;

    double q_valueA = tableA->predict(environment, action, pred_reward, learning);
    double q_valueB = tableB->predict(environment, action, pred_reward, learning);

    double final_q_value = q_valueA + q_valueB;
    return final_q_value;
}

// learn the q-value with any structure you like
double doubleQLearningAgent::doubleQLearninglearnStimulus(vector<double> &prevEnv, vector<double> &action, double& reward, int& tableToUse)
{
    bool learning = true;
    double q_value = 0.0;
    switch(tableToUse){
        {
        case 0:
            q_value = tableA->predict(prevEnv, action, reward, learning);
            break;
        }
        {
            case 1:
            q_value = tableB->predict(prevEnv, action, reward, learning);
            break;
        }
    }
    
    return q_value;
}