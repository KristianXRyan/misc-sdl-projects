# Conway's Game of Life

A version of the cellular automaton 'Conway's Game of Life' written in C++ using SDL2.

The code mostly only uses the C++ standard library, SDL2 is only used for the Windowing and Event system.

## How it works 

The file head/config.hh contains various defaults like the window size, the speed of the simulation, the number of cells, etc.. If you wish to set new defaults, then modify the config header file. You can also input data through the command line.

## Flags

* -w [int]   The width of the window
* -h [int]   The height of the window 
* -r [int]   The number of rows of cells
* -c [int]   The number of columns of cells
* -u [int]   The number of times to update the simulation per second
* -f [int]   The number of frames to render per second (defaults to your monitor's refresh rate)
* -m Allows you to manually start the simulation with your mouse (feature coming soon) 
