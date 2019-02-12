#ifndef CGOL_CONFIG_HH
#define CGOL_CONFIG_HH

// TODO
// add ability to set up a simulation with the mouse
// add color grid 

// arguments: 
// -m : manual setup (mouse)
// -w : width of the window
// -h : height of the window
// -r : number of rows of cells
// -c : number of columns of cells
// -u : number of times to update per second
// -f : the framerate of the game
// -l : the likelyhood of a cell being alive at the start
// 

constexpr int WIDTH = 600; // default width of the window
constexpr int HEIGHT = 600; // default height of the window

/* default fps if SDL cannot get the refresh rate  */
const double FPS = 60.0; 
constexpr double UPS = 15.0; // default update rate

constexpr int NUM_ROWS = 50; // default number of rows
constexpr int NUM_COLUMNS = 50; // default number of columns

constexpr bool MANUAL_INIT = false; // set the program manually

constexpr int LIKELY = 5; // likelyhood of a cell being alive (1 in <number>)

#endif // CGOL_CONFIG_HH