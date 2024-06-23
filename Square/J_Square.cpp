#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

#include "J_Square.hpp"

J_Square::J_Square(float x, float y) :
	Square("square/blue.png", x, y) {
}
