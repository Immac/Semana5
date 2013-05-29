#ifndef SHIELDBLOCK_H
#define SHIELDBLOCK_H

#include "block.h"


class ShieldBlock : public Block
{
    public:
        ShieldBlock();
                     ShieldBlock(float x, float y, int width, int height,SDL_Surface *image,SDL_Surface *screen, Dot *dot);
        virtual void logic();
        virtual ~ShieldBlock();
    protected:
    private:
};

#endif // SHIELDBLOCK_H
