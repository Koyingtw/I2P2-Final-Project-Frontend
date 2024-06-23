#include <allegro5/allegro.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Resources.hpp"

// ---------------add----------------------
#include "Cube/Cube.hpp"
#include "Player/Player.hpp"
#include "Square/I_Square.hpp"
#include "Square/J_Square.hpp"
#include "Square/L_Square.hpp"
#include "Square/O_Square.hpp"
#include "Square/S_Square.hpp"
#include "Square/T_Square.hpp"
#include "Square/Z_Square.hpp"
//----------------------------------------


bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const float PlayScene::DangerTime = 7.61;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);
const std::vector<int> PlayScene::code = { ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
									ALLEGRO_KEY_LEFT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_RIGHT,
									ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER };
Engine::Point PlayScene::GetClientSize() {
	return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}

void PlayScene::Initialize() {
	mapState.clear();
	keyStrokes.clear();
	ticks = 0;
	deathCountDown = -1;
	lives = 10;
	money = 150;
	SpeedMult = 1;
	Player_Score = 0;
	game_over = 0;
	// ------------
	// player_1->Initialize();
	// player_2->Initialize();
	// ------------
	// Add groups from bottom to top.
	AddNewObject(SquareGroup = new Group());
	AddNewObject(CubeGroups1 = new Group());
	AddNewObject(CubeGroups2 = new Group());

	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(DebugIndicatorGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	// Should support buttons.
	AddNewControlObject(UIGroup = new Group());
	player_1 = new Player(1);
	player_2 = new Player(2);
	player_1->Initialize();
	player_2->Initialize();
	Squares_info.clear();
	//ReadMap();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	// preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
	// Preload Lose Scene
	deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
	Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
	// Start BGM.
	bgmId = AudioHelper::PlayBGM("play.ogg");
	ct1 = clock();
}

void PlayScene::Terminate() {
	AudioHelper::StopBGM(bgmId);
	AudioHelper::StopSample(deathBGMInstance);
	deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}

void PlayScene::Update(float deltaTime) {
	IScene::Update(deltaTime);
	IScene::Draw();
	player_1->Update(deltaTime);
	Draw_game();
	UpdateScore();
	if(game_over){
		Player_Score = player_1->score;
		Engine::GameEngine::GetInstance().ChangeScene("win");
	}
	/*Local or not*/
	if(MapId == 1) return;
	player_2->Update(deltaTime);
	
}

void PlayScene::Draw_game() {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2 + (MapId==1?350:0);
    int halfH = h / 2 + 75;
	Clear_Square();
	Square* square;
	/*Player 1*/
	for(int i=0;i<10;i++){
		for(int j=0;j<20;j++){
			float nx = halfW-542+30*i+15,ny = halfH+268-30*j+15;
			switch (player_1->board[i][j]){
				case 'S':
					SquareGroup->AddNewObject(square = new S_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'Z':
					SquareGroup->AddNewObject(square = new Z_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'J':
					SquareGroup->AddNewObject(square = new J_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'L':
					SquareGroup->AddNewObject(square = new L_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'O':
					SquareGroup->AddNewObject(square = new O_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'I':
					SquareGroup->AddNewObject(square = new I_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'T':
					SquareGroup->AddNewObject(square = new T_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				default:
					break;
			}
		}
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<4;j++){
			float nx = halfW-542+30*i+15,ny = halfH-430+90-30*j+15;
			switch (player_1->head_board[i][j]){
				case 'S':
					SquareGroup->AddNewObject(square = new S_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'Z':
					SquareGroup->AddNewObject(square = new Z_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'J':
					SquareGroup->AddNewObject(square = new J_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'L':
					SquareGroup->AddNewObject(square = new L_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'O':
					SquareGroup->AddNewObject(square = new O_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'I':
					SquareGroup->AddNewObject(square = new I_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'T':
					SquareGroup->AddNewObject(square = new T_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				default:
					break;
			}
		}
	}
	/*Local or not*/
	if(MapId == 1) return;
	/*Player 2*/
	for(int i=0;i<10;i++){
		for(int j=0;j<20;j++){
			float nx = halfW+258+30*i+15,ny = halfH+268-30*j+15;
			switch (player_2->board[i][j]){
				case 'S':
					SquareGroup->AddNewObject(square = new S_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'Z':
					SquareGroup->AddNewObject(square = new Z_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'J':
					SquareGroup->AddNewObject(square = new J_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'L':
					SquareGroup->AddNewObject(square = new L_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'O':
					SquareGroup->AddNewObject(square = new O_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'I':
					SquareGroup->AddNewObject(square = new I_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'T':
					SquareGroup->AddNewObject(square = new T_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				default:
					break;
			}
		}
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<4;j++){
			float nx = halfW+258+30*i+15,ny = halfH-430+90-30*j+15;
			switch (player_2->head_board[i][j]){
				case 'S':
					SquareGroup->AddNewObject(square = new S_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'Z':
					SquareGroup->AddNewObject(square = new Z_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'J':
					SquareGroup->AddNewObject(square = new J_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'L':
					SquareGroup->AddNewObject(square = new L_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'O':
					SquareGroup->AddNewObject(square = new O_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'I':
					SquareGroup->AddNewObject(square = new I_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				case 'T':
					SquareGroup->AddNewObject(square = new T_Square(nx, ny));
					Squares_info.push_back(square);
					break;
				default:
					break;
			}
		}
	}
}

void PlayScene::Draw() const {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2 + (MapId==1?350:0);
    int halfH = h / 2 + 75;
	/*debug mode*/
	if (DebugMode) {
		Engine::Image E1 = Engine::Image("background/basic_help.png", halfW-312-400, halfH-302);
		Engine::Image E3 = Engine::Image("background/basic_head.png", halfW-312-400, halfH-430);

		E1.Draw();
		E3.Draw();

		/*Local or not*/
		if(MapId == 1) return;

		Engine::Image E2 = Engine::Image("background/basic_help.png", halfW-312+400, halfH-302);
		Engine::Image E4 = Engine::Image("background/basic_head.png", halfW-312+400, halfH-430);
		E2.Draw();
		E4.Draw();

	}
	
}

void PlayScene::UpdateScore() {;
	UIScore1->Text = std::string("Score ") + std::to_string(player_1->score);
	/*Local or not*/
	if(MapId == 1) return;
	UIScore2->Text = std::string("Score ") + std::to_string(player_2->score);
}

void PlayScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
	if (keyCode == ALLEGRO_KEY_TAB) {
		DebugMode = !DebugMode;
	}
	else if(keyCode == ALLEGRO_KEY_A){
		player_1->Move_Left();
	}
	else if(keyCode == ALLEGRO_KEY_D){
		player_1->Move_Right();
	}
	else if(keyCode == ALLEGRO_KEY_X){
		player_1->Rotate();
	}
	else if(keyCode == ALLEGRO_KEY_S){
		player_1->Move_Down();
	}
	else if(keyCode == ALLEGRO_KEY_C){
		player_1->Hold_Change();
	}
}

void PlayScene::Clear_Square() {
    for(auto i:Squares_info){
        SquareGroup->RemoveObject(i->GetObjectIterator());
    }
    Squares_info.clear();
}

void PlayScene::ConstructUI() {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2 + (MapId==1?350:0);
    int halfH = h / 2 + 75;
	UIGroup->AddNewObject(new Engine::Image("background/basic.png", halfW-312-400, halfH-302));
	UIGroup->AddNewObject(UIScore1 = new Engine::Label(std::string("Score ") + std::to_string(0), "pirulen.ttf", 24, halfW-312-400, halfH-350,255,255,255));
	
	/*Local or not*/
	if(MapId == 1) return;

	UIGroup->AddNewObject(UIScore2 = new Engine::Label(std::string("Score ") + std::to_string(0), "pirulen.ttf", 24, halfW-312+400, halfH-350,255,255,255));
	UIGroup->AddNewObject(new Engine::Image("background/basic.png", halfW-312+400, halfH-302));
	// UIGroup->AddNewObject(new Engine::Image("square/blue.png", halfW-572+30, halfH+298-30));//(170,570)

	// UIGroup->AddNewObject(new Engine::Image("square/red.png", halfW-572+30*2, halfH+298-30*2));

	// UIGroup->AddNewObject(new Engine::Image("square/green.png", halfW+228+30, halfH+298-30));//(170,570)

	// UIGroup->AddNewObject(new Engine::Image("square/orange.png", halfW+228+30*2, halfH+298-30*2));
}