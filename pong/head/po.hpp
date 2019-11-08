#ifndef PONG_O_INTERFACE
#define PONG_O_INTERFACE

#include <SDL2/SDL.h>

namespace p
{
    enum class ObjName
    {
        Paddle,
        Ball,

        NonCollide,
        Collide,
    };
    
    class Object
    {
    protected:
        SDL_Rect  _bounds;
        ObjName     _name;

    public:
        Object(SDL_Rect bounds, ObjName name);
        virtual ~Object() = default;

        virtual void OnCollide(ObjName name); // object doesn't need to know what collided with it
    };

    class Paddle : public Object
    {
    private:
        unsigned _score;
        int       _vely;

    public:
        Paddle(SDL_Rect bounds, ObjName name);
        virtual ~Paddle() = default;

        void IncScore();

        unsigned GetScore() const;

        void OnCollide(ObjName name) override;
    };
}

#endif // PONG_O_INTERFACE
