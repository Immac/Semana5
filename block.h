#ifndef BLOCK_H
#define BLOCK_H
#include "SDL.h"
#include "SDL_image.h"
#include "Utility.h"
#include "Dot.h"
#include "SDL_mixer.h"
class Dot;
enum{
        NONE,
        TOP,
        BOT,
        LEFT,
        RIGHT,
        CORNERUL,
        CORNERUR,
        CORNERDL,
        CORNERDR,
        COLLIDING
        };

class Block
{

    public:

        Block(float x, float y, int width, int height,
              SDL_Surface *image, SDL_Surface *screen,
              Dot *dot);

        bool isColliding;
        bool wasColliding;
        Block();
        float x, y;
        int life;
        int current_frame;
        int current_power_duration;
        int width,height;
        SDL_Surface *image;
        SDL_Surface *screen;
        SDL_Surface *imagen2;
        Dot *dot;
        float xVel;
        float yVel;
            int collisionType();
        bool isPointInside(float pointX, float pointY);
        virtual void show();
        virtual void logic();
        void takeDamage();

        virtual ~Block();
    protected:
    private:

};

#endif // BLOCK_H
