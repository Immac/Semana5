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
this->life = 6;
this->event = event;
this->animations[0] = load_image("walk.png");
this->animations[1] = load_image("damage.png");
this->animations[2] = load_image("attack.png");
this->animations[3] = load_image("attack.png");
this->animations[4] = load_image("attack.png");
this->health[0] = load_image("noHealth.png");
this->health[1] = load_image("halfHeatlh.png");
this->health[2] = load_image("fullHealth.png");
this->invulnerableTime = 0;
this->attackCooldownTime = 0;
currentState = IDLE;
this->isDead = false;
this->show();
 chunk = Mix_LoadWAV("takeDamage.ogg");
if(!chunk){
    // Could not load file from disk
}
}

Paddle::~Paddle()
{
   //free images
    //dtor
}

void Paddle::handleInput(){
   Uint8 *keystate = SDL_GetKeyState(NULL);
if (this->xVel > 0) this->xVel--; else if (this->xVel < 0) this->xVel++;
if ( keystate[SDLK_RIGHT] ) this->xVel = 10;
if ( keystate[SDLK_LEFT] ) this-> xVel = -10;
if ( keystate[SDLK_LEFT] && keystate [SDLK_RIGHT] ) this->xVel = 0;
if ( keystate[SDLK_ESCAPE])exit(0);
if ( keystate[SDLK_z] && keystate[SDLK_RIGHT] && invulnerableTime <= 0 && attackCooldownTime <= 0) this->attackRight();
if ( keystate[SDLK_z] && keystate[SDLK_LEFT] && invulnerableTime <= 0 && attackCooldownTime <= 0) this->attackLeft();
if ( keystate[SDLK_z] && invulnerableTime <= 0 && attackCooldownTime <= 0) this->attackNeutral();

}


void Paddle::logic(){

if( ( this->x < 0 ) )
    {

    this-> x = 0;
    } else if ( ( x + this->width > SCREEN_WIDTH)){

    this->x = SCREEN_WIDTH-this->width;
    } else if(this-> x + this->width < 0){
    this->x = SCREEN_WIDTH-this->width;
    } else if(this->x + this->width > SCREEN_WIDTH + this->width){
    this->x = 0;
    }
    int collision = 0;
    collision = collisionType();

      switch (currentState){
    case IDLE:
        if (this->attackCooldownTime > 0){
            this->attackCooldownTime--;
        }
        if (collision != 0){
            getHit(collision);
        }
    break;
    case TAKING_DAMAGE:
        if(invulnerableTime <= 0){
            this->currentState = IDLE;
        }else{
            this->invulnerableTime--;
            return;
        }
    break;
    case SPIN_RIGHT:
        if(invulnerableTime <= 0){
            this->currentState = IDLE;
        }else{
            if (collision != 0){
            getHit(collision);
            }
            this->invulnerableTime--;
            this->xVel = 8;

        }
         break;
       case SPIN_LEFT:
        if(invulnerableTime <= 0){
            this->currentState = IDLE;
        }else{
            if (collision != 0){
            getHit(collision);
            }
            this->invulnerableTime--;
            this->xVel = -8;

        }
         break;
        case SPIN_ATTACK:
        if(invulnerableTime <= 0){
            this->currentState = IDLE;
        }else{
            if (collision != 0){
            getHit(collision);
            }
            this->invulnerableTime--;


        }
         break;
    }





dot->angle = toUsableAngle(dot->angle);
this->x += this->xVel;



}

void Paddle::attackRight(){
this->currentState = SPIN_RIGHT;

this->invulnerableTime =.3*60;
this->attackCooldownTime=0.5*60;
}

void Paddle::attackLeft(){
this->currentState = SPIN_LEFT;

this->invulnerableTime =.3*60;
this->attackCooldownTime=0.5*60;
}


void Paddle::attackNeutral(){
this->currentState = SPIN_ATTACK;

this->invulnerableTime =.3*60;
this->attackCooldownTime=0.5*60;
}

void Paddle::checkState(){

}

void Paddle::takeDamage(){
    if (invulnerableTime == 0){
        Mix_PlayChannel(-1, chunk, 0);
    this->invulnerableTime = 0.5*60;
this->currentState = TAKING_DAMAGE;

this->life -= 1;
if (this->life <= 0 ){
    this->isDead = true;

}
    }
}

void Paddle::getHit(int collision){


        switch(collision){
        case TOP:
                dot->angle = 270;
                dot->angle += rand()%20 - 40;
                dot->velocity = abs(dot->velocity);
                takeDamage();
            break;
        case BOT:
            dot->angle = 90;
            dot->angle += rand()%2 -4;
           this->takeDamage();
            break;

        /*case RIGHT: case LEFT:
            dot->angle = -dot->angle+180;
            dot->angle += rand()%10 - 20;
           this->takeDamage();

            break;*/
         case CORNERUL:
             dot->velocity = abs(dot->velocity);
             dot->angle = 315;
             dot->angle += rand()%5-10;
          this->takeDamage();
             break;
        case CORNERUR:
            dot->velocity = abs(dot->velocity);
             dot->angle = 225;
             dot->angle += rand()%5-10;
          this->takeDamage();
             break;
        case RIGHT:case CORNERDR:
            dot->velocity = abs(dot->velocity);
             dot->angle = 120;
             dot->angle += rand()%5-10;
          this->takeDamage();
             break;
        case LEFT:case CORNERDL:
            dot->velocity = abs(dot->velocity);
             dot->angle = 60;
             dot->angle += rand()%5-10;
                this->takeDamage();
        }

}

bool canCollide(){
//TODO
}

void Paddle::show(){
    switch (currentState){
    case IDLE: apply_surface( x, y, animations[0], screen);
    break;
    case TAKING_DAMAGE: apply_surface( x, y, animations[1], screen);
    break;
    case SPIN_RIGHT: apply_surface( x, y, animations[2], screen);
    break;
    case SPIN_LEFT: apply_surface( x, y, animations[3], screen);
    break;
      case SPIN_ATTACK: apply_surface( x, y, animations[4], screen);
    break;
    }



}

void Paddle::showHP(){
    int hp = this->life;

        for (int i = 1; i <= 3; i++){

        if(hp >= i*2){
            apply_surface(SCREEN_WIDTH - 70, i*40 , health[2],screen);
        } else if (hp%2 == 1 && hp - i >=0){
        apply_surface(SCREEN_WIDTH - 70, i*40 , health[1],screen);
        hp --;
        }else {
        apply_surface(SCREEN_WIDTH - 70, i*40 , health[0],screen);
        }
        }




    }


