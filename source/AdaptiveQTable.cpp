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
