#include "testSystem.h"

testSystem::testSystem(step_function step, system_config * cfg, system_workspace * wkspc)
{
    m_step = step;
    config = cfg;
    workspace = wkspc;
}

testSystem::~testSystem()
{
    //dtor
}


std::vector<std::vector<double>> testSystem::exec_step()
{
    std::vector<std::vector<double>> output_vec_history;
    output_vec_history.reserve(10000);
        int retval = 0;
        switch(config->step_type) {
        case STEP_TYPE_INIT_VAL:
            bool stable;
            do {
            	std::vector<double> * vec = new std::vector<double>;
            	vec->reserve(workspace->output->output_len);
            	output_vec_history.push_back(*vec);
            	for(unsigned int it = 0; it < workspace->output->output_len; it++) {
                    output_vec_history.back().push_back(**(workspace->output->output_array + it));
                }
                retval = m_step(config, workspace);
                stable = true;
                for(unsigned int it = 0; it < workspace->output->output_len; it++) {
                    stable = stable && (abs(**(workspace->output->output_array + it) - output_vec_history.back()[it]) < 0.0001);
                }

            } while(!stable && output_vec_history.size() < 10000 );
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
