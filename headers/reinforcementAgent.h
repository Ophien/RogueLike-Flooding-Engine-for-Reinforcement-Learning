#ifndef REINFORCEMENT_AGENT_H
#define REINFORCEMENT_AGENT_H

#include "GenericReinforcementAgent.h"
#include "AdaptiveQTable.h"
#include "SimulationCore.h"
#include "SearchEngine.h"
#include "world.h"
#include "statistics.h"
#include <vector>

using namespace std;

class reinforcementAgent : public GenericReinforcementAgent
{
  public:
    world* _world;
    ivec position;
    ivec targetPosition;
    int agentId;
    int iteration;
    char code;
    ivec previousPosition;

    double* currentObservation;
    statistics::observations* obs;

    const int max_allowed_tests = 2;
    const int max_allowed_iterations = 100;
    const int max_epochs = 40;
    const int epoch_size = 25;
    int current_test;
    int epoch;
    int epoch_success;
    int trials;
    int success;

    vector<int> availableActions;
    vector<ivec> availableActionsPositions;

    reinforcementAgent(FalconAdaptiveQTable& table, Object* _world, statistics::observations* obs, int agentId);
    ~reinforcementAgent();

    void _start();
    void _update();
    void reset(double &resetReward);
    void restart();
    vector<int> generateAvailableActionsList();
    vector<double> getEnvironmentSensor();
    void performAction(int &action);
    void previousStateKeeper();
    double calculateReward();

    // simples q-learning
    double predictQValue(vector<double> &environment, vector<double> &action);
    double learnStimulus(vector<double> &prevEnv, vector<double> &action, double& reward);
    
    void debugPrint(bool& print_Q_table, bool& print_map);

    FalconAdaptiveQTable* table;
};

#endif