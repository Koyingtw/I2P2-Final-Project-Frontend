#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <bits/stdc++.h>
#include "Engine/IScene.hpp"

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

class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
	std::string Player_Name;
	int Score_Now;
	long long pass_time;
	Group* Player_Name_Data_Group;
	std::vector<Engine::Label*> now_show_name_datas;
public:
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	void OnKeyDown(int keyCode) override;
	void SaveData(int stage);
	void Clear_Datas();
};

#endif // WINSCENE_HPP
