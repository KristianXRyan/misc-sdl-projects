#ifndef CGOL_CELL_HH
#define CGOL_CELL_HH

struct coord
{
    int x;
    int y;
};

enum class state
{
    ALIVE,
    DEAD
};

class Cell
{
private:
    coord m_coord;
    coord m_SurroundingCells[8];
        
    state m_state;
    
public:
    Cell();
    ~Cell();
        
    void isNowDead();
    void isNowAlive();
    void setXY(int, int);
    
    state getLivingState() const;
    coord getCoords() const;
    const coord* getLocalCellLocations() const;
    
};

#endif // CGOL_CELL_HH