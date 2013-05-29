#ifndef PADDLE_H
#define PADDLE_H

#include "block.h"


class Paddle : public Block
{
    public:
        enum States{
        IDLE,
        WALK_RIGHT,
        WALK_LEFT,
        SPIN_RIGHT,
        SPIN_LEFT,
        JUMP,
        TAKING_DAMAGE,
        SPIN_ATTACK
        };
        bool canCollide();
        bool isDead;
        States currentState;
        Paddle(float x, float y, int width, int height,
              SDL_Surface *image, SDL_Surface *screen,
              Dot *dot, SDL_Event *event);
              SDL_Surface *animations[5];
              SDL_Surface *health[3];
        SDL_Event *event;
        int invulnerableTime;
        int attackCooldownTime;
        virtual ~Paddle();
        void handleInput();
        virtual void show();
        virtual void logic();
        void checkState();
        void takeDamage();
        void getHit(int collision);
        void attackRight();
        void attackLeft();
        void attackNeutral();
        void showHP();
        Mix_Chunk * chunk;
    protected:
    private:
};

#endif // PADDLE_H
