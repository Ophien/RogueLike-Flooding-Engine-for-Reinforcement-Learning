#include "statistics.h"

double statistics::get_higher_frequency_value(map<double, int> &frequency)
{
    int higher_freq = 0;
    double higher_val = 0.0;
    map<double, int>::iterator it = frequency.begin();
    for (; it != frequency.end(); it++)
    {
        int count = it->second;
        if (count > higher_freq)
        {
            higher_freq = count;
            higher_val = it->first;
        }
    }
    return higher_val;
}

void statistics::observations::moveData(double val)
{
    for (int column = 0; column < sample_size; column++)
        for (unsigned int line = 0; line < data.size(); line++)
            data[line][column] += val;
}

double statistics::observations::maxValue()
{
    double matrix_max = MIN_DOUBLE;

    // compute sum, max, mid, mode
    for (int column = 0; column < sample_size; column++)
    {
        for (unsigned int line = 0; line < data.size(); line++)
        {
            double value = data[line][column];
            if (value > matrix_max)
                matrix_max = value;
        }
    }

    return matrix_max;
}

double statistics::observations::minValue()
{
    double matrix_min = MAX_DOUBLE;

    // compute sum, max, mid, mode
    for (int column = 0; column < sample_size; column++)
    {
        for (unsigned int line = 0; line < data.size(); line++)
        {
            double value = data[line][column];
            if (value < matrix_min)
                matrix_min = value;
        }
    }

    return matrix_min;
}

vector<double *> statistics::observations::getTransposed()
{
}

double statistics::observations::column_statistics(bool &keep_positive, double &shift)
{
    // need to norm all values for then to be above 0, consequently preventing operations with negative values that could possibly turn the filnal results biased
    bool dataMoved = false;
    double minVal = 0.0;

    if (keep_positive)
    {
        minVal = minValue();

        if (minVal < 0)
        {
            minVal = minVal * -1.0; // turn it positive
            moveData(minVal);       // move values up
            dataMoved = true;
        }
    }
    else
    {
        if (shift > 0.0)
        {
            moveData(shift);
            dataMoved = true;
        }
    }

    // compute sum, max, mid, mode
    for (int column = 0; column < sample_size; column++)
    {
        double column_sum = 0.0;
        double column_max = MIN_DOUBLE;
        double column_min = MAX_DOUBLE;
        double column_mean = 0.0;
        double column_mode = 0.0;
        double column_dev = 0.0;
        double column_var = 0.0;
        map<double, int> column_value_frequency;
        for (unsigned int line = 0; line < data.size(); line++)
        {
            double value = data[line][column];

            // compute statistics
            column_sum += value;

            // compute max
            if (value > column_max)
                column_max = value;

            // compute min
            if (value < column_min)
                column_min = value;

            // count frequency
            column_value_frequency[value] += 1;
        }

        // setup mean
        column_mean = column_sum / (double)data.size();

        // setup mode
        column_mode = get_higher_frequency_value(column_value_frequency);

        // compute var and dev and values above and bellow mean
        unsigned int above_mean_count = 0;
        unsigned int bellow_mean_count = 0;

        // above mean values
        double above_mean_column_sum = 0.0;
        double above_mean_column_max = MIN_DOUBLE;
        double above_mean_column_min = MAX_DOUBLE;
        double above_mean_column_mean = 0.0;
        double above_mean_column_mode = 0.0;
        double above_mean_column_dev = 0.0;
        double above_mean_column_var = 0.0;
        map<double, int> above_mean_column_value_frequency;

        // bellow mean values
        double bellow_mean_column_sum = 0.0;
        double bellow_mean_column_max = MIN_DOUBLE;
        double bellow_mean_column_min = MAX_DOUBLE;
        double bellow_mean_column_mean = 0.0;
        double bellow_mean_column_mode = 0.0;
        double bellow_mean_column_dev = 0.0;
        double bellow_mean_column_var = 0.0;
        map<double, int> bellow_mean_column_value_frequency;

        for (unsigned int line = 0; line < data.size(); line++)
        {
            double value = data[line][column];

            // compute var
            column_var += (value - column_mean) * (value - column_mean);

            // compute bellow or above mean statistics, sum, min, max, mode
            if (value >= column_mean)
            {
                above_mean_count++;

                above_mean_column_sum += value;

                if (value > above_mean_column_max)
                    above_mean_column_max = value;

                if (value < above_mean_column_min)
                    above_mean_column_min = value;

                // count frequency
                above_mean_column_value_frequency[value] += 1;
            }

            if (value < column_mean)
            {
                bellow_mean_count++;

                bellow_mean_column_sum += value;

                if (value > bellow_mean_column_max)
                    bellow_mean_column_max = value;

                if (value < bellow_mean_column_min)
                    bellow_mean_column_min = value;

                // count frequency
                bellow_mean_column_value_frequency[value] += 1;
            }
        }

        // finishing to compute var and deviation
        //column_var /= (double)(data.size() - 1); // sample var
        column_var /= (double)data.size(); // population var
        column_dev = sqrt(column_var);     // population dev

        // calculate bellow and above mean mean
        bellow_mean_column_mean = bellow_mean_column_sum / (double)bellow_mean_count;
        bellow_mean_column_mode = get_higher_frequency_value(bellow_mean_column_value_frequency);

        above_mean_column_mean = above_mean_column_sum / (double)above_mean_count;
        above_mean_column_mode = get_higher_frequency_value(above_mean_column_value_frequency);

        for (unsigned int line = 0; line < data.size(); line++)
        {
            double value = data[line][column];

            // compute bellow or above mean statistics, var
            if (value >= column_mean)
                above_mean_column_var += (value - above_mean_column_mean) * (value - above_mean_column_mean);

            if (value < column_mean)
                bellow_mean_column_var += (value - bellow_mean_column_mean) * (value - bellow_mean_column_mean);
        }

        above_mean_column_var /= (double)above_mean_count;   // population var
        above_mean_column_dev = sqrt(above_mean_column_var); // population dev

        bellow_mean_column_var /= (double)bellow_mean_count;   // population var
        bellow_mean_column_dev = sqrt(bellow_mean_column_var); // population dev

        // insert variables into output vectors containing statistical measurements
        sum.push_back(column_sum);
        max.push_back(column_max);
        min.push_back(column_min);
        mode.push_back(column_mode);
        mean.push_back(column_mean);
        dev.push_back(column_dev);
        var.push_back(column_var);
        above_mean_sum.push_back(above_mean_column_sum);
        above_mean_max.push_back(above_mean_column_max);
        above_mean_min.push_back(above_mean_column_min);
        above_mean_mode.push_back(above_mean_column_mode);
        above_mean_mean.push_back(above_mean_column_mean);
        above_mean_dev.push_back(above_mean_column_dev);
        above_mean_var.push_back(above_mean_column_var);
        bellow_mean_sum.push_back(bellow_mean_column_sum);
        bellow_mean_max.push_back(bellow_mean_column_max);
        bellow_mean_min.push_back(bellow_mean_column_min);
        bellow_mean_mode.push_back(bellow_mean_column_mode);
        bellow_mean_mean.push_back(bellow_mean_column_mean);
        bellow_mean_dev.push_back(bellow_mean_column_dev);
        bellow_mean_var.push_back(bellow_mean_column_var);
    }

    // sum err
    for (unsigned int i = 0; i < mean.size(); i++)
    {
        upper_err.push_back(mean[i] + above_mean_dev[i]);
        lower_err.push_back(mean[i] - bellow_mean_dev[i]);
    }

    // move data back to its original position
    if (dataMoved)
    {
        if (shift > 0)
        {
            moveData(shift * -1.0);
        }
        else
        {
            minVal = minVal * -1.0; // turn it negative
            moveData(minVal);
        }
    }
}

void statistics::observations::saveCSV(const char *path)
{
    int total_variables = sum.size();

    FILE *f = fopen(path, "w");

    if (f)
    {
        fprintf(f, "sum,max,min,mode,mean,upper,lower,dev,var,above_mean_sum,above_mean_max,above_mean_min,above_mean_mode,above_mean_mean,above_mean_dev,above_mean_var,bellow_mean_sum,bellow_mean_max,bellow_mean_min,bellow_mean_mode,bellow_mean_mean,bellow_mean_dev,bellow_mean_var\n");
        for (int i = 0; i < total_variables; i++)
        {
            fprintf(f,
                    "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
                    sum[i], max[i], min[i], mode[i], mean[i], upper_err[i], lower_err[i], dev[i], var[i], above_mean_sum[i], above_mean_max[i], above_mean_min[i], above_mean_mode[i], above_mean_mean[i], above_mean_dev[i], above_mean_var[i], bellow_mean_sum[i], bellow_mean_max[i], bellow_mean_min[i], bellow_mean_mode[i], bellow_mean_mean[i], bellow_mean_dev[i], bellow_mean_var[i]);
        }
    }

    fclose(f);
}

statistics::observations::observations(int sample_size)
{
    this->sample_size = sample_size;
}

statistics::observations::~observations()
{
}

void statistics::observations::insertSamplesIntoMatrix(double *samples)
{
    data.push_back(samples);
}