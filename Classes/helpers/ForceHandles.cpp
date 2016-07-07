#include "ForceHandles.h"

ForceHandles::ForceHandles(Node *s, Vec2 g) {
    _game_layer = s;
    _gravity = g;
    for (int i = 0; i < _handleCount; ++i) {
        auto point = Sprite::create("res/green_point.png");
        point->setVisible(false);
        _game_layer->addChild(point);
        _handleObjs[i] = point;
    }
}

void ForceHandles::displayHandles_onSnail(Vec2 force, Vec2 snail_pos) {
    displayHandles(_handleCount, snail_pos, force);
}

void ForceHandles::clearHandles() {
    for (Sprite* handle : _handleObjs) {
        handle->setVisible(false);
    }
}

/**
 * recursive version of displayHandles_onSnail visible to MainScne
 */
void ForceHandles::displayHandles(int count, Vec2 start_coord, Vec2 force) {
    if (count > 0){
        drawHandle(count, start_coord);
        Vec2 nextPos = start_coord + force.getNormalized() * _defaultHandleOffset; //* force.getLength();
        displayHandles(count -1, nextPos, force);
    } else return;
}

void ForceHandles::drawHandle(int i, Vec2 pos) {
    // TODO drawHandle in position of parameter
    _handleObjs[i]->setPosition(pos);
    _handleObjs[i]->setVisible(true);
}




