#ifndef CUBE_HPP
#define CUBE_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"

class Square;

class Cube: public Engine::Sprite {
protected:
    PlayScene* getPlayScene();
public:
    std::vector<Square*> Squares;
    char cube_type;
    char cube[10][10];
    int rotation;
    Cube(char cube_type,float x, float y);
    int pos_x,pos_y;
    void Update(float deltaTime) override;
    void Update_Cube();
    void Clear_Cube();
    void Draw_Cube();
    void Draw() const override;
};

#endif 
