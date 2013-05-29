#include "normalblock.h"

NormalBlock::NormalBlock()
{
    //ctor
}

NormalBlock::NormalBlock(float x, float y, int width, int height,
              SDL_Surface *image, SDL_Surface *screen,
              Dot *dot):Block(x,y,width,height,image,screen,dot){
this->imagen2 = load_image("shield_block.png");
              }

void NormalBlock::logic(){
Block::logic();
}
NormalBlock::~NormalBlock()
{
    //dtor
}
