cmake_minimum_required(VERSION 3.20)
project(SortingVisualizer VERSION 1.5.1 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

if(MSVC)
    set(OpenMP_RUNTIME_MSVC llvm)
endif()

find_package(OpenMP REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(sorting-visualizer PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(exchange_bubble_test PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(exchange_partition_test PRIVATE OpenMP::OpenMP_CXX)

set(CPACK_PACKAGE_NAME "sorting-visualizer")
set(CPACK_PACKAGE_VENDOR "SortingVisualizer")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Sorting algorithm visualizer")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "5")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "sorting-visualizer")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_PACKAGE_FILE_NAME "sorting-visualizer-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)
