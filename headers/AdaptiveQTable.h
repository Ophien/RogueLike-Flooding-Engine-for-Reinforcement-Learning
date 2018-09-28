#ifndef ADAPTIVE_Q_TABLE_H
#define ADAPTIVE_Q_TABLE_H

#include <string.h>
#include <map>
#include <vector>

using namespace std;

class FalconAdaptiveQTable
{
  public:
    FalconAdaptiveQTable();
    ~FalconAdaptiveQTable();
    virtual string buildString(vector<double>& vec);
    virtual double predict(vector<double>& environment, vector<double>& action, double &reward, bool& learn);
    virtual int neuronCount();
    virtual void clear();

    map<string, double> neurons;
};

#endif