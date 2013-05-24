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

    this->screen=screen;
    //Initialize the offsets
    x = 0;
    y = 0;

    angle = -45;
    velocity = 8;

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

void Dot::handle_input()
{

//    //If a key was pressed
//    if( event.type == SDL_KEYDOWN )
//    {
//        //Adjust the velocity
//        switch( event.key.keysym.sym )
//        {
//            case SDLK_UP: yVel -= DOT_HEIGHT / 2; break;
//            case SDLK_DOWN: yVel += DOT_HEIGHT / 2; break;
//            case SDLK_LEFT: xVel -= DOT_WIDTH / 2; break;
//            case SDLK_RIGHT: xVel += DOT_WIDTH / 2; break;
//        }
//    }
//    //If a key was released
//    else if( event.type == SDL_KEYUP )
//    {
//        //Adjust the velocity
//        switch( event.key.keysym.sym )
//        {
//            case SDLK_UP: yVel += DOT_HEIGHT / 2; break;
//            case SDLK_DOWN: yVel -= DOT_HEIGHT / 2; break;
//            case SDLK_LEFT: xVel += DOT_WIDTH / 2; break;
//            case SDLK_RIGHT: xVel -= DOT_WIDTH / 2; break;
//        }
//    }
}

void Dot::move()
{
    this->x += (cos (angle*PI/180) * velocity );
    this->y -= sin (angle*PI/180) * velocity;

    if( ( x < 0 ) || ( x + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        angle=-angle+180;
    }

    if( ( y < 0 ) || ( y + DOT_HEIGHT > SCREEN_HEIGHT + 500 ) )
    {
        angle=-angle;
    }
    if (y > SCREEN_HEIGHT + 400){
        exit(0);
    }
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
