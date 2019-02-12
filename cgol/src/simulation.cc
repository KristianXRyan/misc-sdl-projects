#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <vector>
#include <random>

#include "argh.hh"

#define TITLE "Conway's Game of Life" // default window title

/* the state of the cell  */
enum class CellState
{
    ALIVE,
    DEAD
};

/* wrapper for the SDL graphics structs  */
struct graphics
{
    SDL_Window   *gWindow;
    SDL_Renderer *canvas;
    SDL_Event 	 event;
};

/* inits SDL, returns the refresh rate as a double  */
double initGraphics(graphics &gObject, int width, int height)
{
    double fps = -1.0;
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        throw std::runtime_error(std::string("could not initialize SDL: ") +
            SDL_GetError());
   
    gObject.gWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI 
        | SDL_WINDOW_SHOWN);
        
    if (gObject.gWindow == NULL)
        throw std::runtime_error(std::string("SDL Could not initialize a window: ")
            + SDL_GetError());
        
    gObject.canvas = SDL_CreateRenderer(gObject.gWindow, -1, 
        SDL_RENDERER_ACCELERATED);  
        
    if (gObject.canvas == NULL)
        throw std::runtime_error(std::string("could not create a renderer: ")
            + SDL_GetError());    
            
    /* getting the monitor refresh rate */
    SDL_DisplayMode mode;
    int displayIndex = SDL_GetWindowDisplayIndex(gObject.gWindow);
    
    if(SDL_GetCurrentDisplayMode(displayIndex, &mode) != 0)
        return fps;
    if(mode.refresh_rate == 0)
        return fps;
            
    fps = static_cast<double>(mode.refresh_rate);        
    return fps;
}

/* Destroys the sdl graphics structs  */
void destroyGraphics(graphics &gObject)
{
    SDL_DestroyRenderer(gObject.canvas); 
    SDL_DestroyWindow(gObject.gWindow);
    SDL_Quit();
}

/* check if the player is trying to close the window */
bool playerIsRequestingClose(SDL_Event &event)
{
    bool quit = false;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        default:
            break;
        }
    }
    return quit;
}

// draws the cells to the screen
void draw(SDL_Renderer *canvas, std::vector<std::vector<CellState>> &board,
    int width, int height, int rows, int cols)
{
    SDL_SetRenderDrawColor(canvas, 0, 0, 0, 0xFF);
    SDL_RenderClear(canvas);
    
    SDL_Rect drawCell = {0,0, width / rows, height / cols};
    
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
        {
            drawCell.x = i * (width / rows);
            drawCell.y = j * (height / cols);
            
            if(board[i][j] == CellState::ALIVE)
                SDL_SetRenderDrawColor(canvas, 255, 255, 255, 0xFF);
            else
                SDL_SetRenderDrawColor(canvas, 0, 0, 0, 0xFF);
            
            SDL_RenderFillRect(canvas, &drawCell);
        }
    
    SDL_RenderPresent(canvas);
}

/* initializes the cell vectors; default value is alive */
std::vector<std::vector<CellState>> initCells(int rows, int columns, 
    int likely)
{
    /* random generator for determining if the cell is alive or not */
    using sysClock = std::chrono::high_resolution_clock;
    std::mt19937 randomGenerator(sysClock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dis(0, likely);
    
    std::vector<std::vector<CellState>> board(rows, std::vector<CellState>
        (columns, CellState::DEAD));
    
    /* uses the random seed to create random alive cells */
    for(int i = 0; i < rows; i++)
        for(int y = 0; y < columns; y++)
            if(dis(randomGenerator) == 0)
                board[i][y] = CellState::ALIVE;
    
    return board;          
}

/* gets the total number of neighboring cells that are alive */
unsigned int totalAliveNeighbors(const std::vector<std::vector<CellState>> &board,
    int x, int y, int rows, int cols)
{
    unsigned int sum = 0;
    int newX = 0;
    int newY = 0;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            newX = (x + i + rows) % rows;
            newY = (y + j + cols) % cols;
            if(board[newX][newY] == CellState::ALIVE)
                sum++;
        }
    }

    if(board[x][y] == CellState::ALIVE)
        sum--;
    
    return sum;    
}

/* updates the cells  */
void update(std::vector<std::vector<CellState>> &board, int rows, int cols)
{
    /* the copy of the board to determine how many living cells are nearby */
    auto nextBoard = board;
    
    /* Loops through each cell and applies the rules of the game of life */
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            unsigned int numAlive = totalAliveNeighbors(board, i, j, rows, cols);
            bool isAlive = (board[i][j] == CellState::ALIVE);
            CellState &nCell = nextBoard[i][j];
            
            if(isAlive && (numAlive < 2 || numAlive > 3))
                nCell = CellState::DEAD;
            else if(!isAlive && numAlive == 3)
                nCell = CellState::ALIVE;
        }
    }
    board = nextBoard;
}

/* contains the main game loop */
void simulate(graphics &simg, const Arghandler &argh)
{
    std::vector<std::vector<CellState>> board = initCells(argh.getRows(), 
        argh.getCols(), argh.getLikelyhood());
    /* main loop, based off of the main game loop used in Minecraft by Markus
       "Notch" Persson 													   */
    using namespace std::chrono;
    using sysClock = high_resolution_clock;
    
    /* For determining when a second has passed  */
    const milliseconds oneSecond = milliseconds(1000);
    /* For determining how many frames to render and how many updates
       to run in a second										   */
    const double timeUpdate = 1000000000 / argh.getUPS();
    const double timeFrames = 1000000000 / argh.getFPS();
    
    /* variable length delta time data */
    double deltaUpdate = 0.0;
    double deltaFrames = 0.0;
    
    /* For determining how much time has passed since the last
       run of the loop									    */
    nanoseconds lastTime = duration_cast<nanoseconds>
        (sysClock::now().time_since_epoch());
        
    nanoseconds currentTime =  duration_cast<nanoseconds>
        (sysClock::now().time_since_epoch());
        
    milliseconds timer = duration_cast<milliseconds>
        (sysClock::now().time_since_epoch());
    
    /* For keeping track of the frame and update rate  */    
    unsigned int frames = 0;
    unsigned int ticks = 0;
        
    bool isRunning = true;
    
    while(isRunning)
    {
        isRunning = !playerIsRequestingClose(simg.event);

        currentTime = duration_cast<nanoseconds>
            (sysClock::now().time_since_epoch());
        deltaUpdate += (currentTime - lastTime).count() / timeUpdate;
        deltaFrames += (currentTime - lastTime).count() / timeFrames;
        lastTime = currentTime;
        
        while(deltaUpdate >= 1)
        {
            update(board, argh.getRows(), argh.getCols());
            ticks++;
            deltaUpdate--;
        }
        
        while(deltaFrames >= 1)
        {
            draw(simg.canvas, board, argh.getWidth(), argh.getHeight(),
                argh.getRows(), argh.getCols());
            frames++;
            deltaFrames--;
        }
        
        if (duration_cast<milliseconds>(sysClock::now().time_since_epoch())
            - timer >= oneSecond)
        {
            frames = 0;
            ticks  = 0;
            timer  += oneSecond;
        }
    }
}

// main function
int main(int argc, char **argv)
{
    int returnCode = 0;
    graphics simGraphics;
    bool initError = false;   
    Arghandler argh;
    
    try // uses exceptions so it can easily output error strings to the user
    {
        argh.parseArgs(argc, argv);
    
        argh.setRefreshRate(initGraphics(simGraphics, 
            argh.getWidth(), argh.getHeight()));
    }
    catch(std::exception &e)
    {
        returnCode = -1;
        initError = true;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error in initialization", 
            e.what(), NULL);
        std::cerr << "Error in initialization: " << e.what() << '\n';
    }
    
    if(!initError)
    {
        simulate(simGraphics, argh);
        destroyGraphics(simGraphics);
    }
    
    return returnCode;
}