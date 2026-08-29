cmake_minimum_required(VERSION 3.20)
project(SortingVisualizer VERSION 1.1 LANGUAGES CXX)

# Require C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenMP package for parallel sorting implementation
find_package(OpenMP REQUIRED)

# Include directories
include_directories(include)

# Gather source files explicitly
set(SOURCES
    src/main.cpp
    src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    src/algorithms/exchange-sort/bubble-sort/CocktailShakerSort.cpp
    src/algorithms/exchange-sort/bubble-sort/CircleSort.cpp
    src/algorithms/exchange-sort/bubble-sort/OddEvenSort.cpp
    src/algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.cpp
    src/algorithms/exchange-sort/bubble-sort/CombSort.cpp
    src/algorithms/exchange-sort/bubble-sort/OptimizedCombSort.cpp
    # src/algorithms/exchange-sort/quick-sort/LomutoQuickSort.cpp
    src/randomizer/ArrayGenerator.cpp
    src/randomizer/ArrayRandomizer.cpp
    src/randomizer/ArrayReversed.cpp
    src/randomizer/ArrayNearlySorted.cpp
    src/stats/SortStats.cpp
    src/visualizer/TerminalVisualizer.cpp
)

# Define executable target
add_executable(sorting-visualizer ${SOURCES})

# Link OpenMP libraries and apply compiler flags
target_link_libraries(sorting-visualizer PRIVATE OpenMP::OpenMP_CXX)

# Set target compile options for warning levels
if(MSVC)
    target_compile_options(sorting-visualizer PRIVATE /W4)
else()
    target_compile_options(sorting-visualizer PRIVATE -Wall -Wextra -pedantic)
endif()