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
- [Heap Sort](https://www.geeksforgeeks.org/heap-sort)
- [Bitonic Sort](https://en.wikipedia.org/wiki/Bitonic_sorter)

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

```
cmake -B build
cmkae --build build
```
