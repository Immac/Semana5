/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "Timer.h"
#include "Particle.h"
#include "Dot.h"
#include <string>
#include <cstdlib>
#include "block.h"
#define PI 3.14159265
#include <list>
#include "paddle.h"

using namespace std;
//The surfaces

const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

//The surfaces
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;
SDL_MouseMotionEvent evento;

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Semana 5", NULL );

    //Seed random
    srand( SDL_GetTicks() );

    //If everything initialized fine
    return true;
}

void clean_up()
{
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //The frame rate regulator
    Timer fps;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //The dot that will be used
    Dot myDot(screen);
    SDL_Surface *block_image = load_image("block.png");
    list < Block* > blockList;
    Block *block;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 5; j++){
    block = new Block(i * 100,j * 25,100,25,block_image,screen,&myDot);
    blockList.push_back(block);
        }
    }
    Paddle hero((float)SCREEN_WIDTH/2,(float)SCREEN_HEIGHT-10,100,25,block_image,screen,&myDot,&event);


    //While the user hasn't quit
    while( quit == false )
    {

        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the dot
            myDot.handle_input();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }



        //Move the dot
        myDot.move();
        hero.handleInput();
        hero.logic();
        list< Block* > :: iterator blockIterator;
        blockIterator = blockList.begin();
        while(blockIterator != blockList.end()){


        ((Block*)(*blockIterator))->logic();

        if(((Block*)(*blockIterator))->life <= 0){
            blockList.erase(blockIterator);
            blockIterator --;

        }
            blockIterator ++;
        }


        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        //Show the dot on the screen
        myDot.show();
        hero.show();
        blockIterator = blockList.begin();
        while(blockIterator != blockList.end()){
        ((Block*)(*blockIterator))->show();
            blockIterator ++;
        }


        //Update the screen
        if( SDL_Flip( screen ) == -1 ){
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

    }

    //Clean up
    clean_up();

    return 0;
}
