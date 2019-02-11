#ifndef CGOL_ARGH_HH
#define CGOL_ARGH_HH

class Arghandler
{
private:
    bool m_mouse;
    int  m_width;
    int  m_height;
    int  m_rows;
    int  m_cols;
    int  m_ups;
    int  m_fps;
    
public:
    Arghandler();
    ~Arghandler();
    
    void parseArgs(int, char**);
    
    bool isMouseInit() const;
    int getWidth() const;
    int getHeight() const;
    int getRows() const;
    int getCols() const;
    int getUPS() const;
    int getFPS() const;
};

#endif // ARGH_HH