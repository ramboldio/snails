
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
    void add(std::string name, int score);

    void clear();

    std::list<entry>* getList();

    static void writeSampleScores();

private:

    std::list<entry>* _scoreboard;

    UserDefault* _storage;
    void loadFromStorage();
    void writeToStorage();
    static void trim(std::list<entry>* list, int index);

};


#endif //MYGAME_HIGHSCORE_H
