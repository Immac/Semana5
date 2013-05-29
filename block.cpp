#include "block.h"

Block::Block()
{
    //ctor
}

Block::~Block()
{
    //dtor
}

Block::Block(float x, float y, int width, int height,SDL_Surface *image,SDL_Surface *screen, Dot *dot){
this->x = x;
this->y = y;
this->width = width;
this->height = height;

this->screen = screen;
this->image = image;
this->imagen2 = load_image("shield_block.png");

this->dot = dot;
this->isColliding = false;
this->wasColliding = false;
this->life = 2;
this->current_frame = 0;
this->current_power_duration = 0;


}

void Block::show(){
    switch(dot->currentState){
case 3:
    // change graphx
    apply_surface( x, y, imagen2, screen);
    //this->image = imagen2;
    break;
default:
    apply_surface( x, y, image, screen);
  //  this->life--;
}

    }


void Block::logic(){
  //  int dotHeight = dot->y + dot->DOT_HEIGHT;

this->current_frame++;




        int collision = collisionType();
        if(!wasColliding){
        switch(collision){
        case 0:
        break;

        case TOP:
                dot->angle = -dot->angle;
                dot->angle += rand()%10 - 20;

                this->takeDamage();
            break;
        case BOT:
            dot->angle = -dot->angle;
            dot->angle += rand()%10 - 20;
            this->takeDamage();
            break;

        case RIGHT: case LEFT:
            dot->angle = -dot->angle+180;
            dot->angle += rand()%10 - 20;
            this->takeDamage();
            break;
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
        case CORNERDR:
            dot->velocity = abs(dot->velocity);
             dot->angle = 135;
             dot->angle += rand()%5-10;
             this->takeDamage();
             break;
        case CORNERDL:
            dot->velocity = abs(dot->velocity);
             dot->angle = 45;
             dot->angle += rand()%5-10;
             this->takeDamage();
        }

        }
 dot->angle = toUsableAngle(dot->angle);
}

void Block::takeDamage(){
    dot->soundRebound();
switch(dot->currentState){
case 3:
    // change graphx

    //this->image = imagen2;
    break;
default:
    this->life--;
}
}

bool Block::isPointInside(float pointX, float pointY){
    float x_off = (cos (dot->angle*PI/180) * dot->velocity );
    float y_off= sin (dot->angle*PI/180) * dot->velocity;
if(    pointX + x_off > this->x
       && pointX + x_off < this->x+this->width
       && pointY - y_off > this->y
       && pointY - y_off < this->y + this->height){
       return true;
       }
       return false;
}

int Block::collisionType(){
        // ESQUINA SUPERIOR IZQUIERDA   dot->x                  dot->y
        // ESQUINA SUPERIOR DERECHA     dot->x + DOT_WIDTH      dot->y
        // ESQUINA INFERIOR IZQUIERDA   dot->x                  dot->y + DOT_HEIGHT
        // ESQUINA INFERIOR DERECHA     dot->x + DOT_WIDTH      dot->y + DOT_HEIGHT
            int x_off = (cos (dot->angle*PI/180) * dot->velocity );
            int y_off = sin (dot->angle*PI/180) * dot->velocity;

        float posX= dot->x  + x_off;
        float posXMid = dot->x + (dot->DOT_WIDTH/2) + x_off;
        float posXEnd= dot->x + dot->DOT_WIDTH + x_off;
        float posY = dot->y - y_off, posYMid = dot->y+ dot->DOT_HEIGHT/2  - y_off, posYEnd = dot->y + dot->DOT_HEIGHT - y_off;

        if(this->isColliding){
            this->wasColliding = true;
        } else {
        this->wasColliding =false;
        }
        this->isColliding = false;

        if (!this->wasColliding){
        if(    isPointInside(posX,posY)
                &&
                isPointInside(posXMid,posY)
                ||
               isPointInside(posXMid,posY)
                &&
                 isPointInside(posXEnd,posY)
                ){
                    this->isColliding = true;
                    return TOP;
        } else if (
                   isPointInside(posX,posYEnd)
                && isPointInside(posXMid,posYEnd)
                ||
                 isPointInside(posXMid,posYEnd)
                && isPointInside(posXEnd,posYEnd)

                ){
                    this->isColliding = true;
                    return BOT;

        }else if (

                  isPointInside(posX,posY)
            &&
                isPointInside(posX,posYMid)
                ||
                 isPointInside(posX,posYMid)
               && isPointInside(posX,posYEnd)

                   ){
                        this->isColliding = true;
                        return LEFT;
        }else if (

                  isPointInside(posXEnd,posY)
                &&
                isPointInside(posXEnd,posYMid)
                ||
                 isPointInside(posXEnd,posYMid)
                && isPointInside(posXEnd,posYEnd)

                   ){
                    this->isColliding = true;
                    return RIGHT;
        }else if (isPointInside(posX,posY)){
        return CORNERUL;
        }else if(isPointInside(posX,posYEnd)){
        return CORNERDL;
        }else if(isPointInside(posXEnd,posY)){
        return CORNERUR;
        }else if(isPointInside(posXEnd,posYEnd)){
        return CORNERDR;
        }

        }

        return 0;
}


