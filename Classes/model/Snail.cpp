#include "Snail.h"

Snail::Snail(void){
    this->snail_sprite = Sprite::create("res/snail_base.png");
    this->health = 5;
    this->base = true;
}

Snail::~Snail(){}


void Snail::setHealth(int _health) {
    this->health = _health;
}

int Snail::getHealth() {
    return this->health;
}

void Snail::setSprite(Sprite *_snail_sprite) {
    this->snail_sprite = _snail_sprite;
}

Sprite * Snail::getSprite() {
    return this->snail_sprite;
}
