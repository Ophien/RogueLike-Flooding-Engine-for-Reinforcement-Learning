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

#include "GenericReinforcementAgent.h"
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

GenericReinforcementAgent::GenericReinforcementAgent() : Object()
{
}

GenericReinforcementAgent::~GenericReinforcementAgent()
{
}

void GenericReinforcementAgent::enterExploitMode()
{
    epsilon = -1.0;
}

void GenericReinforcementAgent::enterExploreMode()
{
    epsilon = 1.0;
}

/// <summary>
/// Created by Alysson Ribeiro da Silva, the PhaseOne calls all routines to perform the first part of the Q-learning algorithm (exploration and exploitation)
/// </summary>
/// <param name="environment"></param>
/// <param name="availableActions"></param>
void GenericReinforcementAgent::QLearning(vector<double> &environment, vector<int> &availableActions)
{
    if (Q_old != -1.0)
    {
        PhaseTwo(environment, availableActions);
        Q_old = 1.0;
    }

    // select exploration or exploitation
    float randomFloat = ((double)rand() / (RAND_MAX));
    double reward = 0.0;
    double max_q = -100000000.0;
    bool enableRandom = true;
    selectedAction = -1;

    // Random Action
    if (epsilon > randomFloat)
    {
        // Set variables to move agent
        int range = availableActions.size();
        int randomMoveAct = rand() % range;

        int act = availableActions[randomMoveAct];
        vector<double> actVec = generateActionVector(act);

        // Calculates the predicted Q-value from your q-table structure
        max_q = predictQValue(environment, actVec);

        // Set selected action
        selectedAction = act;
    }
    // Q-Max action
    else
    {
        for (int i = 0; i < availableActions.size(); i++)
        {
            // Setup action moving field
            int act = availableActions[i];
            vector<double> actVec = generateActionVector(act);

            double q_value = predictQValue(environment, actVec);

            if (q_value > max_q)
            {
                max_q = q_value;
                selectedAction = act;
            }
        }
    }

    // set the Q-old variable to compute the temporal difference
    Q_old = max_q;

    // move agent to configure its next q-phase
    performAction(selectedAction);

    // store previous state
    prevEnvironment = vector<double>(environment);
}

void GenericReinforcementAgent::doubleQLearning(vector<double> &environment, vector<int> &availableActions)
{
    if (Q_old != -1.0)
    {
        dPhaseTwo(environment, availableActions);
        Q_old = 1.0;
    }

    // select exploration or exploitation
    float randomFloat = ((double)rand() / (RAND_MAX));
    double reward = 0.0;
    double max_q = -100000000.0;
    bool enableRandom = true;
    selectedAction = -1;

    // select which table will be used to learn < 50 table A > 50 table B
    //tableSelectionRand = ((double)rand() / (RAND_MAX));

    if (previousTable == 0)
        selectedTable = 1;
    else
        selectedTable = 0;

    previousTable = selectedTable;

    // Random Action
    if (depsilon > randomFloat)
    {
        // Set variables to move agent
        int range = availableActions.size();
        int randomMoveAct = rand() % range;

        int act = availableActions[randomMoveAct];
        vector<double> actVec = generateActionVector(act);

        // Calculates the predicted Q-value from your q-table structure
        max_q = doubleQLearningPredictQValue(environment, actVec, selectedTable);

        // Set selected action
        selectedAction = act;
    }
    // Q-Max action
    else
    {
        int selectedIndex = 0;
        for (int i = 0; i < availableActions.size(); i++)
        {
            // Setup action moving field
            int act = availableActions[i];
            vector<double> actVec = generateActionVector(act);

            // get max tableA + tableB
            double q_value = doubleQLearningPredictAllTables(environment, actVec);

            if (q_value > max_q)
            {
                selectedIndex = i;
                max_q = q_value;
                selectedAction = act;
            }
        }

        // calculate real Q-value based on the selected table
        // Setup action moving field
        vector<double> actVec = generateActionVector(availableActions[selectedIndex]);

        max_q = doubleQLearningPredictQValue(environment, actVec, selectedTable);
    }

    // set the Q-old variable to compute the temporal difference
    Q_old = max_q;

    // move agent to configure its next q-phase
    performAction(selectedAction);

    // store previous state
    prevEnvironment = vector<double>(environment);
}

double GenericReinforcementAgent::getEpsilon()
{
    return epsilon;
}


double GenericReinforcementAgent::getdoubleQEpsilon()
{
    return depsilon;
}

/// <summary>
/// Created by Alysson Ribeiro da Silva, the UpdateFinalState function is used to force the Q-learning algorithm to learn stimulus received by the last State
/// </summary>
/// <param name="res"></param>
void GenericReinforcementAgent::doubleUpdateFinalState(double &res)
{
    // Asign the Q-new variable to perform actions
    Q_new = res;

    // Immediate reward, after performed action
    immediateReward = calculateReward();

    if (usedDirectReward)
    {
        Q_new = immediateReward;
    }

    // Calculates the Q-learning Temporal Difference error
    double sum = 0.0;

    if (!useBelman)
    {
        sum = dlearningRate * (immediateReward + (ddiscountParameter * Q_new) - Q_old);
    }
    else
    {
        sum = immediateReward + discountParameter * Q_new;
    }

    // Bounded Q-Learning
    sum = sum * (1.0 - Q_old);

    // Q-To be learned
    double q_to_learn = Q_old + sum;

    // Generate action vector to be learned
    vector<double> actVec = generateActionVector(selectedAction);

    // Call the learning function to reinforce the observed environment and actions
    doubleQLearninglearnStimulus(prevEnvironment, actVec, q_to_learn, selectedTable);
}

/// <summary>
/// Created by Alysson Ribeiro da Silva, the UpdateFinalState function is used to force the Q-learning algorithm to learn stimulus received by the last State
/// </summary>
/// <param name="res"></param>
void GenericReinforcementAgent::UpdateFinalState(double &res)
{
    // Asign the Q-new variable to perform actions
    Q_new = res;

    // Immediate reward, after performed action
    immediateReward = calculateReward();

    if (usedDirectReward)
    {
        Q_new = immediateReward;
    }

    // Calculates the Q-learning Temporal Difference error
    double sum = 0.0;

    if (!useBelman)
    {
        sum = learningRate * (immediateReward + (discountParameter * Q_new) - Q_old);
    }
    else
    {
        sum = immediateReward + discountParameter * Q_new;
    }

    // Bounded Q-Learning
    sum = sum * (1.0 - Q_old);

    // Q-To be learned
    double q_to_learn = Q_old + sum;

    // Generate action vector to be learned
    vector<double> actVec = generateActionVector(selectedAction);

    // Call the learning function to reinforce the observed environment and actions
    learnStimulus(prevEnvironment, actVec, q_to_learn);
}

/// <summary>
/// Created by Alysson Ribeiro da Silva, the SetNumberOfActions set the total number of actions used by the reinforcement algorithm
/// </summary>
/// <param name="actionCount"></param>
void GenericReinforcementAgent::SetNumberOfActions(int &actionCount)
{
    this->actionCount = actionCount;
}

// control

/// <summary>
/// Unity engine update method.
/// </summary>
void GenericReinforcementAgent::update()
{
    _update();
}

/// <summary>
/// Unity engine start method.
/// </summary>
void GenericReinforcementAgent::start()
{
    _start();
}

/// <summary>
/// Created by Alysson Ribeiro da Silva, the generateActionVector generates a boolean action vector to be used by a learning algorithm
/// </summary>
/// <param name="selectedAction"></param>
/// <returns></returns>
vector<double> GenericReinforcementAgent::generateActionVector(int &selectedAction)
{
    vector<double> ret(actionCount);
    ret[selectedAction] = 1.0;
    return ret;
}

/// <summary>
/// Created by Alysson Ribeiro da Silva, the PhaseTwo algorithm performs the second part of the Q-learning algorithm (check and learning)
/// </summary>
/// <param name="environment"></param>
/// <param name="availableActions"></param>
void GenericReinforcementAgent::dPhaseTwo(vector<double> &environment, vector<int> &availableActions)
{
    // Variable to hold the newly expected max Q-value
    Q_new = -100000000.0;

    // Calculates the immediate reward, used for reinforcement learning
    immediateReward = calculateReward();

    if (dusedDirectReward)
    {
        Q_new = immediateReward;
    }
    else
    {
        // store index to get from the inverse q-table
        int selectedField = 0;

        // Check in the expectations, which one is the best and use it to update the Q-learning Q-value of the virtual Q-learning table
        for (int i = 0; i < availableActions.size(); i++)
        {
            // Setup action moving field
            int field = availableActions[i];
            vector<double> act = generateActionVector(field);

            // select action from table 1 or table 2
            double q_value = doubleQLearningPredictQValue(environment, act, selectedTable);

            if (q_value > Q_new)
            {
                selectedField = i;
                Q_new = q_value;
            }
        }

        // set the q-value that will be used to compute the temporal difference
        int inverse_table = 0;
        if (selectedTable == 0)
            inverse_table = 1;
        else
            inverse_table = 0;

        // Setup action moving field
        vector<double> act = generateActionVector(availableActions[selectedField]);
        Q_new = doubleQLearningPredictQValue(environment, act, inverse_table);
    }

    // Calculates the Q-learning Temporal Difference error
    double sum = 0.0;

    if (!duseBelman)
    {
        sum = dlearningRate * (immediateReward + (ddiscountParameter * Q_new) - Q_old);
    }
    else
    {
        sum = immediateReward + ddiscountParameter * Q_new;
    }

    // Calculates the bounded rule for the reinforcement learning
    sum = sum * (1.0 - Q_old);

    // Calculates the newly Q-value to be learned
    double q_to_learn = Q_old + sum;

    // Generates the action vector used for learning
    vector<double> actVec = generateActionVector(selectedAction);

    // Call the learning function to reinforce the observed environment and actions
    doubleQLearninglearnStimulus(prevEnvironment, actVec, q_to_learn, selectedTable);

    // Updates the epsilon with its decay settings
    depsilon = depsilon - depsilonDecay;
}

/// <summary>
/// Created by Alysson Ribeiro da Silva, the PhaseTwo algorithm performs the second part of the Q-learning algorithm (check and learning)
/// </summary>
/// <param name="environment"></param>
/// <param name="availableActions"></param>
void GenericReinforcementAgent::PhaseTwo(vector<double> &environment, vector<int> &availableActions)
{
    // Variable to hold the newly expected max Q-value
    Q_new = -100000000.0;

    // Calculates the immediate reward, used for reinforcement learning
    immediateReward = calculateReward();

    // select which table will learn

    if (usedDirectReward)
    {
        Q_new = immediateReward;
    }
    else
    {
        // Check in the expectations, which one is the best and use it to update the Q-learning Q-value of the virtual Q-learning table
        for (int i = 0; i < availableActions.size(); i++)
        {
            // Setup action moving field
            int field = availableActions[i];
            vector<double> act = generateActionVector(field);

            double q_value = predictQValue(environment, act);

            if (q_value > Q_new)
            {
                Q_new = q_value;
            }
        }
    }

    // Calculates the Q-learning Temporal Difference error
    double sum = 0.0;

    if (!useBelman)
    {
        sum = learningRate * (immediateReward + (discountParameter * Q_new) - Q_old);
    }
    else
    {
        sum = immediateReward + discountParameter * Q_new;
    }

    // Calculates the bounded rule for the reinforcement learning
    sum = sum * (1.0 - Q_old);

    // Calculates the newly Q-value to be learned
    double q_to_learn = Q_old + sum;

    // Generates the action vector used for learning
    vector<double> actVec = generateActionVector(selectedAction);

    // Call the learning function to reinforce the observed environment and actions
    learnStimulus(prevEnvironment, actVec, q_to_learn);

    // Updates the epsilon with its decay settings
    epsilon = epsilon - epsilonDecay;
}

double GenericReinforcementAgent::doubleQLearningPredictQValue(vector<double>& environment, vector<double>& action, int& tableToUse){
}

// predict q-value with any structure you like
double GenericReinforcementAgent::doubleQLearningPredictAllTables(vector<double> &environment, vector<double> &action)
{
}

// learn the q-value with any structure you like
double GenericReinforcementAgent::doubleQLearninglearnStimulus(vector<double> &prevEnv, vector<double> &action, double& reward, int& tableToUse)
{
}

void GenericReinforcementAgent::setDirectReward(bool &value)
{
    usedDirectReward = value;
}

void GenericReinforcementAgent::setBelman(bool &value)
{
    useBelman = value;
}

void GenericReinforcementAgent::performAction(int &action)
{
}

double GenericReinforcementAgent::calculateReward()
{
}

double GenericReinforcementAgent::predictQValue(vector<double> &environment, vector<double> &action)
{
}

double GenericReinforcementAgent::learnStimulus(vector<double> &prevEnv, vector<double> &action, double &reward)
{
}

void GenericReinforcementAgent::_update()
{
}

void GenericReinforcementAgent::_start()
{
}
