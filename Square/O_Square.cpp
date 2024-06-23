#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

#include "O_Square.hpp"

O_Square::O_Square(float x, float y) :
	Square("square/yellow.png", x, y) {
}
