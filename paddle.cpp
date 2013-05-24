#include "paddle.h"

Paddle::Paddle(float x, float y, int width, int height,
              SDL_Surface *image, SDL_Surface *screen,
              Dot *dot,SDL_Event *event){
this->x = x;
this->y = y;
this->width = width;
this->height = height;
this->screen = screen;
this->image = image;
this->dot = dot;
this->isColliding = false;
this->wasColliding = false;
this->life = 110;
this->event = event;



}

Paddle::~Paddle()
{
    //dtor
}

void Paddle::handleInput(){
   Uint8 *keystate = SDL_GetKeyState(NULL);
   this->xVel = 0;
if ( keystate[SDLK_RIGHT] ) this->xVel = 10;
if ( keystate[SDLK_LEFT] ) this-> xVel = -10;
if ( keystate[SDLK_LEFT] && keystate [SDLK_RIGHT] ) this->xVel = 0;
    //If a key was pressed


}


void Paddle::logic(){






if( ( this->x < 0 ) )
    {

    this-> x = 0;
    } else if ( ( x + this->width > SCREEN_WIDTH)){

    this->x = SCREEN_WIDTH-this->width;
    } else if(this-> x + this->width < 0){
    this->x = SCREEN_WIDTH;
    } else if(this->x + this->width > SCREEN_WIDTH + this->width){
    this->x = 0;
    }






        int collision = collisionType();
        if(!wasColliding){
        switch(collision){
        case 0:
        break;

        case TOP:
                dot->angle = -dot->angle;
                dot->angle += rand()%10 - 20;
                this->life--;
            break;
        case BOT:
            dot->angle = -dot->angle;
            dot->angle += rand()%10 - 20;
            this->life--;
            break;
/*
        case RIGHT: case LEFT:
            dot->angle = -dot->angle+180;
            dot->angle += rand()%10 - 20;
            this->life--;
            break;*/
         case CORNERUL:
             dot->velocity = abs(dot->velocity);
             dot->angle = 315;
             dot->angle += rand()%5-10;
             this->life--;
             break;
        case CORNERUR:
            dot->velocity = abs(dot->velocity);
             dot->angle = 225;
             dot->angle += rand()%5-10;
             this->life--;
             break;
        case CORNERDR:
            dot->velocity = abs(dot->velocity);
             dot->angle = 135;
             dot->angle += rand()%5-10;
             this->life--;
             break;
        case CORNERDL:
            dot->velocity = abs(dot->velocity);
             dot->angle = 45;
             dot->angle += rand()%5-10;
             this->life--;
        }

        }

this->x += this->xVel;

}
