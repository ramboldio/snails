#include "Snail.h"

Snail::Snail(void){
    this->snail_sprite = Sprite::create("res/snail_base.png");
    //this->health = 5;
}

Snail::~Snail(){}


void Snail::setHealth(int _health) {
    this->health = _health;
}

void Snail::setSprite(Sprite *_snail_sprite) {
    this->snail_sprite = _snail_sprite;
}

Sprite * Snail::getSprite() {
    return this->snail_sprite;
}
