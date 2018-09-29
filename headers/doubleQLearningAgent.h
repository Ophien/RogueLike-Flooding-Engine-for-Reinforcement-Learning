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
