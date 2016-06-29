#ifndef Snail_h
#define Snail_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Snail : public Layer
{
    int health;
    Sprite *snail_sprite;
    
public:
    bool ground_state;
    bool air_state;
    bool base;
    Snail();
    virtual ~Snail();
    void setHealth(int _health);
    void setSprite(Sprite *_snail_sprite);
    Sprite * getSprite();    
};


#endif /* Snail_h */
