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

set(TERMINAL_ARRAY_VISUALIZER_TEST_SOURCES
    terminal/terminal_array_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
)

set(TERMINAL_AUXIL_VISUALIZER_TEST_SOURCES
    terminal/terminal_auxil_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
)

set(TERMINAL_TABLE_VISUALIZER_TEST_SOURCES
    terminal/terminal_table_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(TERMINAL_COUNT_VISUALIZER_TEST_SOURCES
    terminal/terminal_count_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(TERMINAL_GRAPH_VISUALIZER_TEST_SOURCES
    terminal/terminal_graph_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/terminal/TerminalGraphVisualizer.cpp
)

set(RANDOMIZER_TEST_SOURCES
    randomizer/randomizer_test.cpp
    ../src/randomizer/ArrayGenerator.cpp
    ../src/randomizer/ArrayRandomizer.cpp
    ../src/randomizer/ArrayReversed.cpp
    ../src/randomizer/ArrayNearlySorted.cpp
)

set(EXCHANGE_BUBBLE_TEST_SOURCES
    algorithms/exchange_bubble_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CocktailShakerSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OddEvenSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CombSort.cpp
)

set(EXCHANGE_PARTITION_TEST_SOURCES
    algorithms/exchange_partition_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/ArraySplitRange.cpp
    ../src/algorithms/exchange-sort/partition-sort/CircleSort.cpp
)

set(SINGLE_PIVOT_SORT_TEST_SOURCES
    algorithms/single_pivot_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/ArraySplitRange.cpp
    ../src/algorithms/PivotSelection.cpp
    ../src/algorithms/exchange-sort/partition-sort/LomutoQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/HoareQuickSort.cpp
)

set(DUAL_PIVOT_SORT_TEST_SOURCES
    algorithms/dual_pivot_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/ArraySplitRange.cpp
    ../src/algorithms/PivotSelection.cpp
    ../src/algorithms/exchange-sort/partition-sort/DualPivotQuickSort.cpp
)

set(STABLE_QUICK_TEST_SOURCES
    algorithms/stable_quick_test.cpp
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
    algorithms/selection_selection_test.cpp
    ../src/algorithms/selection-sort/selection-sort/SelectionSort.cpp
    ../src/algorithms/selection-sort/selection-sort/DoubleSelectionSort.cpp
    ../src/algorithms/selection-sort/selection-sort/CycleSort.cpp
)

set(SELECTION_HEAP_TEST_SOURCES
    algorithms/selection_heap_test.cpp
    ../src/algorithms/selection-sort/heap-sort/MaxHeapSort.cpp
    ../src/algorithms/selection-sort/heap-sort/MinHeapSort.cpp
    ../src/algorithms/selection-sort/heap-sort/SmoothSort.cpp
)

set(INSERTION_INSERTION_TEST_SOURCES
    algorithms/insertion_insertion_test.cpp
    ../src/algorithms/insertion-sort/insertion-sort/InsertionSort.cpp
    ../src/algorithms/insertion-sort/insertion-sort/BinaryInsertionSort.cpp
    ../src/algorithms/insertion-sort/insertion-sort/ShellSort.cpp
)

set(INSERTION_TREE_TEST_SOURCES
    algorithms/insertion_tree_test.cpp
    ../src/algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.cpp
    ../src/algorithms/TreeStructure.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
)

set(MERGE_SORT_TEST_SOURCES
    algorithms/merge_sort_test.cpp
    ../src/algorithms/merge-sort/MergeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
)

set(DISTRIBUTION_PIGEONHOLE_TEST_SOURCES
    algorithms/distribution_pigeonhole_test.cpp
    ../src/algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(DISTRIBUTION_COUNTING_TEST_SOURCES
    algorithms/distribution_counting_test.cpp
    ../src/algorithms/distribution-sort/counting-sort/CountingSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/terminal/TerminalArrayVisualizer.cpp
    ../src/visualizer/terminal/TerminalTableVisualizer.cpp
)

set(EARLY_CUTOFF_SORT_TEST_SOURCES
    algorithms/early_cutoff_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedBubbleSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.cpp
)

set(PARALLEL_SORT_TEST_SOURCES
    algorithms/parallel_sort_test.cpp
    ../src/algorithms/PairwiseCompareSwap.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedOddEvenSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCombSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/OptimizedCircleSort.cpp
)

set(TERMINAL_INTEGRATION_TEST_SOURCES
    terminal/terminal_integration_test.cpp
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

set(GRAPHICS_ARRAY_VISUALIZER_TEST_SOURCES
    graphics/graphics_array_visualizer_test.cpp
)

set(GRAPHICS_AUXIL_VISUALIZER_TEST_SOURCES
    graphics/graphics_auxil_visualizer_test.cpp
)

set(GRAPHICS_TABLE_VISUALIZER_TEST_SOURCES
    graphics/graphics_table_visualizer_test.cpp
)

set(GRAPHICS_COUNT_VISUALIZER_TEST_SOURCES
    graphics/graphics_count_visualizer_test.cpp
)

set(GRAPHICS_GRAPH_VISUALIZER_TEST_SOURCES
    graphics/graphics_graph_visualizer_test.cpp
)

set(GRAPHICS_INTEGRATION_TEST_SOURCES
    graphics/graphics_integration_test.cpp
)

set(GRAPHICS_DASHBOARD_INTEGRATION_TEST_SOURCES
    graphics/graphics_visualizer_dashboard_test.cpp
)

set(TEST_TARGETS
    terminal_array_visualizer_test
    terminal_auxil_visualizer_test
    terminal_table_visualizer_test
    terminal_count_visualizer_test
    terminal_graph_visualizer_test
    graphics_array_visualizer_test
    graphics_auxil_visualizer_test
    graphics_table_visualizer_test
    graphics_count_visualizer_test
    graphics_graph_visualizer_test
    graphics_dashboard_integration_test
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
    terminal_integration_test
    graphics_integration_test
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

foreach(test_target IN ITEMS
        graphics_array_visualizer_test
        graphics_auxil_visualizer_test
        graphics_table_visualizer_test
        graphics_count_visualizer_test
        graphics_graph_visualizer_test
        graphics_integration_test
        graphics_dashboard_integration_test)
    target_link_libraries(${test_target} PRIVATE guivisual wxWidgets::wxWidgets)
    set_tests_properties(${test_target} PROPERTIES SKIP_RETURN_CODE 77)
endforeach()

# Custom target referencing the single list
add_custom_target(tests DEPENDS ${TEST_TARGETS})
