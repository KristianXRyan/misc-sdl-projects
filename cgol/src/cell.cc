#include "cell.hh"

#include <iostream>

Cell::Cell() : m_coord({-1,-1}),m_SurroundingCells({{0,0}}),m_state(state::DEAD)
{
}

Cell::~Cell()
{
}
   
void Cell::isNowDead()
{
    m_state = state::DEAD;
} 

void Cell::isNowAlive()
{
    m_state = state::ALIVE;
}

void Cell::setXY(int x, int y)
{
    m_coord = {x, y};
    
    m_SurroundingCells[0] = {x - 1, y - 1};
    m_SurroundingCells[1] = {x, y - 1};
    m_SurroundingCells[2] = {x + 1, y - 1};
    m_SurroundingCells[3] = {x - 1, y};
    m_SurroundingCells[4] = {x + 1, y};
    m_SurroundingCells[5] = {x - 1, y + 1};
    m_SurroundingCells[6] = {x, y + 1};
    m_SurroundingCells[7] = {x + 1, y + 1};   
}
    
state Cell::getLivingState() const
{
    return m_state;
}

coord Cell::getCoords() const
{
    return m_coord;
}

const coord* Cell::getLocalCellLocations() const
{
    return m_SurroundingCells;    
}
  