#ifndef DOUBLE_Q_LEARNING_AGENT_H
#define DOUBLE_Q_LEARNING_AGENT_H

#include "GenericReinforcementAgent.h"
#include "AdaptiveQTable.h"
#include "SimulationCore.h"
#include "SearchEngine.h"
#include "world.h"
#include <vector>

using namespace std;

class doubleQLearningAgent : public GenericReinforcementAgent
{
  public:
    world* _world;
    ivec position;
    ivec targetPosition;
    int agentId;
    int iteration;
    char code;
    ivec previousPosition;

    int trials;
    int success;

    vector<int> availableActions;
    vector<ivec> availableActionsPositions;

    doubleQLearningAgent(FalconAdaptiveQTable& tableA, FalconAdaptiveQTable& tableB, Object* _world, int agentId);
    ~doubleQLearningAgent();

    void _start();
    void _update();
    void reset(double &resetReward);
    vector<int> generateAvailableActionsList();
    vector<double> getEnvironmentSensor();
    void performAction(int &action);
    void previousStateKeeper();
    double calculateReward();

    double doubleQLearningPredictAllTables(vector<double>& environment, vector<double>& action);
    double doubleQLearningPredictQValue(vector<double>& environment, vector<double>& action, int& tableToUse);
    double doubleQLearninglearnStimulus(vector<double>& prevEnv, vector<double>& action, double& reward, int& tableToUse);

    void debugPrint(bool& print_Q_table, bool& print_map);

    FalconAdaptiveQTable* tableA;
    FalconAdaptiveQTable* tableB;
};

#endif