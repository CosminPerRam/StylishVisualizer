include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.87)
FetchContent_MakeAvailable(ImGui)

set(IMGUI_DIR "${imgui_SOURCE_DIR}")
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
    GIT_TAG v2.5)
FetchContent_MakeAvailable(ImGui-SFML)

FetchContent_Declare(ImPlot
    GIT_REPOSITORY https://github.com/epezent/implot
    GIT_TAG v0.13)
FetchContent_MakeAvailable(ImPlot)

add_library(ImPlot
    "${implot_SOURCE_DIR}/implot.cpp"
    "${implot_SOURCE_DIR}/implot_items.cpp"
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp")
add_library(ImPlot::ImPlot ALIAS ImPlot)
target_include_directories(ImPlot PUBLIC "${implot_SOURCE_DIR}" "${imgui_SOURCE_DIR}")
target_compile_definitions(ImPlot PUBLIC ImDrawIdx=unsigned)
target_compile_features(ImPlot PUBLIC cxx_std_11)