#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"

class Player;
class Square;
class Cube;

namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
private:
	enum TileType {
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
	};
	ALLEGRO_SAMPLE_ID bgmId;
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
protected:
	int lives;
	int money;
	int SpeedMult;
public:
	clock_t ct1,ct2;
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const float DangerTime;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	// int LibraryId;
	int Player_Score;
	float ticks;
	float deathCountDown;
	// Map tiles.
	Player* player_1;
	Player* player_2;
	Group* CubeGroups;
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* EffectGroup;
	Group* UIGroup;
	Group* SquareGroup;
	Engine::Label* UIMoney;
	Engine::Label* UILives;
	Engine::Label* UITimes;
	Engine::Label* UIScore1;
	Engine::Label* UIScore2;
	Engine::Image* imgTarget;
	Engine::Sprite* dangerIndicator;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<int>> mapDistance;
	std::list<std::pair<int, float>> enemyWaveData;
	std::vector<Square*> Squares_info;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	// void OnMouseDown(int button, int mx, int my) override;
	// void OnMouseMove(int mx, int my) override;
	// void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	// void Hit();
	// int GetMoney() const;
	// void EarnMoney(int money);
	void UpdateScore();
	// void ReadMap();
	void ConstructUI();
	void Clear_Square();
	void Draw_game();
	// void UIBtnClicked(int id);
};
#endif // PLAYSCENE_HPP
