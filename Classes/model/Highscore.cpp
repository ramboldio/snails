
#include "Highscore.h"


Highscore::Highscore() {
    _storage = cocos2d::UserDefault::getInstance();
    _scoreboard = new std::list<entry>();
    loadFromStorage();

    // sample set
    _scoreboard->push_back({"Lukas", 651});
}

void Highscore::add(Highscore::entry newItem) {
    // create iterator
    std::list<entry>::iterator it;

    for (it=_scoreboard->begin(); it!=_scoreboard->end(); ++it) {
        // wait for position when score can be inserted
        if (it==_scoreboard->end() || it->score <= newItem.score) {
            _scoreboard->insert(it, newItem);
            break;
        }
    }
    writeToStorage();
}

void Highscore::add(std::string name, int score) {
    add({name, score});
}

void Highscore::loadFromStorage() {
    auto j_list = json::parse(_storage->getStringForKey(SCORE_KEY));
    _scoreboard = j_list[0];
}

void Highscore::writeToStorage() {
    json j = j_list(_scoreboard);
    _storage->setStringForKey(SCORE_KEY, j.dump());
}

void Highscore::clear() {
    _storage->setStringForKey(SCORE_KEY, "");
    loadFromStorage();
}

std::list<entry> Highscore::getList() {
    return std::list<entry>();
}
