#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <allegro5/base.h>
#include <allegro5/allegro_audio.h>
#include <list>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>

#include "Engine/Point.hpp"
#include "Engine/Group.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;
class Cube;

class Player: public Engine::Sprite {
protected:
    int player_number;
    PlayScene* getPlayScene();
public:
    std::vector<Cube*> Cubes;
    char board[15][25];
    int score;
    char hold;
    Cube* cube_hold;
    char next[4];
    Cube* cube_next[4];
    char block;
    int block_dis;
    char head_board[15][5];
    Player(int number);
    std::string cube_types;
    void Update(float deltaTime) override;
    void Eliminate();
    void Generate();
    void Clear_Square();
    void Clear_Cube();
    void Move_Left();
    void Move_Right();
    void Rotate();
    void Move_Down();
    void Initialize();
    bool Check_Row(int x,int y);
    int Cnt_Head_Square(int dis);
    void Hold_Change();
    Cube* preview;
};
#endif // PLAYER_HPP

/*
board : 
   y
   ^
 19|    o
...|    o o
  4|    o
  3|
  2| o   o o   o o o
  1| o o o o o o   o
  0| o o o o o o   o
   |----------------> x
     0 1 2 3 4 ... 9
*/
