# ImGui-Visualizer
This is a program which visualizes a bunch of [sorting algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm).  
Made in C++17 using SFML, ImGui and ImPlot (the code is cross platform).  
See a video of the program in action [here](https://www.youtube.com/watch?v=IISj6aj4E6o).

## Capabilities
Has the following sorting algorithms:
- [Bubble Sort](https://en.wikipedia.org/wiki/Bubble_sort)
- [Cocktail Sort](https://en.wikipedia.org/wiki/Cocktail_shaker_sort)
- [Merge Sort](https://en.wikipedia.org/wiki/Merge_sort)
- [Quick Sort](https://en.wikipedia.org/wiki/Quicksort)
- [Radix Sort (Least And Most Significant Digit)](https://en.wikipedia.org/wiki/Radix_sort)
- [Shell Sort](https://en.wikipedia.org/wiki/Shellsort)  
- [Stalin Sort](https://www.quora.com/What-is-Stalin-sort)
- [Bogo Sort](https://en.wikipedia.org/wiki/Bogosort)
- [Comb Sort](https://en.wikipedia.org/wiki/Comb_sort)
- [Insertion Sort](https://en.wikipedia.org/wiki/Insertion_sort)
- [Selection Sort](https://en.wikipedia.org/wiki/Selection_sort)
- [Gnome Sort](https://en.wikipedia.org/wiki/Gnome_sort)
- [Heap Sort](https://www.geeksforgeeks.org/heap-sort/)

And you can:
- Stop, pause and step through sorting
- Change the delay (or have none, *boo BubbleSort, boooo*)
- Change the volume of the audio representation and tweak its effects
- Change the plot or the ui's styling

## Warning
As also stated in [ImPlot's github repository](https://github.com/epezent/implot): `Dear ImGui uses 16-bit indexing by default [...]`, this is a potential problem that might also occur in this program when you select a high amount of elements and multiple plot types at the same time, I strongly suggest enabling [32-bit](https://www.youtube.com/watch?v=wcq3UjVUdRA) indices by uncommenting `#define ImDrawIdx unsigned int` in the `imconfig.h` file.  
The precompiled binaries come with 32-bit indices (go crazy).

## Precompiled binaries
Check the [releases](https://github.com/CosminPerRam/ImGui-Visualizer/releases) page.

## Building the game

### Dependencies
 - [SFML](https://www.sfml-dev.org/) 2.5.1
 - [imgui](https://github.com/ocornut/imgui) 1.87
 - [imgui-sfml](https://github.com/eliasdaler/imgui-sfml) 2.5
 - [implot](https://github.com/epezent/implot) 0.13

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
*. (Optional, recommended) Uncomment the line containing (or add it) `#define ImDrawIdx unsigned int` in `imconfig.h`
10. Download `implot` (from [here](https://github.com/ocornut/imgui)), unzip it, rename the folder to `implot` and place it into the `libraries` folder
11. Open `ImGui-Visualizer.sln`
12. Select the desired configuration (`Debug`/`Release`) and build!  
*. Note: `openal32.dll` (from SFML's `bin` folder) is needed to be in the Debug/Release folder.

### Linux/MacOS - CMake
*. You need to do the steps `3`, `7`, `8`, `9` and `10` from above.  
Clone the repo and check out the cmake script.
