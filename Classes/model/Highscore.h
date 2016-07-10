
#ifndef highscore_h
#define highscore_h

#include <stdio.h>
#include "cocos2d.h"

#define SCORE_KEY "highscore_table"

using namespace cocos2d;

struct entry {
    std::string name; int score;
};

class Highscore : public Layer {


public:

    Highscore();
    void add(entry newItem);

    void clear();

    std::list<entry>* getList();

private:

    std::list<entry>* _scoreboard;

    void add(std::string name, int score);

    UserDefault* _storage;
    void loadFromStorage();
    void writeToStorage();
};


#endif //MYGAME_HIGHSCORE_H
