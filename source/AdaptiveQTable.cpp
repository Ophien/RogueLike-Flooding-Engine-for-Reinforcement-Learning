#include "AdaptiveQTable.h"

FalconAdaptiveQTable::FalconAdaptiveQTable()
{
}

FalconAdaptiveQTable::~FalconAdaptiveQTable()
{
}

string FalconAdaptiveQTable::buildString(vector<double>& vec)
{
    string ret = "";

    for (int i = 0; i < vec.size(); i++)
    {
        int bin_value = (int)vec[i];
        ret.append(to_string(bin_value));
    }

    return ret;
}

double FalconAdaptiveQTable::predict(vector<double>& environment, vector<double>& action, double &reward, bool& learn)
{
    string envKey = buildString(environment);
    string actKey = buildString(action);
    string finalKey = envKey.append(actKey);

    if (neurons.find(finalKey) == neurons.end()){
        neurons[finalKey] = 0.5;
    }else{
        if(learn)
            neurons[finalKey] = reward;
    }

    return neurons[finalKey];
}

void FalconAdaptiveQTable::clear(){
    neurons.clear();
}

int FalconAdaptiveQTable::neuronCount()
{
    int count = neurons.size();

    return count;
}