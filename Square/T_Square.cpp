#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

#include "T_Square.hpp"

T_Square::T_Square(float x, float y) :
	Square("square/purple.png", x, y) {
}
