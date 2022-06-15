# ImGui-Visualizer
This is a program which visualizes a bunch of sorting algorithms, made in C++17 using SFML and ImGui.  
The code is cross platform.

## Algorithms
Bubble Sort

## Precompiled binaries
Check the [releases](https://github.com/CosminPerRam/ImGui-Visualizer/releases) page.

## Dependencies
 - [SFML](https://www.sfml-dev.org/) 2.5.1! (Using all modules except for the `network` one)
 - [imgui](https://github.com/ocornut/imgui) 1.87
 - [imgui-sfml](https://github.com/eliasdaler/imgui-sfml) 2.5
 - [implot](https://github.com/epezent/implot) 0.13

## Building the game
### Windows - Visual Studio
1. Clone/download the repo
2. Enter the repo directory
3. Create a folder named `libraries`
4. Download `SFML 2.5.1 32-bit VS 2017` (from [here](https://www.sfml-dev.org/download/sfml/2.5.1/))
5. Unzip and place the contents in the `libraries` folder. 
(Ex: the path for the `bin` folder inside SFML should look like this: `repo/libraries/SFML-2.5.1/bin`)
6. Create a folder named `imgui` inside `libraries`
7. Download `imgui` (from [here](https://github.com/ocornut/imgui)), unzip it and extract all .cpp and .h files into the `imgui` folder
8. Download `imgui-sfml` (from [here](https://github.com/eliasdaler/imgui-sfml)), unzip it and extract all .cpp and .h files into the `imgui` folder
9. Inside `imconfig.h` add `#include "imconfig-SFML.h"` at the top of the file  
([this video](https://www.youtube.com/watch?v=2YS5WJTeKpI) is a good tutorial for doing the last 3 steps)
10. Download `implot` (from [here](https://github.com/ocornut/imgui)), unzip it, rename the folder to `implot` and place it into the `libraries` folder
11. Open `ImGui-Visualizer.sln`
12. Select the desired configuration (`Debug`/`Release`) and build!  
*. Note: `openal32.dll` (from SFML's `bin` folder) is needed to be in the Debug/Release folder.

~~### Linux/MacOS - CMake
*. You need to do the steps `3`, `7`, `8`, `9` and `10` from above.  
Clone the repo and check out the cmake script.~~
