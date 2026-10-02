# Test tree build

set(ARRAY_VISUALIZER_TEST_SOURCES
    array_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/TerminalArrayVisualizer.cpp
)

set(TABLE_VISUALIZER_TEST_SOURCES
    table_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/TerminalTableVisualizer.cpp
)

set(COUNT_VISUALIZER_TEST_SOURCES
    count_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/TerminalTableVisualizer.cpp
)

set(GRAPH_VISUALIZER_TEST_SOURCES
    graph_visualizer_test.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/TerminalGraphVisualizer.cpp
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
    ../src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CocktailShakerSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OddEvenSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedOddEvenSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/CombSort.cpp
    ../src/algorithms/exchange-sort/bubble-sort/OptimizedCombSort.cpp
)

set(EXCHANGE_PARTITION_TEST_SOURCES
    exchange_partition_test.cpp
    ../src/algorithms/exchange-sort/partition-sort/CircleSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/OptimizedCircleSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/LomutoQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/HoareQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/DualPivotQuickSort.cpp
    ../src/algorithms/exchange-sort/partition-sort/StableQuickSort.cpp
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

set(DISTRIBUTION_PIGEONHOLE_TEST_SOURCES
    distribution_pigeonhole_test.cpp
    ../src/algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/TerminalArrayVisualizer.cpp
    ../src/visualizer/TerminalTableVisualizer.cpp
)

set(DISTRIBUTION_COUNTING_TEST_SOURCES
    distribution_counting_test.cpp
    ../src/algorithms/distribution-sort/counting-sort/CountingSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/TerminalArrayVisualizer.cpp
    ../src/visualizer/TerminalTableVisualizer.cpp
)

set(MERGE_SORT_TEST_SOURCES
    merge_sort_test.cpp
    ../src/algorithms/merge-sort/MergeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
)

set(INTEGRATION_TEST_SOURCES
    integration_test.cpp
    ../src/randomizer/ArrayGenerator.cpp
    ../src/randomizer/ArrayRandomizer.cpp
    ../src/randomizer/ArrayReversed.cpp
    ../src/randomizer/ArrayNearlySorted.cpp
    ../src/algorithms/TreeStructure.cpp
    ../src/algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    ../src/algorithms/merge-sort/MergeSort.cpp
    ../src/algorithms/distribution-sort/counting-sort/CountingSort.cpp
    ../src/algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.cpp
    ../src/stats/SortStats.cpp
    ../src/visualizer/VisualizationSession.cpp
    ../src/visualizer/TerminalArrayVisualizer.cpp
    ../src/visualizer/TerminalTableVisualizer.cpp
    ../src/visualizer/TerminalGraphVisualizer.cpp
)

add_executable(array_visualizer_test ${ARRAY_VISUALIZER_TEST_SOURCES})
add_executable(table_visualizer_test ${TABLE_VISUALIZER_TEST_SOURCES})
add_executable(graph_visualizer_test ${GRAPH_VISUALIZER_TEST_SOURCES})
add_executable(randomizer_test ${RANDOMIZER_TEST_SOURCES})
add_executable(exchange_bubble_test ${EXCHANGE_BUBBLE_TEST_SOURCES})
add_executable(exchange_partition_test ${EXCHANGE_PARTITION_TEST_SOURCES})
add_executable(selection_selection_test ${SELECTION_SELECTION_TEST_SOURCES})
add_executable(selection_heap_test ${SELECTION_HEAP_TEST_SOURCES})
add_executable(insertion_insertion_test ${INSERTION_INSERTION_TEST_SOURCES})
add_executable(insertion_tree_test ${INSERTION_TREE_TEST_SOURCES})
add_executable(distribution_pigeonhole_test ${DISTRIBUTION_PIGEONHOLE_TEST_SOURCES})
add_executable(distribution_counting_test ${DISTRIBUTION_COUNTING_TEST_SOURCES})
add_executable(merge_sort_test ${MERGE_SORT_TEST_SOURCES})
add_executable(integration_test ${INTEGRATION_TEST_SOURCES})

add_test(NAME array_visualizer_test COMMAND $<TARGET_FILE:array_visualizer_test>)
add_test(NAME table_visualizer_test COMMAND $<TARGET_FILE:table_visualizer_test>)
add_test(NAME graph_visualizer_test COMMAND $<TARGET_FILE:graph_visualizer_test>)
add_test(NAME randomizer_test COMMAND $<TARGET_FILE:randomizer_test>)
add_test(NAME exchange_bubble_test COMMAND $<TARGET_FILE:exchange_bubble_test>)
add_test(NAME exchange_partition_test COMMAND $<TARGET_FILE:exchange_partition_test>)
add_test(NAME selection_selection_test COMMAND $<TARGET_FILE:selection_selection_test>)
add_test(NAME selection_heap_test COMMAND $<TARGET_FILE:selection_heap_test>)
add_test(NAME insertion_insertion_test COMMAND $<TARGET_FILE:insertion_insertion_test>)
add_test(NAME insertion_tree_test COMMAND $<TARGET_FILE:insertion_tree_test>)
add_test(NAME distribution_pigeonhole_test COMMAND $<TARGET_FILE:distribution_pigeonhole_test>)
add_test(NAME distribution_counting_test COMMAND $<TARGET_FILE:distribution_counting_test>)
add_test(NAME merge_sort_test COMMAND $<TARGET_FILE:merge_sort_test>)
add_test(NAME integration_test COMMAND $<TARGET_FILE:integration_test>)

add_custom_target(tests
    DEPENDS
        array_visualizer_test
        table_visualizer_test
        graph_visualizer_test
        randomizer_test
        exchange_bubble_test
        exchange_partition_test
        selection_selection_test
        selection_heap_test
        insertion_insertion_test
        insertion_tree_test
        merge_sort_test
        distribution_pigeonhole_test
        distribution_counting_test
        integration_test
)

foreach(test_target IN ITEMS array_visualizer_test table_visualizer_test graph_visualizer_test randomizer_test exchange_bubble_test exchange_partition_test selection_selection_test selection_heap_test insertion_insertion_test insertion_tree_test merge_sort_test distribution_pigeonhole_test distribution_counting_test integration_test)
    target_include_directories(${test_target} PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${test_target} PRIVATE OpenMP::OpenMP_CXX)
    if(MSVC)
        target_compile_options(${test_target} PRIVATE /W4)
    else()
        target_compile_options(${test_target} PRIVATE -Wall -Wextra -pedantic)
    endif()
endforeach()
