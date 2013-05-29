/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Timer.h"
#include "Particle.h"
#include "Dot.h"
#include <string>
#include <cstdlib>
#include "block.h"
#define PI 3.14159265
#include <list>
#include "paddle.h"
#include "slowblock.h"
#include "normalblock.h"
#include "utility.h"
#include "SDL_ttf.h"
#include "gravityblock.h"
#include "shieldblock.h"
using namespace std;
//The surfaces

const int SCREEN_BPP = 32;

//The frame rate


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
     if( TTF_Init() == -1 )
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
      if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
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
enum BlockToCreate{
    BLOCKNORMAL,
    BLOCKSLOW,
    BLOCKGRAVITY,
    BLOCKSHIELD
    };


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
    SDL_Surface *slow_block_image = load_image("slow_block.png");
    SDL_Surface *gravity_block_image = load_image("gravity_block.png");
    SDL_Surface *shield_block_image = load_image("shielded_block.png");
    list < Block* > blockList;
    Block *block;
    int block_size_width = 128;
    int block_size_height = 25;
    int x,y;

    block = new NormalBlock(0 * block_size_width,0 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new ShieldBlock(1 * block_size_width,0 * block_size_height,block_size_width,block_size_height,shield_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(2 * block_size_width,0 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new ShieldBlock(3 * block_size_width,0 * block_size_height,block_size_width,block_size_height,shield_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(4 * block_size_width,0 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);

    block = new NormalBlock(0 * block_size_width,1 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new SlowBlock(1 * block_size_width,1 * block_size_height,block_size_width,block_size_height,slow_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(2 * block_size_width,1 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new SlowBlock(3 * block_size_width,1 * block_size_height,block_size_width,block_size_height,slow_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(4 * block_size_width,1 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);

    block = new gravityBlock(1 * block_size_width,2 * block_size_height,block_size_width,block_size_height,gravity_block_image,screen,&myDot);
    blockList.push_back(block);
     block = new NormalBlock(0 * block_size_width,2 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
     block = new NormalBlock(2 * block_size_width,2 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
     block = new NormalBlock(4 * block_size_width,2 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new gravityBlock(3 * block_size_width,2 * block_size_height,block_size_width,block_size_height,gravity_block_image,screen,&myDot);
    blockList.push_back(block);

    block = new gravityBlock(0 * block_size_width,3 * block_size_height,block_size_width,block_size_height,gravity_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(1 * block_size_width,3 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(2 * block_size_width,3 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(3 * block_size_width,3 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new gravityBlock(4 * block_size_width,3 * block_size_height,block_size_width,block_size_height,gravity_block_image,screen,&myDot);
    blockList.push_back(block);

block = new NormalBlock(0 * block_size_width,4 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new ShieldBlock(1 * block_size_width,4 * block_size_height,block_size_width,block_size_height,shield_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(2 * block_size_width,4 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new ShieldBlock(3 * block_size_width,4 * block_size_height,block_size_width,block_size_height,shield_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(4 * block_size_width,4 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);

    block = new NormalBlock(0 * block_size_width,5 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);
    block = new SlowBlock(1 * block_size_width,5 * block_size_height,block_size_width,block_size_height,slow_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new SlowBlock(2 * block_size_width,5 * block_size_height,block_size_width,block_size_height,slow_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new SlowBlock(3 * block_size_width,5 * block_size_height,block_size_width,block_size_height,slow_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new NormalBlock(4 * block_size_width,5 * block_size_height,block_size_width,block_size_height,block_image,screen,&myDot);
    blockList.push_back(block);



/*

    block = new SlowBlock(2 * block_size_width,3 * block_size_height,block_size_width,block_size_height,slow_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new gravityBlock(2 * block_size_width,5 * block_size_height,block_size_width,block_size_height,gravity_block_image,screen,&myDot);
    blockList.push_back(block);
    block = new ShieldBlock(2 * block_size_width,4 * block_size_height,block_size_width,block_size_height,shield_block_image,screen,&myDot);
    blockList.push_back(block);
*/



    myDot.blockList = &blockList;

     Paddle hero((float)SCREEN_WIDTH/2,(float)SCREEN_HEIGHT-50,50,50,block_image,screen,&myDot,&event);

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

        hero.handleInput();

        //=== LOGIC ===//
        myDot.move();
        hero.logic();
        if (hero.isDead){
            break;
        }
        list< Block* > :: iterator blockIterator;
        blockIterator = blockList.begin();
        while(blockIterator != blockList.end()){


        ((Block*)(*blockIterator))->logic();

        if(((Block*)(*blockIterator))->life <= 0){
            delete ((Block*)(*blockIterator));
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
        hero.showHP();

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
