#ifndef DOT_H
#define DOT_H

#include <cmath>

#include "Particle.h"
#include "SDL_ttf.h"
#include <cstring>
#include <list>
#include "block.h"
#include "SDL_mixer.h"
class Block;
#define TOTAL_PARTICLES 20

using namespace std;

class Dot
{

    private:
    //The offsets

    SDL_Surface *red = NULL;
    SDL_Surface *green = NULL;
    SDL_Surface *blue = NULL;

    SDL_Surface *dot = NULL;


    SDL_Surface *screen;

    //The particles
    Particle *particles[ TOTAL_PARTICLES ];

    public:
        enum State{
        NORMAL,
        SLOWED,
        GRAVITY,
        SHIELD
        };
        float x, y;
        int currentState;
        int durationState;
        void handleState();
        void startSlow();
        void startNormal();
        void startGravity();
        void startShield();
        float angle, velocity;
        int damage;
        const float DOT_WIDTH = 20;
        const float DOT_HEIGHT = 20;
        const float INIT_VELOCITY = 8;
        list < Block* > *blockList;
           Mix_Chunk * sfxShield;
            Mix_Chunk * sfxGravity;
            Mix_Chunk * sfxBound;
            void soundRebound();
    //Initializes
    Dot(SDL_Surface *screen);

    //Cleans up particles
    ~Dot();

    //Handles keypresses
    void handle_input();

    //Moves the dot
    void move();

    //Shows the particles
    void show_particles();

    //Shows the dot
    void show();
};

#endif // DOT_H
