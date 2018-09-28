#ifndef GENERIC_REINFORCEMENT_AGENT_H
#define GENERIC_REINFORCEMENT_AGENT_H

#include <vector>

#include "Object.h"

using namespace std;

class GenericReinforcementAgent : public Object
{
  public:
    GenericReinforcementAgent();
    ~GenericReinforcementAgent();
    void QLearning(vector<double>& environment, vector<int>& availableActions);
    void doubleQLearning(vector<double>& environment, vector<int>& availableActions);

protected:
    // Abstract functions for Q-learning
    virtual void performAction(int& action);
    virtual double calculateReward();
    
    // double q-learning
    virtual double doubleQLearningPredictAllTables(vector<double>& environment, vector<double>& action);
    virtual double doubleQLearningPredictQValue(vector<double>& environment, vector<double>& action, int& tableToUse);
    virtual double doubleQLearninglearnStimulus(vector<double>& prevEnv, vector<double>& action, double& reward, int& tableToUse);
    void doubleUpdateFinalState(double& res);

    // single q-learning
    virtual double predictQValue(vector<double>& environment, vector<double>& action);
    virtual double learnStimulus(vector<double>& prevEnv, vector<double>& action, double& reward);
    void UpdateFinalState(double& res);

    virtual void _update();
    virtual void _start();

    void SetNumberOfActions(int& actionCount);
    void enterExploitMode();
    void enterExploreMode();
    void setDirectReward(bool& value);
    void setBelman(bool& value);
    double getEpsilon();
    double getdoubleQEpsilon();

  protected:
    // Q LEARNING VARIABLES --------------------------------------------------
    // Q learning dynamics
    float intialEpsilon = 1.0f;
    float epsilon = 1.0f;
    float epsilonDecay = 0.001f;
    float discountParameter = 0.3f;
    float learningRate = 0.5f;
    bool  useBelman = false;
    bool  usedDirectReward = false;

    // Q learning
    double Q_old = -1.0;
    double Q_new = -1.0;
    vector<double> prevEnvironment;
    int selectedAction = 0;
    double immediateReward = 0.0;
    float tableSelectionRand = 0.0;
    int selectedTable = 0;
    int previousTable = 0;

    // DOUBLE Q_LEARNING VARIABLES -------------------------------------------
        // Q learning dynamics
    float dintialEpsilon = 1.0f;
    float depsilon = 1.0f;
    float depsilonDecay = 0.001f;
    float ddiscountParameter = 0.1f;
    float dlearningRate = 0.5f;
    bool  duseBelman = false;
    bool  dusedDirectReward = false;

    // Q learning
    double dQ_old = -1.0;
    double dQ_new = -1.0;
    vector<double> dprevEnvironment;
    int dselectedAction = 0;
    double dimmediateReward = 0.0;

    int actionCount = 0;

    void update();
    void start();

    vector<double> generateActionVector(int& selectedAction);
    void PhaseTwo(vector<double>& environment, vector<int>& availableActions);
    void dPhaseTwo(vector<double>& environment, vector<int>& availableActions);
};
#endif