#include "system.h"

system::system(step_function step, system_config * cfg, system_workspace * wkspc)
{
    m_step = step;
    config = cfg;
    workspace = wkspc;
}

system::~system()
{
    //dtor
}


std::vector<std::vector<double>> system::exec_step()
{
    std::vector<std::vector<double>> output_vec_history;
        int retval = 0;
        switch(config->step_type) {
        case STEP_TYPE_INIT_VAL:
            bool stable;
            do {
                for(unsigned int it = 0; it < workspace->output->output_len; it++) {
                    output_vec_history.back().push_back(**(workspace->output->output_array + it));
                }
                retval = m_step(config, workspace);
                stable = true;
                for(unsigned int it = 0; it < workspace->output->output_len; it++) {
                    stable = stable && abs((**(workspace->output->output_array + it) - output_vec_history.back()[it])/ output_vec_history.back()[it]) < 0.001;
                }

            } while(!stable);
            break;
        case STEP_TYPE_DISCRETE_INPUT:
            //TODO: implement this
            retval = m_step(config, workspace);
            for(unsigned int it = 0; it < workspace->output->output_len; it++) {
                output_vec_history.back().push_back(**(workspace->output->output_array + it));
            }

        };
        return output_vec_history;
}
