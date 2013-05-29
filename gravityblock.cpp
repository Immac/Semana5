#include "gravityblock.h"

gravityBlock::gravityBlock()
{
    //ctor
}


gravityBlock::gravityBlock(float x, float y, int width, int height,SDL_Surface *image,SDL_Surface *screen, Dot *dot){
this->x = x;
this->y = y;
this->width = width;
this->height = height;
this->screen = screen;
this->image = image;
this->dot = dot;
this->isColliding = false;
this->wasColliding = false;
this->life = 2;
this->current_frame = 0;
this->current_power_duration = 0;
this->imagen2 = load_image("shield_block.png");
}

void gravityBlock::logic(){

Block::logic();
if (this->life <= 0){
    this->dot->startGravity();
}
}


gravityBlock::~gravityBlock()
{
    //dtor
}
