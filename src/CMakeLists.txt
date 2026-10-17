# Source tree build

# Algorithms and Visualization Session Library

add_library(sortalgos SHARED
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

target_include_directories(sortalgos PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(sortalgos PUBLIC OpenMP::OpenMP_CXX)

# When building a shared library on Windows with MSVC, export all symbols so
# consumers (the executable) can link without adding explicit __declspec
# annotations in the sources.
set_target_properties(sortalgos PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)


# Terminal Visualizer Library
add_library(termvisual SHARED
    visualizer/terminal/TerminalArrayVisualizer.cpp
    visualizer/terminal/TerminalTableVisualizer.cpp
    visualizer/terminal/TerminalGraphVisualizer.cpp
)
target_link_libraries(termvisual PUBLIC sortalgos)
set_target_properties(termvisual PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Terminal Menu Library
add_library(termmenu SHARED
    menus/terminal/TerminalMainMenu.cpp
    menus/terminal/TerminalPresortMenu.cpp
    menus/terminal/ExchangeSortMenu.cpp
    menus/terminal/SelectionSortMenu.cpp
    menus/terminal/InsertionSortMenu.cpp
    menus/terminal/MergeSortMenu.cpp
    menus/terminal/DistributionSortMenu.cpp
    menus/terminal/exchange-sort/PivotSelectionMenu.cpp
)
target_link_libraries(termmenu PUBLIC sortalgos)
set_target_properties(termmenu PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Executable
set(TERMINAL_APP_SOURCES
    terminal/main.cpp
)

add_executable(sorting-visualizer ${TERMINAL_APP_SOURCES})
target_link_libraries(sorting-visualizer PRIVATE sortalgos termvisual termmenu)


add_custom_target(release
    DEPENDS sorting-visualizer
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Release
)

install(TARGETS
    sortalgos
    termvisual
    termmenu
    sorting-visualizer


    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../README.md"
    "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE"
    "${CMAKE_CURRENT_SOURCE_DIR}/../version.md"
    DESTINATION .
)

if(MSVC)
    target_compile_options(sorting-visualizer PRIVATE /W4)
    target_compile_options(sortalgos PRIVATE /W4)
    target_compile_options(termvisual PRIVATE /W4)
    target_compile_options(termmenu PRIVATE /W4)
else()
    target_compile_options(sorting-visualizer PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(sortalgos PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(termvisual PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(termmenu PRIVATE -Wall -Wextra -pedantic)
endif()