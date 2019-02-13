#ifndef ARKO_HH
#define ARKO_HH

struct SDL_Renderer;

namespace ark
{
    class ArkObject
    {
    private:
        struct coord
        {
            int x;
            int y;
        };
        
        coord m_position;
        
    public:
        ArkObject(int,int);
        ~ArkObject();
        
        void drawTo(SDL_Renderer *) const;
    };

}
#endif // ARKO_HH