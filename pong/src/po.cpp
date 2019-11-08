#include "po.hpp"

p::Object::Object(SDL_Rect bounds, ObjName name)
    : _bounds(bounds),_name(name)
{
    
}

void p::Object::OnCollide(ObjName name)
{
}

p::Paddle::Paddle(SDL_Rect r, ObjName name)
    : p::Object(r, name),_score(0),_vely(5)
{
    
}

void p::Paddle::IncScore()
{
    _score++;
}

unsigned p::Paddle::GetScore() const
{
    return _score;
}

void p::Paddle::OnCollide(ObjName name)
{
    switch(name)
    {
    case ObjName::Collide:
        _bounds.y -= _vely;
        break;

    default:
        break;
    }
}
