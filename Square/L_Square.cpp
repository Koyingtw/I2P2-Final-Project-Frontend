#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

#include "L_Square.hpp"

L_Square::L_Square(float x, float y) :
	Square("square/orange.png", x, y) {
}
