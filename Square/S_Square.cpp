#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

#include "S_Square.hpp"

S_Square::S_Square(float x, float y) :
	Square("square/green.png", x, y) {
}
