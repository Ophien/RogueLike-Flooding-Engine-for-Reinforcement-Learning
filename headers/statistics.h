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

#ifndef STATISTICS_H
#define STATISTICS_H

#include <math.h>
#include <vector>
#include <limits>
#include <map>

using namespace std;

namespace statistics
{
#define MIN_DOUBLE -std::numeric_limits<double>::max();
#define MAX_DOUBLE std::numeric_limits<double>::max();

double get_higher_frequency_value(map<double, int> &requency);

class observations
{
public:
  observations(int sample_size);
  ~observations();

  void moveData(double val);
  double maxValue();
  double minValue();
  void insertSamplesIntoMatrix(double *samples);
  double *getSamplesFromMatrix(unsigned int index);
  vector<double *> &getMatrix();
  vector<double *> getTransposed();
  void saveCSV(const char *path);

  // COLUMN OPERATIONS
  double column_statistics(bool& keep_positive, double& shift);

private:
  vector<double *> data;
  unsigned int sample_size;

  vector<double> sum;
  vector<double> max;
  vector<double> min;
  vector<double> mode;
  vector<double> mean;
  vector<double> upper_err;
  vector<double> lower_err;
  vector<double> dev;
  vector<double> var;
  vector<double> above_mean_sum;
  vector<double> above_mean_max;
  vector<double> above_mean_min;
  vector<double> above_mean_mode;
  vector<double> above_mean_mean;
  vector<double> above_mean_dev;
  vector<double> above_mean_var;
  vector<double> bellow_mean_sum;
  vector<double> bellow_mean_max;
  vector<double> bellow_mean_min;
  vector<double> bellow_mean_mode;
  vector<double> bellow_mean_mean;
  vector<double> bellow_mean_dev;
  vector<double> bellow_mean_var;
};
} // namespace statistics

#endif
