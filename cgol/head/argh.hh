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
    
    double  m_ups;
    double  m_fps;
    
public:
    // constructor, destructor
    Arghandler();
    ~Arghandler();
    
    // doers
    void parseArgs(int, char**);
    
    // getters
    bool isMouseInit() const;
    int getWidth() const;
    int getHeight() const;
    int getRows() const;
    int getCols() const;
    double getUPS() const;
    double getFPS() const;
    
    // setter
    void setRefreshRate(double);
};

#endif // ARGH_HH