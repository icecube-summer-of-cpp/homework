

#ifndef CPPSUMMER_QUIZ1_H
#define CPPSUMMER_QUIZ1_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <complex>

inline void enable_stream_exception(std::ios& io);

enum return_vals{
    SUCCESS,
    COULD_NOT_OPEN_FILE,
    COULD_NOT_READ_FILE,
    NO_INPUT_FILE,
};

#endif //CPPSUMMER_QUIZ1_H
