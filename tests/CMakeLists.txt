# Test tree build

enable_testing()

set(RANDOMIZER_TEST_SOURCES
    randomizer_test.cpp
    ../src/randomizer/ArrayGenerator.cpp
    ../src/randomizer/ArrayRandomizer.cpp
    ../src/randomizer/ArrayReversed.cpp
    ../src/randomizer/ArrayNearlySorted.cpp
)

set(EXCHANGE_BUBBLE_TEST_SOURCES
    exchange_bubble_test.cpp
    ../src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CocktailShakerSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OddEvenSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CombSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCombSort.cpp
)

set(EXCHANGE_PARTITION_TEST_SOURCES
    exchange_partition_test.cpp
    ../src/algorithms/exchange-sort/partition-sort/CircleSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/LomutoQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/HoareQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/DualPivotQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/StableQuickSort.cpp
)

set(VISUALIZER_TEST_SOURCES
    visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/TerminalVisualizer.cpp
)

set(INTEGRATION_TEST_SOURCES
    integration_test.cpp
    ../src/randomizer/ArrayGenerator.cpp
    ../src/randomizer/ArrayRandomizer.cpp
    ../src/randomizer/ArrayReversed.cpp
    ../src/randomizer/ArrayNearlySorted.cpp
    ../src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/LomutoQuickSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/TerminalVisualizer.cpp
)

add_executable(randomizer_test ${RANDOMIZER_TEST_SOURCES})
add_executable(exchange_bubble_test ${EXCHANGE_BUBBLE_TEST_SOURCES})
add_executable(exchange_partition_test ${EXCHANGE_PARTITION_TEST_SOURCES})
add_executable(visualizer_test ${VISUALIZER_TEST_SOURCES})
add_executable(integration_test ${INTEGRATION_TEST_SOURCES})

add_test(NAME randomizer_test COMMAND randomizer_test)
add_test(NAME exchange_bubble_test COMMAND exchange_bubble_test)
add_test(NAME exchange_partition_test COMMAND exchange_partition_test)
add_test(NAME visualizer_test COMMAND visualizer_test)
add_test(NAME integration_test COMMAND integration_test)

foreach(test_target IN ITEMS randomizer_test exchange_bubble_test exchange_partition_test visualizer_test integration_test)
    target_include_directories(${test_target} PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)
    if(MSVC)
        target_compile_options(${test_target} PRIVATE /W4)
    else()
        target_compile_options(${test_target} PRIVATE -Wall -Wextra -pedantic)
    endif()
endforeach()
