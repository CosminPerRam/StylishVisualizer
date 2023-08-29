cmake_minimum_required(VERSION 3.16)
project(sorting-visualizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_definitions(ImDrawIdx=unsigned)
add_compile_definitions(IMGUI_DISABLE_OBSOLETE_FUNCTIONS)

add_subdirectory(external)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/WX /W3 /permissive-)
    add_compile_options(/MP)
endif()

find_package(Threads REQUIRED)

add_executable(sorting-visualizer
    src/Audio.cpp
    src/Interface.cpp
    src/main.cpp
    src/Manager.cpp
    src/Program.cpp
    src/Settings.cpp
    src/SortingAlgorithm.cpp
    src/SortingStatistics.cpp
    src/Utilities.cpp
    src/SortingAlgorithms/BitonicSort.cpp
    src/SortingAlgorithms/BogoSort.cpp
    src/SortingAlgorithms/BubbleSort.cpp
    src/SortingAlgorithms/CocktailSort.cpp
    src/SortingAlgorithms/CombSort.cpp
    src/SortingAlgorithms/GnomeSort.cpp
    src/SortingAlgorithms/HeapSort.cpp
    src/SortingAlgorithms/InsertionSort.cpp
    src/SortingAlgorithms/MergeSort.cpp
    src/SortingAlgorithms/PancakeSort.cpp
    src/SortingAlgorithms/QuickSort.cpp
    src/SortingAlgorithms/RadixSortLSD.cpp
    src/SortingAlgorithms/RadixSortMSD.cpp
    src/SortingAlgorithms/SelectionSort.cpp
    src/SortingAlgorithms/ShellSort.cpp
    src/SortingAlgorithms/StalinSort.cpp)
target_include_directories(sorting-visualizer PRIVATE include)
target_link_libraries(sorting-visualizer PRIVATE sfml-audio sfml-graphics ImGui-SFML::ImGui-SFML ImPlot::ImPlot Threads::Threads)
