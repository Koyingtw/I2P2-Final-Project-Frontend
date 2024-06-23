#ifndef ScoreboardScene_HPP
#define ScoreboardScene_HPP
using namespace std;
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
// #include <bits/stdc++.h>

class ScoreboardScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
	std::vector<std::pair<pair<int,int>,pair<string,string>>> now_score;
	vector<Engine::Label*> now_show_datas;
	int now_page;
	Group* show_data_group;
public:
	explicit ScoreboardScene() = default;
	void Initialize() override;
	// void Terminate() override;
	// void Update(float deltaTime) override;
	void BackOnClick(int stage);
	void Check_Score_Now();
	void Show_Score_Datas();
	void NextPage(int stage);
	void PrePage(int stage);
	void Clear_Datas();
};

#endif // WINSCENE_HPP