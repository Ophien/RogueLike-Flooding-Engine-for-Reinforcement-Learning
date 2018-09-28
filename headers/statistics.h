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