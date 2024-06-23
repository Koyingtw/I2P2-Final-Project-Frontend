#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

#include "I_Square.hpp"

I_Square::I_Square(float x, float y) :
	Square("square/light_blue.png", x, y) {
}
