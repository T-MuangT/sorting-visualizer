# Source tree build

set(SOURCES
    main.cpp
    menus/ExchangeSortMenu.cpp
    stats/SortStats.cpp
    visualizer/TerminalVisualizer.cpp
    randomizer/ArrayGenerator.cpp
    randomizer/ArrayRandomizer.cpp
    randomizer/ArrayReversed.cpp
    randomizer/ArrayNearlySorted.cpp
    algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    algorithms/exchange-sort/bubble-sort/CocktailShakerSort.cpp
    algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.cpp
    algorithms/exchange-sort/bubble-sort/OddEvenSort.cpp
    algorithms/exchange-sort/bubble-sort/CombSort.cpp
    algorithms/exchange-sort/bubble-sort/OptimizedCombSort.cpp
    algorithms/exchange-sort/partition-sort/CircleSort.cpp
    algorithms/exchange-sort/partition-sort/LomutoQuickSort.cpp
    algorithms/exchange-sort/partition-sort/HoareQuickSort.cpp
    algorithms/exchange-sort/partition-sort/DualPivotQuickSort.cpp
    algorithms/exchange-sort/partition-sort/StableQuickSort.cpp
)

add_executable(sorting-visualizer ${SOURCES})

target_include_directories(sorting-visualizer PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(sorting-visualizer PRIVATE OpenMP::OpenMP_CXX)

if(MSVC)
    target_compile_options(sorting-visualizer PRIVATE /W4)
else()
    target_compile_options(sorting-visualizer PRIVATE -Wall -Wextra -pedantic)
endif()
