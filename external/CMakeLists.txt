include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(ImGui)

set(IMGUI_DIR "${imgui_SOURCE_DIR}")
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
    GIT_TAG 3eb1ece0fed8351e89e69d4f72cf762ac1c4f4cf
    GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(ImGui-SFML)

FetchContent_Declare(ImPlot
    GIT_REPOSITORY https://github.com/epezent/implot
    GIT_TAG f1b0792cd3e239f615d4f20b9647d37594de8c56
    GIT_PROGRESS TRUE)
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
