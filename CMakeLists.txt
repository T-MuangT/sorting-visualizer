cmake_minimum_required(VERSION 3.20)
project(SortingVisualizer VERSION 1.7.5 LANGUAGES CXX)

# Centralize build outputs to avoid multi-config nesting path issues on Windows
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Ensure multi-config generators (like Visual Studio) respect these paths for all configurations
foreach(OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUT_CONFIG} UPPER_CONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPER_CONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPER_CONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPER_CONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach()

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:Release>:-DNDEBUG>
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-Wall>
        $<$<CONFIG:Debug>:-Wextra>
        $<$<CONFIG:Debug>:-Wpedantic>
    )
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        add_compile_options(-march=x86-64 -mtune=generic)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
        add_compile_options(-mcpu=generic)
    endif()
elseif(MSVC)
    add_compile_options(
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Release>:/DNDEBUG>
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Debug>:/RTC1>
        $<$<CONFIG:Debug>:/W4>
        /std:c++latest
    )
    set(OpenMP_RUNTIME_MSVC llvm)
endif()

find_package(OpenMP REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(sorting-visualizer PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(parallel_sort_test PRIVATE OpenMP::OpenMP_CXX)

set(CPACK_PACKAGE_NAME "sorting-visualizer")
set(CPACK_PACKAGE_VENDOR "SortingVisualizer")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Sorting algorithm visualizer")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "7")
set(CPACK_PACKAGE_VERSION_PATCH "5")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "sorting-visualizer")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_PACKAGE_FILE_NAME "sorting-visualizer-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)
