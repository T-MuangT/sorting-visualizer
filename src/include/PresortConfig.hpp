#ifndef PRESORT_CONFIG_HPP
#define PRESORT_CONFIG_HPP

#include <cstddef>

#include "ArrayGenerator.hpp"

struct PresortConfig {
    Pattern pattern = Pattern::UniformRandom;
    std::size_t arraySize = 32;
    int delayMs = 100;
};

#endif // PRESORT_CONFIG_HPP