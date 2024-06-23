#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <allegro5/base.h>
#include <list>
#include <string>
#include "Engine/Sprite.hpp"

class PlayScene;

class Square: public Engine::Sprite {
protected:
    
public:
    Square(std::string imgSquare,float x, float y);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif // SQUARE_HPP
