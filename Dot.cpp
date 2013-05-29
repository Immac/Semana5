#include "Dot.h"

Dot::Dot(SDL_Surface *screen)
{
    red = load_image( "red.bmp" );
    green = load_image( "green.bmp" );
    blue = load_image( "blue.bmp" );

    //Set alpha
    SDL_SetAlpha( red, SDL_SRCALPHA | SDL_RLEACCEL, 192 );
    SDL_SetAlpha( blue, SDL_SRCALPHA | SDL_RLEACCEL, 192 );
    SDL_SetAlpha( green, SDL_SRCALPHA | SDL_RLEACCEL, 192 );

    dot = load_image( "dot.bmp" );
    this->currentState = NORMAL;
    this->screen=screen;
    //Initialize the offsets
    x = SCREEN_WIDTH/2;
    y = SCREEN_HEIGHT/2;
    this->durationState = 0;
    angle = 45;
    velocity = 8;
    blockList = 0;
    sfxShield = Mix_LoadWAV("metal.wav");
     sfxGravity = Mix_LoadWAV("gravity.wav");
      sfxBound = Mix_LoadWAV("bound.wav");
      Mix_VolumeChunk(sfxBound,10);

    //Initialize particles
    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        switch( rand() % 3 )
        {
            case 0: particles[ p ] = new Particle( x, y, screen,red); break;
            case 1: particles[ p ] = new Particle( x, y, screen,green); break;
            case 2: particles[ p ] = new Particle( x, y, screen,blue); break;
        }
    }
}

/*void Dot::setBlockList(list <Block*> &lista){
this->blockList = lista;
}
*/

void Dot::handle_input(){
}


Dot::~Dot()
{
    //Delete particles
    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        delete particles[ p ];
    }

    SDL_FreeSurface( dot );
    SDL_FreeSurface( red );
    SDL_FreeSurface( green );
    SDL_FreeSurface( blue );
}



void Dot::move()
{
    this->angle = toUsableAngle(angle);
    this->x += (cos (angle*PI/180) * velocity );
    this->y -= sin (angle*PI/180) * velocity;
    this->handleState();




    if( ( x + (cos (angle*PI/180) * velocity ) < 0 ) || ( x + (cos (angle*PI/180) * velocity ) + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        this->angle = toUsableAngle(-this->angle +180 );
    }

    if( ( y  - sin (angle*PI/180) * velocity < 0 ) || ( y - sin (angle*PI/180) * velocity + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        this->angle = toUsableAngle(-this->angle);
    }
    if (y > SCREEN_HEIGHT + 400){
        exit(0);
    }

}


void Dot::handleState(){


switch(this->currentState){
case NORMAL:


    if (this->durationState-- <= 0){
       this->startNormal();
    }
    break;

case SLOWED:

    break;

case GRAVITY:

     if (this->angle <= 90 || this-> angle >= 270){
    this->angle = toUsableAngle(angle+rand()%6);
    } else if(this->angle < 270){
    this->angle = toUsableAngle(angle-rand()%6);
    }

    if (this->durationState-- <= 0){
       this->startNormal();
    }

    break;
case SHIELD:

if (this->durationState-- <= 0){
        this->startNormal();
    }

}
}

void Dot::startSlow(){
this->startNormal();

//this->currentState = SLOWED;
this->velocity /=2;
this->durationState = 12*60;

}

void Dot::startGravity(){
startNormal();
 Mix_PlayChannel(-1, sfxGravity, 0);
this->currentState = GRAVITY;
this->durationState = (rand()%5+5)*60;
}

void Dot::startNormal(){
this->velocity = INIT_VELOCITY;
this->currentState = NORMAL;
this->durationState = 0;

}

void Dot::startShield(){
this->startNormal();
 Mix_PlayChannel(-1, sfxShield, 0);
this->currentState = SHIELD;
this->durationState = (rand()%10+6)*60;
}

void Dot::soundRebound(){
 Mix_PlayChannel(-1, sfxBound, 0);

}
void Dot::show_particles()
{
    //Go through particles
    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        //Delete and replace dead particles
        if( particles[ p ]->is_dead() == true )
        {
            delete particles[ p ];

            switch( rand() % 3 )
            {
                case 0: particles[ p ] = new Particle( x, y, screen,red); break;
                case 1: particles[ p ] = new Particle( x, y, screen,green); break;
                case 2: particles[ p ] = new Particle( x, y, screen,blue); break;
            }
        }
    }

    //Show particles
    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        particles[ p ]->show();
    }
}

void Dot::show()
{
    //Show the dot
    apply_surface( x, y, dot, screen );

    //Show the particles
    show_particles();
}
