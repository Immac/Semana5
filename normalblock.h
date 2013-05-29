#ifndef NORMALBLOCK_H
#define NORMALBLOCK_H

#include "block.h"


class NormalBlock : public Block
{
    public:
        NormalBlock();
        NormalBlock(float x, float y, int width, int height,
              SDL_Surface *image, SDL_Surface *screen,
              Dot *dot);
        virtual ~NormalBlock();
        virtual void logic();
    protected:
    private:
};

#endif // NORMALBLOCK_H
