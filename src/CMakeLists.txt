# Source tree build

# ============================================================
# Algorithms and Visualization Session Library
# ============================================================

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

target_include_directories(sortalgos
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(sortalgos
    PUBLIC
        OpenMP::OpenMP_CXX
)

set_target_properties(sortalgos PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# ============================================================
# Terminal Visualizer and Menu Library
# ============================================================

add_library(termvisual SHARED
    visualizer/terminal/TerminalArrayVisualizer.cpp
    visualizer/terminal/TerminalTableVisualizer.cpp
    visualizer/terminal/TerminalGraphVisualizer.cpp
)

target_link_libraries(termvisual
    PUBLIC
        sortalgos
)

set_target_properties(termvisual PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

add_library(termmenu SHARED
    menus/terminal/TerminalMainMenu.cpp
    menus/terminal/TerminalPresortMenu.cpp
    menus/terminal/sort-menu/TerminalExchangeSortMenu.cpp
    menus/terminal/sort-menu/TerminalSelectionSortMenu.cpp
    menus/terminal/sort-menu/TerminalInsertionSortMenu.cpp
    menus/terminal/sort-menu/TerminalMergeSortMenu.cpp
    menus/terminal/sort-menu/TerminalDistributionSortMenu.cpp
    menus/terminal/sort-menu/exchange-sort/TerminalPivotSelectionMenu.cpp
)

target_link_libraries(termmenu
    PUBLIC
        sortalgos
)

set_target_properties(termmenu PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# ============================================================
# Terminal Executable
# ============================================================

add_executable(sorting-visualizer
    terminal/main.cpp
)

target_link_libraries(sorting-visualizer
    PRIVATE
        sortalgos
        termvisual
        termmenu
)

# ============================================================
# GUI Visualizer and Menu Library
# ============================================================

add_library(guivisual SHARED
    visualizer/graphics/GraphicsVisualizerDashboard.cpp
    visualizer/graphics/GraphicsArrayVisualizer.cpp
    visualizer/graphics/GraphicsTableVisualizer.cpp
    visualizer/graphics/GraphicsGraphVisualizer.cpp
)

target_link_libraries(guivisual
    PUBLIC
        sortalgos
    PRIVATE
        ${SORTING_VISUALIZER_WX_TARGETS}
)

set_target_properties(guivisual PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

add_library(guimenu SHARED
    menus/graphics/GraphicsMainMenu.cpp
    menus/graphics/GraphicsPresortMenu.cpp
    menus/graphics/sort-menu/GraphicsExchangeSortMenu.cpp
    menus/graphics/sort-menu/GraphicsSelectionSortMenu.cpp
    menus/graphics/sort-menu/GraphicsInsertionSortMenu.cpp
    menus/graphics/sort-menu/GraphicsMergeSortMenu.cpp
    menus/graphics/sort-menu/GraphicsDistributionSortMenu.cpp
    menus/graphics/sort-menu/exchange-sort/GraphicsPivotSelectionMenu.cpp
)

target_link_libraries(guimenu
    PUBLIC
        sortalgos
    PRIVATE
        ${SORTING_VISUALIZER_WX_TARGETS}
)

set_target_properties(guimenu PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# ============================================================
# GUI Executable
# ============================================================

add_executable(sorting-visualizer-gui
    graphics/main.cpp
)

target_link_libraries(sorting-visualizer-gui
    PRIVATE
        sortalgos
        guivisual
        guimenu
        wxWidgets::wxWidgets
        Threads::Threads
)

if(WIN32)
    # Mark the GUI executable as a Windows GUI application.
    set_target_properties(sorting-visualizer-gui PROPERTIES
        WIN32_EXECUTABLE ON
    )
endif()

# ============================================================
# Windows Runtime DLL Deployment
# ============================================================

if(WIN32)
    if(NOT DEFINED VCPKG_TARGET_TRIPLET)
        message(FATAL_ERROR
            "VCPKG_TARGET_TRIPLET is not defined. "
            "Configure the project with the vcpkg toolchain."
        )
    endif()

    if(DEFINED VCPKG_INSTALLED_DIR)
        set(_vcpkg_installed_root "${VCPKG_INSTALLED_DIR}")
    else()
        set(_vcpkg_installed_root
            "${CMAKE_BINARY_DIR}/vcpkg_installed"
        )
    endif()

    set(_vcpkg_release_bin
        "${_vcpkg_installed_root}/${VCPKG_TARGET_TRIPLET}/bin"
    )

    set(_vcpkg_debug_bin
        "${_vcpkg_installed_root}/${VCPKG_TARGET_TRIPLET}/debug/bin"
    )

    if(NOT EXISTS "${_vcpkg_release_bin}")
        message(FATAL_ERROR
            "vcpkg Release runtime directory not found: "
            "${_vcpkg_release_bin}"
        )
    endif()

    # Stage the matching vcpkg runtime DLLs beside the GUI executable.
    # This includes wxWidgets and its potential DLL dependencies.
    # The entire directory is copied for convenient build-tree testing.
    add_custom_command(
        TARGET sorting-visualizer-gui
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "$<IF:$<CONFIG:Debug>,${_vcpkg_debug_bin},${_vcpkg_release_bin}>"
            "$<TARGET_FILE_DIR:sorting-visualizer-gui>"
        VERBATIM
        COMMENT "Staging vcpkg runtime DLLs for the GUI"
    )
endif()

# ============================================================
# Runtime Search Paths for Installed Applications
# ============================================================

if(APPLE)
    # Shared libraries locate their sibling libraries in lib/.
    set_target_properties(
        sortalgos
        termvisual
        termmenu
        guivisual
        guimenu
        PROPERTIES
            INSTALL_RPATH "@loader_path"
    )

    # Executables locate installed libraries in ../lib/.
    set_target_properties(
        sorting-visualizer
        sorting-visualizer-gui
        PROPERTIES
            INSTALL_RPATH "@loader_path/../lib"
    )
elseif(UNIX)
    set_target_properties(
        sortalgos
        termvisual
        termmenu
        guivisual
        guimenu
        PROPERTIES
            INSTALL_RPATH "$ORIGIN"
    )

    set_target_properties(
        sorting-visualizer
        sorting-visualizer-gui
        PROPERTIES
            INSTALL_RPATH "$ORIGIN/../lib"
    )
endif()

# ============================================================
# Installation Rules and Runtime Dependency Collection
# ============================================================

set(_project_install_targets
    sortalgos
    termvisual
    termmenu
    guivisual
    guimenu
    sorting-visualizer
    sorting-visualizer-gui
)

install(
    TARGETS ${_project_install_targets}

    RUNTIME_DEPENDENCY_SET sorting_visualizer_runtime_deps

    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if(WIN32)
    # Collect runtime DLL dependencies of the installed targets.
    # The vcpkg Release bin directory helps CMake resolve third-party
    # DLLs that aren't located beside the executable at install time.
    install(
        TARGETS ${_project_install_targets}

        RUNTIME_DEPENDENCIES
            DIRECTORIES
                "${_vcpkg_release_bin}"

            PRE_EXCLUDE_REGEXES
                "^api-ms-.*"
                "^ext-ms-.*"

            POST_EXCLUDE_REGEXES
                ".*[\\\\/]system32[\\\\/].*"
                ".*[\\\\/]SysWOW64[\\\\/].*"

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()

# Project documentation
install(
    FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../README.md"
        "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE"
        "${CMAKE_CURRENT_SOURCE_DIR}/../version.md"
    DESTINATION .
)

# ============================================================
# Compiler Warnings
# ============================================================

set(_project_targets
    sortalgos
    termvisual
    termmenu
    guivisual
    guimenu
    sorting-visualizer
    sorting-visualizer-gui
)

foreach(_target IN LISTS _project_targets)
    if(MSVC)
        target_compile_options(${_target} PRIVATE /W4)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -pedantic)
    endif()
endforeach()