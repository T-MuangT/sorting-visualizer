# Test suite build

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)
link_libraries(OpenMP::OpenMP_CXX)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_library(visualization_session_test SHARED
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
)

target_include_directories(visualization_session_test
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src
)

set_target_properties(visualization_session_test PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(ARRAY_VISUALIZER_TEST_SOURCES
    array_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
)

set(AUXIL_VISUALIZER_TEST_SOURCES
    auxil_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
)

set(TABLE_VISUALIZER_TEST_SOURCES
    table_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(COUNT_VISUALIZER_TEST_SOURCES
    count_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(GRAPH_VISUALIZER_TEST_SOURCES
    graph_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalGraphVisualizer.cpp
)

set(RANDOMIZER_TEST_SOURCES
    randomizer_test.cpp
    ../src/randomizer/ArrayGenerator.cpp
    ../src/randomizer/ArrayRandomizer.cpp
    ../src/randomizer/ArrayReversed.cpp
    ../src/randomizer/ArrayNearlySorted.cpp
)

set(EXCHANGE_BUBBLE_TEST_SOURCES
    exchange_bubble_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CocktailShakerSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OddEvenSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CombSort.cpp
)

set(EXCHANGE_PARTITION_TEST_SOURCES
    exchange_partition_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/ArraySplitRange.cpp
    ../src/algorithms/exchange-sort/partition-sort/CircleSort.cpp
)

set(SINGLE_PIVOT_SORT_TEST_SOURCES
    single_pivot_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/ArraySplitRange.cpp
    ../src/algorithms/PivotSelection.cpp
    ../src/algorithms/exchange-sort/partition-sort/LomutoQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/HoareQuickSort.cpp
)

set(DUAL_PIVOT_SORT_TEST_SOURCES
    dual_pivot_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/ArraySplitRange.cpp
    ../src/algorithms/PivotSelection.cpp
    ../src/algorithms/exchange-sort/partition-sort/DualPivotQuickSort.cpp
)

set(STABLE_QUICK_TEST_SOURCES
    stable_quick_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/ArraySplitRange.cpp
    ../src/algorithms/exchange-sort/partition-sort/StableQuickSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
    ../src/visualizer/terminal/TerminalGraphVisualizer.cpp
)

set(SELECTION_SELECTION_TEST_SOURCES
    selection_selection_test.cpp
    ../src/algorithms/selection-sort/selection-sort/SelectionSort.cpp
    ../src/algorithms/selection-sort/selection-sort/DoubleSelectionSort.cpp
    ../src/algorithms/selection-sort/selection-sort/CycleSort.cpp
)

set(SELECTION_HEAP_TEST_SOURCES
    selection_heap_test.cpp
    ../src/algorithms/selection-sort/heap-sort/MaxHeapSort.cpp
    ../src/algorithms/selection-sort/heap-sort/MinHeapSort.cpp
    ../src/algorithms/selection-sort/heap-sort/SmoothSort.cpp
)

set(INSERTION_INSERTION_TEST_SOURCES
    insertion_insertion_test.cpp
    ../src/algorithms/insertion-sort/insertion-sort/InsertionSort.cpp
    ../src/algorithms/insertion-sort/insertion-sort/BinaryInsertionSort.cpp
    ../src/algorithms/insertion-sort/insertion-sort/ShellSort.cpp
)

set(INSERTION_TREE_TEST_SOURCES
    insertion_tree_test.cpp
    ../src/algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.cpp
    ../src/algorithms/TreeStructure.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
)

set(MERGE_SORT_TEST_SOURCES
    merge_sort_test.cpp
    ../src/algorithms/merge-sort/MergeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
)

set(DISTRIBUTION_PIGEONHOLE_TEST_SOURCES
    distribution_pigeonhole_test.cpp
    ../src/algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(DISTRIBUTION_COUNTING_TEST_SOURCES
    distribution_counting_test.cpp
    ../src/algorithms/distribution-sort/counting-sort/CountingSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(EARLY_CUTOFF_SORT_TEST_SOURCES
    early_cutoff_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedBubbleSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.cpp
)

set(PARALLEL_SORT_TEST_SOURCES
    parallel_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedOddEvenSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCombSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/OptimizedCircleSort.cpp
)

set(INTEGRATION_TEST_SOURCES
    integration_test.cpp
    ../src/randomizer/ArrayGenerator.cpp
    ../src/randomizer/ArrayRandomizer.cpp
    ../src/randomizer/ArrayReversed.cpp
    ../src/randomizer/ArrayNearlySorted.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/TreeStructure.cpp
    ../src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    ../src/algorithms/merge-sort/MergeSort.cpp
    ../src/algorithms/distribution-sort/counting-sort/CountingSort.cpp
    ../src/algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
    ../src/visualizer/terminal/TerminalGraphVisualizer.cpp
)

set(TEST_TARGETS
    array_visualizer_test
    auxil_visualizer_test
    table_visualizer_test
    count_visualizer_test
    graph_visualizer_test
    randomizer_test
    exchange_bubble_test
    exchange_partition_test
    single_pivot_sort_test
    dual_pivot_sort_test
    stable_quick_test
    selection_selection_test
    selection_heap_test
    insertion_insertion_test
    insertion_tree_test
    merge_sort_test
    distribution_pigeonhole_test
    distribution_counting_test
    early_cutoff_sort_test
    parallel_sort_test
    integration_test
)

# Unified Loop for Executables, Properties, and CTest
foreach(test_target IN LISTS TEST_TARGETS)
    string(TOUPPER ${test_target} upper_name)
    add_executable(${test_target} ${${upper_name}_SOURCES})

    target_include_directories(${test_target} PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${test_target} PRIVATE OpenMP::OpenMP_CXX)
    if(MSVC)
        target_compile_options(${test_target} PRIVATE /W4)
    else()
        target_compile_options(${test_target} PRIVATE -Wall -Wextra -pedantic)
    endif()

    add_test(NAME ${test_target} COMMAND $<TARGET_FILE:${test_target}>)
endforeach()

# Custom target referencing the single list
add_custom_target(tests DEPENDS ${TEST_TARGETS})