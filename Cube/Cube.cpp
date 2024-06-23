#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>

#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Cube.hpp"
#include "Square/I_Square.hpp"
#include "Square/J_Square.hpp"
#include "Square/L_Square.hpp"
#include "Square/O_Square.hpp"
#include "Square/S_Square.hpp"
#include "Square/T_Square.hpp"
#include "Square/Z_Square.hpp"

PlayScene* Cube::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Cube::Cube(char cube_type,float x, float y) :
	Sprite("/square/none.png", x, y),cube_type(cube_type),pos_x(x),pos_y(y){
		Squares.clear();
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				cube[i][j] = 'X';
		rotation = 0;
}

void Cube::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	Update_Cube();
	Draw_Cube();
}

void Cube::Update_Cube(){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cube[i][j] = 'X';
	switch (cube_type){
		case 'I':
			cube[0][1] = 'I';
			cube[1][1] = 'I';
			cube[2][1] = 'I';
			cube[3][1] = 'I';
			break;
		/*
		y
		3 
		2 
		1 I I I I
		0 
		  0 1 2 3 x
		*/
		case 'J':
			cube[1][0] = 'J';
			cube[2][0] = 'J';
			cube[2][1] = 'J';
			cube[2][2] = 'J';
			break;
		/*
		y
		3
		2     J
		1     J
		0   J J
		  0 1 2 3 x
		*/
		case 'L':
			cube[2][0] = 'L';
			cube[1][0] = 'L';
			cube[1][1] = 'L';
			cube[1][2] = 'L';
			break;
		/*
		y
		3    
		2   L 
		1   L
		0   L L
		  0 1 2 3 x
		*/
		case 'O':
			cube[1][1] = 'O';
			cube[1][2] = 'O';
			cube[2][1] = 'O';
			cube[2][2] = 'O';
			break;
		/*
		y
		3   
		2   O O
		1   O O
		0 
		  0 1 2 3 x
		*/
		case 'S':
			cube[1][1] = 'S';
			cube[2][1] = 'S';
			cube[2][2] = 'S';
			cube[3][2] = 'S';
			break;
		/*
		y
		3   
		2     S S
		1   S S
		0 
		  0 1 2 3 x
		*/
		case 'Z':
			cube[1][2] = 'Z';
			cube[2][1] = 'Z';
			cube[2][2] = 'Z';
			cube[3][1] = 'Z';
			break;
		/*
		y
		3   
		2   Z Z 
		1     Z Z
		0 
		  0 1 2 3 x
		*/
		case 'T':
			cube[1][2] = 'T';
			cube[2][1] = 'T';
			cube[2][2] = 'T';
			cube[3][2] = 'T';
			break;
		/*
		y
		3   
		2   T T T 
		1     T 
		0 
		  0 1 2 3 x
		*/
		default:
			break;
	}
	for(int rt=0;rt<rotation;rt++){
		char cube_tmp[4][4];
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				cube_tmp[j][4-i-1] = cube[i][j];
			}
		}
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				cube[i][j] = cube_tmp[i][j];
			}
		}
	}
}

/*
3
2
1
0 
  0 1 2 3
(0,0) -> (0,3)
(3,3) -> (3,0)
(0,3) -> (3,3)
(3,0) -> (0,0)
*/

void Cube::Clear_Cube(){
	PlayScene* scene = getPlayScene();
	for(auto i:Squares){
        scene->CubeGroups->RemoveObject(i->GetObjectIterator());
    }
    Squares.clear();
}

void Cube::Draw_Cube(){
	Clear_Cube();
	PlayScene* scene = getPlayScene();
	Square* square;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			float nx = pos_x + 30 * i ,ny = pos_y - 30* j;
			switch (cube[i][j]){
				case 'S':
					scene -> CubeGroups->AddNewObject(square = new S_Square(nx, ny));
					Squares.push_back(square);
					break;
				case 'Z':
					scene -> CubeGroups->AddNewObject(square = new Z_Square(nx, ny));
					Squares.push_back(square);
					break;
				case 'J':
					scene -> CubeGroups->AddNewObject(square = new J_Square(nx, ny));
					Squares.push_back(square);
					break;
				case 'L':
					scene -> CubeGroups->AddNewObject(square = new L_Square(nx, ny));
					Squares.push_back(square);
					break;
				case 'O':
					scene -> CubeGroups->AddNewObject(square = new O_Square(nx, ny));
					Squares.push_back(square);
					break;
				case 'I':
					scene -> CubeGroups->AddNewObject(square = new I_Square(nx, ny));
					Squares.push_back(square);
					break;
				case 'T':
					scene -> CubeGroups->AddNewObject(square = new T_Square(nx, ny));
					Squares.push_back(square);
					break;
				default:
					break;
			}
		}
	}
	// scene -> CubeGroups ->AddNewObject(square = new O_Square(pos_x, pos_y));
	// Squares.push_back(square);
}

void Cube::Draw() const {
	Sprite::Draw();
}