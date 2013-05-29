#ifndef GRAVITYBLOCK_H
#define GRAVITYBLOCK_H

#include "block.h"


class gravityBlock : public Block
{
    public:
        gravityBlock();
        gravityBlock(float x, float y, int width, int height,SDL_Surface *image,SDL_Surface *screen, Dot *dot);
        virtual void logic();
        virtual ~gravityBlock();
    protected:
    private:
};

#endif // GRAVITYBLOCK_H
