#include <allegro5/allegro_audio.h>
#include <bits/stdc++.h>
using namespace std;

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreboardScene.hpp"
#include "StageSelectScene.hpp"

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewControlObject(show_data_group = new Group());
    now_page = 0;
    AddNewObject(new Engine::Label("SCOREBOARD", "pirulen.ttf", 48, halfW, 50, 55, 255, 55, 255, 0.5, 0.5));
    ScoreboardScene::Show_Score_Datas();
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-200 , h - 150, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, h - 100, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-200-500 , h - 150, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrePage, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PREV PAGE", "pirulen.ttf", 48, halfW - 500, h - 100, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-200+500 , h - 150, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextPage, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("NEXT PAGE", "pirulen.ttf", 48, halfW+500, h - 100, 0, 0, 0, 255, 0.5, 0.5));
}

void ScoreboardScene::Check_Score_Now(){
    now_score.clear();
    ifstream inputFile("./Resource/scoreboard.txt"); 
    stringstream buffer;
    string line,P_Name,cleartime;
    int P_Score,P_time;
    while(getline(inputFile, line)){ 
        buffer.clear();
        buffer << line;
        buffer >> P_Name;
        buffer >> P_Score;
        buffer >> P_time;
        buffer >> cleartime;
        now_score.push_back({{-P_Score,P_time},{cleartime,P_Name}});
    }
    std::sort(now_score.begin(),now_score.end());
}

void ScoreboardScene::Show_Score_Datas(){
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    ScoreboardScene::Check_Score_Now();
    int all_pages = (now_score.size()+9)/10;
    for(auto i:now_show_datas){
        show_data_group->RemoveObject(i->GetObjectIterator());
    }
    now_show_datas.clear();
    int cnt = 0;
    Engine::Label *lb1,*lb2,*lb3,*lb4;
    int max_n = min((now_page+1)*10,(int)now_score.size());
    for(int i=now_page*10;i<max_n;i++){
        lb1 = new Engine::Label(now_score[i].second.second, "pirulen.ttf", 24, halfW-400, 150 + cnt * 50, 20, 255, 20, 255, 0.5, 0.5);
        lb2 = new Engine::Label(to_string(-now_score[i].first.first), "pirulen.ttf", 24, halfW-200, 150 + cnt * 50, 20, 255, 255, 255, 0.5, 0.5);
        string time_out = to_string(now_score[i].first.second/60)+"m,"+to_string((now_score[i].first.second)%60)+"s";
        lb3 = new Engine::Label(time_out, "pirulen.ttf", 24, halfW, 150 + cnt * 50, 255, 20, 20, 255, 0.5, 0.5);
        lb4 = new Engine::Label(now_score[i].second.first, "pirulen.ttf", 24, halfW+300, 150 + cnt * 50, 255, 255, 20, 255, 0.5, 0.5);
        show_data_group->AddNewObject(lb1);
        show_data_group->AddNewObject(lb2);
        show_data_group->AddNewObject(lb3);
        show_data_group->AddNewObject(lb4);
        now_show_datas.push_back(lb1);
        now_show_datas.push_back(lb2);
        now_show_datas.push_back(lb3);
        now_show_datas.push_back(lb4);
        cnt++;
    }
}

void ScoreboardScene::NextPage(int stage){
    ScoreboardScene::Check_Score_Now();
    int all_pages = (now_score.size()+9)/10;
    now_page = min(all_pages-1,now_page+1);
    ScoreboardScene::Show_Score_Datas();
}

void ScoreboardScene::PrePage(int stage){
    ScoreboardScene::Check_Score_Now();
    now_page = max(0,now_page-1);
    ScoreboardScene::Show_Score_Datas();
}

void ScoreboardScene::Clear_Datas(){
    for(auto i:now_show_datas){
        show_data_group->RemoveObject(i->GetObjectIterator());
    }
    now_show_datas.clear();
}

void ScoreboardScene::BackOnClick(int stage) {
    ScoreboardScene::Clear_Datas();
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
