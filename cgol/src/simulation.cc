#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <vector>
#include <random>

#include "cell.hh"
#include "argh.hh"
#include "config.hh"

#define TITLE "Conway's Game of Life"

struct graphics
{
    SDL_Window   *gWindow;
    SDL_Renderer *canvas;
    SDL_Event 	 event;
};

// inits SDL, returns the refresh rate of the window
double initGraphics(graphics &gObject, int width, int height)
{
    double fps = FPS;
    
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
            
    SDL_DisplayMode mode;
    int displayIndex = SDL_GetWindowDisplayIndex(gObject.gWindow);
    
    if(SDL_GetCurrentDisplayMode(displayIndex, &mode) != 0)
        throw std::runtime_error(std::string("could not get the refresh rate")
            + SDL_GetError());
    if(mode.refresh_rate == 0)
        throw std::runtime_error(std::string("could not get the refresh rate")
            + SDL_GetError());
            
    fps = static_cast<double>(mode.refresh_rate);        
    return fps;
}

// uninits SDL
void destroyGraphics(graphics &gObject)
{
    SDL_DestroyRenderer(gObject.canvas); 
    SDL_DestroyWindow(gObject.gWindow);
    SDL_Quit();
}

// check if the player is trying to close the window
bool requestClose(SDL_Event &event)
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
void draw(SDL_Renderer *canvas, std::vector<std::vector<Cell>> &board,
    int width, int height, int rows, int cols)
{
    SDL_SetRenderDrawColor(canvas, 0, 0, 0, 0xFF);
    SDL_RenderClear(canvas);
    
    // CODE HERE
    
    SDL_Rect drawCell = {0,0, width / rows, height / cols};
    
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
        {
            drawCell.x = i * (width / rows);
            drawCell.y = j * (height / cols);
            
            if(board[i][j].getLivingState() == state::ALIVE)
                SDL_SetRenderDrawColor(canvas, 255, 255, 255, 0xFF);
            else
                SDL_SetRenderDrawColor(canvas, 0, 0, 0, 0xFF);
            
            SDL_RenderFillRect(canvas, &drawCell);
        }
    // END CODE
    
    SDL_RenderPresent(canvas);
}

// init the cells
std::vector<std::vector<Cell>> initCells(int rows, int columns)
{
    // random generator for determining if the cell is alive or not
    using sysClock = std::chrono::high_resolution_clock;
    std::mt19937 randomGenerator(sysClock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dis(0, 5);
    
    std::vector<std::vector<Cell>> board(rows, std::vector<Cell>(columns, Cell()));
    for(int i = 0; i < rows; i++)
        for(int y = 0; y < columns; y++)
        {
            board[i][y].setXY(i,y);
            if(dis(randomGenerator) == 1)
                board[i][y].isNowAlive();
            else
                board[i][y].isNowDead();
        }
    return board;          
}

unsigned int totalAliveNeighbors(const std::vector<std::vector<Cell>> &board,
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
            if(board[newX][newY].getLivingState() == state::ALIVE)
                sum++;
        }
    }

    if(board[x][y].getLivingState() == state::ALIVE)
        sum--;
    
    return sum;    
}

// runs the simulation
void update(std::vector<std::vector<Cell>> &board, int rows, int cols)
{
    auto nextBoard = board;
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            unsigned int numAlive = totalAliveNeighbors(board, i, j, rows, cols);
            bool isAlive = (board[i][j].getLivingState() == state::ALIVE);
            Cell &nCell = nextBoard[i][j];
            
            if(isAlive && (numAlive < 2 || numAlive > 3))
                nCell.isNowDead();
            else if(!isAlive && numAlive == 3)
                nCell.isNowAlive();
        }
    }
    board = nextBoard;
}

// contains the main game loop
void simulate(graphics &simg, const Arghandler &argh)
{
    std::vector<std::vector<Cell>> board = initCells(argh.getRows(), 
        argh.getCols());
    // main loop, based off of the main game loop used in Minecraft by Markus
    // "Notch" Persson

    // TODO : make this an arg:
    using namespace std::chrono;
    using sysClock = high_resolution_clock;
    
    const milliseconds oneSecond = milliseconds(1000);
    
    const double timeUpdate = 1000000000 / argh.getUPS();
    const double timeFrames = 1000000000 / argh.getFPS();
    
    double deltaUpdate = 0.0;
    double deltaFrames = 0.0;
    
    nanoseconds lastTime = duration_cast<nanoseconds>
        (sysClock::now().time_since_epoch());
        
    nanoseconds currentTime =  duration_cast<nanoseconds>
        (sysClock::now().time_since_epoch());
        
    milliseconds timer = duration_cast<milliseconds>
        (sysClock::now().time_since_epoch());
        
    unsigned int frames = 0;
    unsigned int ticks = 0;
        
    bool isRunning = true;
    
    while(isRunning)
    {
        isRunning = !requestClose(simg.event);

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
    
    try
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