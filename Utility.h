#ifndef UTILITY_H
#define UTILITY_H

#include "SDL.h"
#include "SDL_image.h"
#include "Timer.h"
#include <string>
#define PI 3.14159265

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAMES_PER_SECOND = 60;
SDL_Surface *load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);

float toUsableAngle(float angle);

#endif // UTILITY_H
