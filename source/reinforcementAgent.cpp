#include "reinforcementAgent.h"
#include <unistd.h>

reinforcementAgent::reinforcementAgent(FalconAdaptiveQTable &table, Object *_world, statistics::observations* obs, int agentId)
{
    this->obs = obs;
    this->_world = (world *)_world;
    this->agentId = agentId;
    this->table = &table;
    int numberOfPossibleMovements = 8;
    trials = 0;
    success = 0;
    currentObservation = new double[max_epochs];
    SetNumberOfActions(numberOfPossibleMovements);
}

reinforcementAgent::~reinforcementAgent()
{
}

// init variables
void reinforcementAgent::_start()
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
void reinforcementAgent::_update()
{
    // clear variables
    availableActions.clear();
    availableActionsPositions.clear();

    vector<double> environment = getEnvironmentSensor();           // should contain a representation of the environment
    vector<int> availableActions = generateAvailableActionsList(); // should contain the code to all available moving fields

    bool print_Q_table = false;
    bool print_map = false;
    debugPrint(print_Q_table, print_map);

    // check if actions are available, otherwise reset simulation
    if (availableActions.size() == 0)
    {
        double dead_reward = -0.5;
        reset(dead_reward);
        return;
    }

    // perform the Q-learning
    QLearning(environment, availableActions);

    // check if agent is dead
    bool gotByHazzardArea = checkColision2D(*_world->map, position, COLLIDER_HAZARD_AREA);
    if (gotByHazzardArea)
    {
        double dead_reward = -0.5;
        reset(dead_reward);
        return;
    }

    // check if the agent can continue
    if (iteration > max_allowed_iterations)
    {
        double dead_reward = -0.5;
        reset(dead_reward);
        return;
    }

    // check sucess
    if (position == targetPosition)
    {
        // count success here
        success++;
        epoch_success++;

        double success_reward = 1.0;
        reset(success_reward);
        return;
    }

    iteration++;
}

// print the map
void reinforcementAgent::debugPrint(bool &print_Q_table, bool &print_Map)
{
    //system("clear");

    double rate = 0.0;
    if (trials > 0)
        rate = (double)success / (double)trials;
    printf("QTable size: %d Trial: %d Iteration: %d Epoch: %d Rate: %.4f Test: %d\n", table->neuronCount(), trials, iteration, epoch, rate, current_test);

    printf("Reward: %f\n", calculateReward());
    printf("Epsilon: %.10f\n", getEpsilon());

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
        for (map<string, double>::iterator it = table->neurons.begin(); it != table->neurons.end(); it++)
        {
            string action = (*it).first;
            double reward = (*it).second;

            printf("%s | %f\n", action.c_str(), reward);
        }
    }

    //usleep(10000);
}

void reinforcementAgent::restart(){
    // count as a new iteration
    current_test++;
    
    // reset epsilon
    epsilon = 1.0;

    // create a new buffer to store the new test results
    currentObservation = new double[max_epochs];

    // reset epoch
    epoch = 0;
    epoch_success = 0;
    success = 0;
    trials = 0;
    iteration = 0;

    // reset q-table
    table->clear();
}

// reset the state case necessary, can restart the simulation too
void reinforcementAgent::reset(double &_resetReward)
{
    UpdateFinalState(_resetReward);

    trials += 1;
    iteration = 0;

    // check epochs
    if(trials % epoch_size == 0){
        double epoch_success_rate = (double)epoch_success / (double)epoch_size;

        // save rating here
        currentObservation[epoch] = epoch_success_rate;

        epoch = epoch + 1;
        epoch_success = 0;
    }

    if(epoch == max_epochs){
        obs->insertSamplesIntoMatrix(currentObservation);
        restart();
        //sim->stop();
    }

    if(current_test == max_allowed_tests){
        sim->stop();
    }

    // tell to the world that i`m read
    _world->reloadMap();

    position = _world->testingPoints[agentId].first;
    targetPosition = _world->testingPoints[agentId].second;

    availableActions.clear();
    availableActionsPositions.clear();
}

// generate the environment
vector<double> reinforcementAgent::getEnvironmentSensor()
{
    vector<double> env(6);

    int x = position.x;
    int y = position.y;

    if (x < targetPosition.x)
        env[0] = 1.0;

    if (y < targetPosition.y)
        env[1] = 1.0;

    if (x > targetPosition.x)
        env[2] = 1.0;

    if (y > targetPosition.y)
        env[3] = 1.0;

    if (x == targetPosition.x)
        env[4] = 1.0;

    if (y == targetPosition.y)
        env[5] = 1.0;

    int mask_radius = 2;

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
    }

    // keep track of the distance from the target
    int distance_to_target = position.euclid2D(targetPosition);
    env.push_back(distance_to_target);

    return env;
}

// generate available actions
vector<int> reinforcementAgent::generateAvailableActionsList()
{
    // generate action list for the q-learning, a boolean vector, and also generate the real action table available
    availablePositions2D(*_world->map, position, availableActionsPositions, availableActions);
    return availableActions;
}

// performs the selected action
void reinforcementAgent::performAction(int &action)
{
    previousPosition.x = position.x;
    previousPosition.y = position.y;

    position = availableActionsPositions[action];
}

// calculate the reward for performing an action
double reinforcementAgent::calculateReward()
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
        reward = -0.1;

    return reward;
}

// predict q-value with any structure you like
double reinforcementAgent::predictQValue(vector<double> &environment, vector<double> &action)
{
    double pred_reward = -1.0;
    bool learning = false;
    double q_value = table->predict(environment, action, pred_reward, learning);
    return q_value;
}

// learn the q-value with any structure you like
double reinforcementAgent::learnStimulus(vector<double> &prevEnv, vector<double> &action, double& reward)
{
    bool learning = true;
    double q_value = table->predict(prevEnv, action, reward, learning);
    return q_value;
}