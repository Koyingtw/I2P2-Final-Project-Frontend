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
#include "Square.hpp"
#include "Engine/Sprite.hpp"

Square::Square(std::string imgSquare, float x, float y) :
	Sprite(imgSquare, x, y){
}

void Square::Update(float deltaTime) {
	Sprite::Update(deltaTime);
}

void Square::Draw() const {
	Sprite::Draw();
}
