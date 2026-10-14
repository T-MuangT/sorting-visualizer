# Source tree build

# Algorithms and Visualization Session Library

add_library(libsortalgos SHARED
    # Session Bridge / Telemetry
    visualizer/VisualizationSession.cpp

    # Randomizers & Stats
    randomizer/ArrayGenerator.cpp
    randomizer/ArrayRandomizer.cpp
    randomizer/ArrayReversed.cpp
    randomizer/ArrayNearlySorted.cpp
    stats/SortStats.cpp

    # Algorithm Primitives & Sorting Implementations
    algorithms/PairwiseCompareSwap.cpp
    algorithms/ArraySplitRange.cpp
    algorithms/PivotSelection.cpp
    algorithms/TreeStructure.cpp
    algorithms/exchange-sort/bubble-sort/BubbleSort.cpp
    algorithms/exchange-sort/bubble-sort/OptimizedBubbleSort.cpp
    algorithms/exchange-sort/bubble-sort/CocktailShakerSort.cpp
    algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.cpp
    algorithms/exchange-sort/bubble-sort/OddEvenSort.cpp
    algorithms/exchange-sort/bubble-sort/OptimizedOddEvenSort.cpp
    algorithms/exchange-sort/bubble-sort/CombSort.cpp
    algorithms/exchange-sort/bubble-sort/OptimizedCombSort.cpp
    algorithms/exchange-sort/partition-sort/CircleSort.cpp
    algorithms/exchange-sort/partition-sort/OptimizedCircleSort.cpp
    algorithms/exchange-sort/partition-sort/LomutoQuickSort.cpp
    algorithms/exchange-sort/partition-sort/HoareQuickSort.cpp
    algorithms/exchange-sort/partition-sort/DualPivotQuickSort.cpp
    algorithms/exchange-sort/partition-sort/StableQuickSort.cpp
    algorithms/selection-sort/selection-sort/SelectionSort.cpp
    algorithms/selection-sort/selection-sort/DoubleSelectionSort.cpp
    algorithms/selection-sort/selection-sort/CycleSort.cpp
    algorithms/selection-sort/heap-sort/MaxHeapSort.cpp
    algorithms/selection-sort/heap-sort/MinHeapSort.cpp
    algorithms/selection-sort/heap-sort/SmoothSort.cpp
    algorithms/insertion-sort/insertion-sort/InsertionSort.cpp
    algorithms/insertion-sort/insertion-sort/BinaryInsertionSort.cpp
    algorithms/insertion-sort/insertion-sort/ShellSort.cpp
    algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.cpp
    algorithms/merge-sort/MergeSort.cpp
    algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.cpp
    algorithms/distribution-sort/counting-sort/CountingSort.cpp
)

target_include_directories(libsortalgos PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(libsortalgos PUBLIC OpenMP::OpenMP_CXX)

# When building a shared library on Windows with MSVC, export all symbols so
# consumers (the executable) can link without adding explicit __declspec
# annotations in the sources.
set_target_properties(libsortalgos PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)


# Terminal Visualizer Library
add_library(libtermvisual SHARED
    visualizer/terminal/TerminalArrayVisualizer.cpp
    visualizer/terminal/TerminalTableVisualizer.cpp
    visualizer/terminal/TerminalGraphVisualizer.cpp
)
target_link_libraries(libtermvisual PUBLIC libsortalgos)
set_target_properties(libtermvisual PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)


# Executable
set(APP_SOURCES
    main.cpp
    menus/ExchangeSortMenu.cpp
    menus/SelectionSortMenu.cpp
    menus/InsertionSortMenu.cpp
    menus/MergeSortMenu.cpp
    menus/DistributionSortMenu.cpp
    menus/exchange-sort/PivotSelectionMenu.cpp
)

add_executable(sorting-visualizer ${APP_SOURCES})
target_link_libraries(sorting-visualizer PRIVATE libsortalgos libtermvisual)


add_custom_target(release
    DEPENDS sorting-visualizer
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Release
)

install(TARGETS
    libsortalgos
    libtermvisual
    sorting-visualizer


    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../README.md"
    "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE"
    "${CMAKE_CURRENT_SOURCE_DIR}/../version.md"
    DESTINATION .
)

if(MSVC)
    target_compile_options(sorting-visualizer PRIVATE /W4)
    target_compile_options(libsortalgos PRIVATE /W4)
    target_compile_options(libtermvisual PRIVATE /W4)
else()
    target_compile_options(sorting-visualizer PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(libsortalgos PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(libtermvisual PRIVATE -Wall -Wextra -pedantic)
endif()