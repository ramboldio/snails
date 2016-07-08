
#ifndef highscore_h
#define highscore_h

#include <stdio.h>
#include "cocos2d.h"
#include "../helpers/json.hpp"


using namespace cocos2d;

class Highscore : public Layer {

    Highscore();

    struct entry {
        std::string name, int score;
    };

    std::list<entry>* _scoreboard;
    UserDefault* _storage;

    void loadFromStorage();
    void writeToStorage();
public:

    void add(entry newItem);
    void add(std::string name, int score);
    void clear();
    std::list<entry> getList();
};


#endif //MYGAME_HIGHSCORE_H
