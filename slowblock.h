#ifndef SLOWBLOCK_H
#define SLOWBLOCK_H

#include "block.h"


class SlowBlock : public Block
{
    public:
        SlowBlock();
    SlowBlock(float x, float y, int width, int height,SDL_Surface *image,SDL_Surface *screen, Dot *dot);
        virtual ~SlowBlock();
        virtual void logic();

    protected:
    private:
};

#endif // SLOWBLOCK_H
