#ifndef TESTSYSTEM_H
#define TESTSYSTEM_H

#include <vector>
#include <math.h>

#define STEP_TYPE_INIT_VAL 0x0
#define STEP_TYPE_DISCRETE_INPUT 0x1


struct system_config {
    double step_size;
    unsigned int step_type;
};

struct input_struct {
    unsigned int input_len;
    double **input_array;
};

struct output_struct {
    unsigned int output_len;
    double **output_array;
};

struct state_struct {
    unsigned int state_len;
    double **state_array;
};

struct system_workspace {
    double time_step;
    input_struct * input;
    output_struct * output;
    state_struct * state;
};

typedef int (*step_function)(system_config *, system_workspace *);

class testSystem
{
    public:
        testSystem(step_function step, system_config * cfg, system_workspace * wkspc);
        virtual ~testSystem();

        system_config * Get_config() { return config; };
        system_workspace * Get_workspace() { return workspace; };

        std::vector<std::vector<double>> exec_step();
        void init();

    protected:

    private:
        step_function m_step;
        system_config * config;
        system_workspace * workspace;
};

#endif // SYSTEM_H
