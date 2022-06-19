cmake_minimum_required(VERSION 3.16)
project(sorting-visualizer CXX)

set(BUILD_SHARED_LIBS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_subdirectory(external)

find_package(Threads REQUIRED)

add_executable(sorting-visualizer
    src/Audio.cpp
    src/BitonicSort.cpp
    src/BogoSort.cpp
    src/BubbleSort.cpp
    src/CocktailSort.cpp
    src/CombSort.cpp
    src/GnomeSort.cpp
    src/HeapSort.cpp
    src/InsertionSort.cpp
    src/Interface.cpp
    src/main.cpp
    src/Manager.cpp
    src/MergeSort.cpp
    src/Program.cpp
    src/QuickSort.cpp
    src/RadixSortLSD.cpp
    src/RadixSortMSD.cpp
    src/SelectionSort.cpp
    src/Settings.cpp
    src/ShellSort.cpp
    src/SortingAlgorithm.cpp
    src/SortingStatistics.cpp
    src/StalinSort.cpp
    src/Utilities.cpp)
target_include_directories(sorting-visualizer PRIVATE include)
target_link_libraries(sorting-visualizer PRIVATE sfml-audio sfml-graphics ImGui-SFML::ImGui-SFML ImPlot::ImPlot Threads::Threads)
target_compile_features(sorting-visualizer PRIVATE cxx_std_17)
