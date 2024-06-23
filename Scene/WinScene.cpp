#include <functional>
#include <string>
#include <bits/stdc++.h>
using namespace std;
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"

#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreboardScene.hpp"
#include "StageSelectScene.hpp"

void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Player_Name = "";
	PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    Score_Now = scene->Player_Score;
	pass_time = (scene->ct2 - scene->ct1)*33/(10*CLOCKS_PER_SEC);
	now_show_name_datas.clear();
	AddNewControlObject(Player_Name_Data_Group = new Group());

	AddNewObject(new Engine::Label("Score : ", "pirulen.ttf", 48, halfW - 450, 100, 255, 255, 255, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label(to_string(Score_Now), "pirulen.ttf", 48, halfW - 250, 100, 255, 255, 255, 255, 0.5, 0.5));

	AddNewObject(new Engine::Label("Player : ", "pirulen.ttf", 48, halfW - 200, 150, 255, 255, 255, 255, 0.5, 0.5));
	// AddNewObject(new Engine::Label(to_string(Score_Now), "pirulen.ttf", 48, halfW + 400, h - 400, 255, 255, 255, 255, 0.5, 0.5));

	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, 50, 255, 255, 255, 255, 0.5, 0.5));
	std::cerr << pass_time << '\n';
	string time_out = "Use Time: "+to_string(pass_time/60)+"m,"+to_string(pass_time%60)+"s";
	AddNewObject(new Engine::Label(time_out, "pirulen.ttf", 48, halfW + 300, 100, 200, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW -200 - 250, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW -250, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW -200 +250, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::SaveData, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Save", "pirulen.ttf", 48, halfW + 250, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");
	
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	WinScene::Clear_Datas();
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void WinScene::SaveData(int stage) {
	std::ofstream outfile;
	outfile.open("./Resource/scoreboard.txt", std::ios_base::app); // append instead of overwrite
	outfile << "\n";
	outfile << Player_Name; 
	outfile << " ";
	outfile << to_string(Score_Now);
	outfile << " ";
	outfile << to_string(pass_time);
	outfile << " ";
	time_t now = time(0);
   	tm *ltm = localtime(&now);
	outfile << 1900 + ltm->tm_year<< "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday;
	outfile << "["<<ltm->tm_hour << ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<"]";
	WinScene::Clear_Datas();
	BackOnClick(stage);
}

void WinScene::OnKeyDown(int keyCode) {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	for(auto i:now_show_name_datas){
		Player_Name_Data_Group->RemoveObject(i->GetObjectIterator());
	}
	now_show_name_datas.clear();
	//backspace 63
	//space 75
	cerr << keyCode << '\n';
	if(keyCode == 75){
		Player_Name += '_';
	}
	else if(keyCode == 63 && Player_Name.size() != 0){
		Player_Name = Player_Name.substr(0, Player_Name.size()-1);
	}
	else if(keyCode >= 1 && keyCode <= 26){
		Player_Name += 'A'+keyCode-1;
	}
	if(Player_Name.size() != 0){
		cerr << Player_Name << '\n';
		Engine::Label *lb1;
		// cerr << Player_Name << '\n';
		lb1 = new Engine::Label(Player_Name, "pirulen.ttf", 48, halfW + 200, 150, 255, 255, 255, 255, 0.5, 0.5);
		// cerr << Player_Name << '\n';
		Player_Name_Data_Group->AddNewObject(lb1);
		// cerr << Player_Name << '\n';
		now_show_name_datas.push_back(lb1);
		// cerr << Player_Name << '\n';
	}
}

void WinScene::Clear_Datas(){
    for(auto i:now_show_name_datas){
        Player_Name_Data_Group->RemoveObject(i->GetObjectIterator());
    }
    now_show_name_datas.clear();
}