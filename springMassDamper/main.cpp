#include <iostream>
#include <chrono>
#include <random>
#include <array>
#include "include/springMassDamper.h"

using namespace std;

int main()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    array<double, 7> intervals {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    array<double, 7> weights {0.0, 0.1, 0.2, 0.3, 0.2, 0.1, 0.1 };
    piecewise_linear_distribution<double> rnd_x(intervals.begin(),intervals.end(),weights.begin());
    unsigned int trials = 0;
    cout << "How many times shall the input be sampled? ";
    cin >> trials;
    system_workspace * SMD_wkspc = SpringMassDamper->Get_workspace();
    vector<vector<double>> step_result;
    for (unsigned int i = 0; i < trials; i++)
    {
    	*SMD_wkspc->input->input_array[0] = rnd_x(generator);
    	step_result = SpringMassDamper->exec_step();
        cout << "[ ";
        for (unsigned int x = 0; x < step_result.size(); x++)
        {
                cout << step_result[x][0] << " ";
        }
        cout << "]\n";
    }

    return 0;
}
