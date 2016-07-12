#ifndef Snail_h
#define Snail_h
#define SNAIL_HEALTH 5

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Snail : public Layer
{
    int health = SNAIL_HEALTH;
    Sprite *snail_sprite;
    
public:
    bool ground_state;
    bool air_state;
    bool base;
    Snail();
    virtual ~Snail();
    void setHealth(int _health);
    int getHealth();
    void setSprite(Sprite *_snail_sprite);
    Sprite * getSprite();    
};


#endif /* Snail_h */
