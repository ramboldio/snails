#ifndef ForceHandles_h
#define ForceHandles_h

#include <stdio.h>
#include "../scenes/MainScene.h"
#include "cocos2d.h"

using namespace cocos2d;

// forward define MainScene Class
class MainScene;

class ForceHandles : public Layer{

    // apperance settings
    static const int _handleCount = 6;
    static const int _defaultHandleOffset = 20;

    Node * _game_layer;
    Vec2 _gravity;

    Sprite* _handleObjs [_handleCount];

    void displayHandles(int count, Vec2 start_coord, Vec2 force);
public:

    ForceHandles(Node *s, Vec2 g);

    void displayHandles_onSnail(Vec2 force, Vec2 snail_pos);

    void clearHandles();

    void drawHandle(int i, Vec2 pos);
};


#endif //MYGAME_FORCEHANDLES_H
