#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include <random>

#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/AudioHelper.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Resources.hpp"

// ---------------add----------------------

#include "Player.hpp"
#include "Square/I_Square.hpp"
#include "Square/J_Square.hpp"
#include "Square/L_Square.hpp"
#include "Square/O_Square.hpp"
#include "Square/S_Square.hpp"
#include "Square/T_Square.hpp"
#include "Square/Z_Square.hpp"
#include "Cube/Cube.hpp"
//----------------------------------------

auto rnd = std::mt19937(time(NULL));

PlayScene* Player::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(int number) :
	Sprite("/square/none.png", 48763, 48763),player_number(number){
        for(int i=0;i<20;i++){
            for(int j=0;j<25;j++){
                board[i][j] = 'X';
            }
        }
        for(int i=0;i<20;i++){
            for(int j=0;j<5;j++){
                head_board[i][j] = 'X';
            }
        }
        cube_types = "IJLOSTZ";
        if(number==1)
            hold = cube_types[rnd()%7];
        else
            hold = 'X';
        for (int i = 0; i < 4; i++) {
            std::mutex mtx;
            std::lock_guard<std::mutex> lock(mtx);
            next[i] = cube_types[rnd()%7];
        }

        Cubes.clear();
        block = cube_types[rnd()%7];
        block_dis = 3;

        score = 0;
        preview = new Cube(block, 48763, 48763);
}

void Player::Clear_Cube(){
	PlayScene* scene = getPlayScene();
	for(auto i:Cubes){
        scene->CubeGroups2->RemoveObject(i->GetObjectIterator());
    }
    Cubes.clear();
}

void Player::Initialize(){
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    PlayScene* scene = getPlayScene();
    int halfW = w / 2 + (scene->MapId==1?350*player_number:0);
    int halfH = h / 2 + 75;
    
    /*hold*/
	scene -> CubeGroups2 -> AddNewObject(cube_hold = new Cube(hold, halfW-712 + 32 + 800 * (player_number - 1) , halfH-302 + 120));

    /*next*/
    for(int i=0;i<3;i++){
        scene -> CubeGroups2 -> AddNewObject(cube_next[i] = new Cube(next[i], halfW-712 + 505 + 800 * (player_number - 1) , halfH-302 + 120 + 120 * i));
    }
}

void Player::Update(float deltaTime) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    PlayScene* scene = getPlayScene();
    int halfW = w / 2 + (scene->MapId==1?350*player_number:0);
    int halfH = h / 2 + 75;
    Sprite::Update(deltaTime);
    Player::Eliminate();
    Player::Clear_Cube();
    /*hold*/
    cube_hold->cube_type = hold;
    // Cube *cb;
	// scene -> CubeGroups -> AddNewObject(cb = new Cube(hold, halfW-712 + 32 + 800 * (player_number - 1) , halfH-302 + 120));
    // cube_hold = cb;

    /*next*/
    for(int i=0;i<3;i++){
        cube_next[i]->cube_type = next[i];
    }
    // for(int i=0;i<3;i++){
    //     scene -> CubeGroups -> AddNewObject(cb = new Cube(next[i], halfW-712 + 505 + 800 * (player_number - 1) , halfH-302 + 120 + 120 * i));
    //     Cubes.push_back(cb);
    // }
    
    /*preview*/
    // if(player_number == 1) preview->Update(deltaTime);
    preview->Update(deltaTime);
    if(player_number == 2) return;
    while(Cnt_Head_Square(block_dis)<4){
        for(int i=-2;i<=2;i++){
            if(Cnt_Head_Square(block_dis+i) == 4){
                block_dis = block_dis+i;
                break;
            }
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<4;j++){
            if(i-block_dis>=0&&i-block_dis<4) head_board[i][j] = preview->cube[i-block_dis][j];
            else head_board[i][j] = 'X';
        }
    }
}

int Player::Cnt_Head_Square(int dis){
    int cnt = 0;
    for(int i=0;i<10;i++){
        for(int j=0;j<4;j++){
            if(i-dis>=0&&i-dis<4){
                if(preview->cube[i-dis][j]!='X') cnt++;
            }
        }
    }
    return cnt;
}

void Player::Hold_Change(){
    std::swap(preview->cube_type,hold);
}

void Player::Move_Left(){
    if(Cnt_Head_Square(block_dis - 1) == 4){
        block_dis = block_dis - 1;
    }
}

void Player::Move_Right(){
    if(Cnt_Head_Square(block_dis + 1) == 4){
        block_dis = block_dis + 1;
    }
}

void Player::Rotate(){
    preview->rotation = (preview->rotation+1)%4;
    int cnt = 0;
    for(int i=0;i<10;i++){
        for(int j=0;j<4;j++){
            if(i-block_dis>=0&&i-block_dis<4){
                if(preview->cube[i-block_dis][j]!='X') cnt++;
            }
        }
    }
}

bool Player::Check_Row(int x,int y){
    bool ok = 1;
    for(int i=y;i<20;i++){
        if(board[x][i]!='X') ok = 0;
    }
    return ok;
}

void Player::Move_Down(){
    if(player_number == 1){
        for(int j=-2;j<20;j++){
            int cnt = 0;
            for(int k=0;k<4;k++){
                for(int i=0;i<10;i++){
                    if(j+k>=0&&j+k<20&&board[i][j+k]=='X' && head_board[i][k]!='X'&&Check_Row(i,j+k)){
                        cnt++;
                    }
                }
            }
            if(cnt==4){
                for(int k=0;k<4;k++){
                    for(int i=0;i<10;i++){
                        if(j+k>=0&&j+k<20&&board[i][j+k]=='X' && head_board[i][k]!='X'){
                            board[i][j+k] = head_board[i][k];
                        }
                    }
                }
                preview->cube_type = next[0];
                for(int i=0;i<2;i++) next[i] = next[i+1];
                next[2] = cube_types[rnd()%7];
                return;
            }
        }
        PlayScene* scene = getPlayScene();
        scene->game_over = 1;
    }
}

void Player::Eliminate() {
    PlayScene* scene = getPlayScene();
    if(scene->MapId != 1) return;
    int lines = 0;
    for(int j=20-1;j>=0;j--){
        int cnt = 0;
        for(int i=0;i<10;i++){
            if(board[i][j] != 'X'){
                cnt++;
            }
        }
        if(cnt == 10){
            lines++;
            for(int k=j+1;k<20;k++){
                for(int i=0;i<10;i++){
                    board[i][k-1] = board[i][k];
                }
            }
            for(int i=0;i<10;i++){
                    board[i][19] = 'X';
            }
        }
    }
    if(lines == 1){
        score += 100;
    }
    else if(lines == 2){
        score += 300;
    }
    else if(lines == 3){
        score += 500;
    }
    else if(lines == 4){
        score += 800;
    }
}
