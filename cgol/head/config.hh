#ifndef CGOL_CONFIG_HH
#define CGOL_CONFIG_HH

// TODO
// Add CMD args
// add ability to set up a seed with the mouse
// add color grid 
// remove 'Cell' class (useless)
// fix bug with screen resizing

// arguments: 
// -m : manual setup (mouse)
// -w : width of the window
// -h : height of the window
// -r : number of rows of cells
// -c : number of columns of cells
// -u : number of times to update per second
// -f : the framerate of the game

constexpr int WIDTH = 600;
constexpr int HEIGHT = 600;

#define TITLE "Conway's Game of Life"

const double FPS = 60.0;
constexpr double UPS = 15.0;

constexpr int NUM_ROWS = 50;
constexpr int NUM_COLUMNS = 50;

constexpr int NUM_CELLS = 0;

constexpr bool MANUAL_INIT = false;

#endif // CGOL_CONFIG_HH