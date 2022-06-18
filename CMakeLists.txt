cmake_minimum_required(VERSION 3.16)
project(blockudokuplusplus CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SFML 2.5.1 REQUIRED COMPONENTS audio graphics)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

add_executable(blockudokuplusplus
    src/Audio.cpp
    src/BubbleSort.cpp
    src/CocktailSort.cpp
    src/Interface.cpp
    src/main.cpp
    src/Manager.cpp
    src/MergeSort.cpp
    src/Program.cpp
    src/QuickSort.cpp
    src/RadixSortLSD.cpp
    src/RadixSortMSD.cpp
    src/ShellSort.cpp
    src/SortingAlgorithm.cpp
    src/Utilities.cpp
    src/StalinSort.cpp
    src/BogoSort.cpp
    src/Settings.cpp
    src/CombSort.cpp
    src/InsertionSort.cpp
    src/SelectionSort.cpp
    libraries/imgui/imgui.cpp
    libraries/imgui/imgui_demo.cpp
    libraries/imgui/imgui_draw.cpp
    libraries/imgui/imgui_tables.cpp
    libraries/imgui/imgui_widgets.cpp
    libraries/imgui/imgui-SFML.cpp
    libraries/implot/implot.cpp
    libraries/implot/implot_demo.cpp
    libraries/implot/implot_items.cpp)
target_include_directories(blockudokuplusplus PRIVATE include libraries/imgui)
target_include_directories(blockudokuplusplus PRIVATE include libraries/implot)
target_link_libraries(blockudokuplusplus PRIVATE Threads::Threads)
target_link_libraries(blockudokuplusplus PRIVATE sfml-audio sfml-graphics sfml-window ${OPENGL_LIBRARIES})
target_compile_features(blockudokuplusplus PRIVATE cxx_std_17)
