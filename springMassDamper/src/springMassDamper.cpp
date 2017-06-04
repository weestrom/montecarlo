#include "springMassDamper.h"

system_config cfg {
    0.01, //step_size
    STEP_TYPE_INIT_VAL //step_type
};

double* x = new double(0); //m
double* v = new double(0); //m/s
double* a = new double(0); //m/s^2
double* m = new double(1); //kg
double* k = new double(1); //N/m
double* b = new double(1); //N*s/m

double * in_array[] = {x, v, a};
double * out_array[] = {x, v, a};
double * st_array[] = {m, k, b};

input_struct in_struct {
    3,
    in_array
};

output_struct out_struct {
    3,
    out_array
};

state_struct st_struct {
    3,
    st_array
};

system_workspace wkspc {
    0.01, //time_step
    &in_struct,
    &out_struct,
    &st_struct
};

int stepfun(system_config * cfg, system_workspace * wkspc) {
    *wkspc->output->output_array[2] = -1 * (*wkspc->input->input_array[0] * *wkspc->state->state_array[1] + *wkspc->input->input_array[1] * *wkspc->state->state_array[2])/
                                            *wkspc->state->state_array[0];
    *wkspc->output->output_array[1] = *wkspc->input->input_array[1] + *wkspc->output->output_array[2] * cfg->step_size;
    *wkspc->output->output_array[0] = *wkspc->input->input_array[0] + *wkspc->output->output_array[1] * cfg->step_size + 0.5 * (*wkspc->output->output_array[2] * pow(cfg->step_size,2.0));

    return 0;

}

testSystem * SpringMassDamper = new testSystem(*stepfun, &cfg, &wkspc);
