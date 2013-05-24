#ifndef PADDLE_H
#define PADDLE_H

#include "block.h"


class Paddle : public Block
{
    public:
        Paddle(float x, float y, int width, int height,
              SDL_Surface *image, SDL_Surface *screen,
              Dot *dot, SDL_Event *event);
        SDL_Event *event;
        virtual ~Paddle();
        void handleInput();

        virtual void logic();
    protected:
    private:
};

#endif // PADDLE_H
