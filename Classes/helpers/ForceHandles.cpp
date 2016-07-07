#include "ForceHandles.h"

ForceHandles::ForceHandles(MainScene *s, Vec2 g) {
    _scene = s;
    _gravity = g;
}

void ForceHandles::displayHandles_onSnail(Vec2 force, Vec2 snail_pos) {
    displayHandles(_handleCount, snail_pos, force);
}

void ForceHandles::clearHandles() {
    // TODO delte handleObjs from MainScene
    /*
    for (Sprite handle : _handleObjs) {

    }
     */
}

/**
 * recursive version of displayHandles_onSnail visible to MainScne
 */
void ForceHandles::displayHandles(int count, Vec2 start_coord, Vec2 force) {
    if (count > 0){
        drawHandle(start_coord);
        Vec2 nextPos = start_coord + force.getNormalized() * _defaultHandleOffset; //* force.getLength();
        displayHandles(count -1, nextPos, force);
    } else return;
}

void ForceHandles::drawHandle(Vec2 pos) {
    // TODO drawHandle in position of parameter
}




