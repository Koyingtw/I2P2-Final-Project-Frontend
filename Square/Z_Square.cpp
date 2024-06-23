#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

#include "Z_Square.hpp"

Z_Square::Z_Square(float x, float y) :
	Square("square/red.png", x, y) {
}
