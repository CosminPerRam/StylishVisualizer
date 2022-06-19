# ImGui-Visualizer
This is a program which visualizes a bunch of [sorting algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm).  
Made in C++17 using [SFML](https://github.com/SFML/SFML) 2.6, [ImGui](https://github.com/ocornut/imgui) 1.87 (+[imgui-sfml](https://github.com/eliasdaler/imgui-sfml) 2.5) and [ImPlot](https://github.com/epezent/implot) 0.13, the code is cross platform!  
See a video of the program in action [here](https://www.youtube.com/watch?v=IISj6aj4E6o).

## Capabilities
Has the following sorting algorithms (15):  
[Bubble Sort](https://en.wikipedia.org/wiki/Bubble_sort),
[Cocktail Sort](https://en.wikipedia.org/wiki/Cocktail_shaker_sort),
[Merge Sort](https://en.wikipedia.org/wiki/Merge_sort),
[Quick Sort](https://en.wikipedia.org/wiki/Quicksort),
[Radix Sort (Least And Most Significant Digit)](https://en.wikipedia.org/wiki/Radix_sort),
[Shell Sort](https://en.wikipedia.org/wiki/Shellsort),
[Stalin Sort](https://www.quora.com/What-is-Stalin-sort),
[Bogo Sort](https://en.wikipedia.org/wiki/Bogosort),
[Comb Sort](https://en.wikipedia.org/wiki/Comb_sort),
[Insertion Sort](https://en.wikipedia.org/wiki/Insertion_sort),
[Selection Sort](https://en.wikipedia.org/wiki/Selection_sort),
[Gnome Sort](https://en.wikipedia.org/wiki/Gnome_sort),
[Heap Sort](https://www.geeksforgeeks.org/heap-sort),
[Bitonic Sort](https://en.wikipedia.org/wiki/Bitonic_sorter)

And you can:
- Stop, pause and step through sorting
- Change the delay (or have none, *boo BubbleSort, boooo*)
- Change the volume of the audio representation and tweak its effects
- Change the plot or the ui's styling

## Precompiled binaries
Check the [releases](https://github.com/CosminPerRam/ImGui-Visualizer/releases) page.

## Building the repository
Windows/Linux/MacOS:  
Every dependency is handled by the cmake script (THANKS [@ChrisTrasher](https://github.com/ChrisThrasher)).  
```
cmake -B build
cmake --build build
```
*Windows note:* After building, you need to copy `openal32.dll` (it's at `build\_deps\sfml-src\extlibs\bin\`) to the `sorting-visualizer.exe`'s directory.
