
#include "Highscore.h"

// json lib https://github.com/nlohmann/json
#include "../helpers/json.hpp"
#include <ctime>

using json = nlohmann::json;

Highscore::Highscore() {
    _storage = cocos2d::UserDefault::getInstance();
    _scoreboard = new std::list<entry>();
    loadFromStorage();
}

void Highscore::add(entry newItem) {
    // TODO limit list length

    // set timestamp as name
    time_t now = time(0);   // get time now

    // TODO make time more pretty
    newItem.name = std::asctime(std::localtime(&now));

    // create iterator
    std::list<entry>::iterator it;

    for (it=_scoreboard->begin(); it!=_scoreboard->end(); ++it) {
        // wait for position when score can be inserted
        if (it->score < newItem.score) {
            _scoreboard->insert(it, newItem);
            break;
        }
        // last player
    }
    if (it==_scoreboard->end()) {
        _scoreboard->push_back(newItem);
    }
    writeToStorage();
}

void Highscore::add(std::string name, int score) {
    add({name, score});
}

void Highscore::loadFromStorage() {
    _scoreboard->clear();

    try {
        auto response = json::parse(_storage->getStringForKey(SCORE_KEY));
        // TODO properly parse json string to list
        for (int i = 0; i < response.size(); ++i) {
            json e = response.at(i);
            _scoreboard->push_back({e["name"], e["score"]});
        }

    } catch (const std::exception e){
        log("Could not load Highscores from local storage!");
    }

}

void Highscore::writeToStorage() {
    json j;
    for (std::list<entry>::iterator it = _scoreboard->begin(); it != _scoreboard->end(); it++) {
        json entry;
        entry["name"] = it->name;
        entry["score"] = it->score;
        j.push_back(entry);
    }
    _storage->setStringForKey(SCORE_KEY, j.dump());
}

void Highscore::clear() {
    _storage->setStringForKey(SCORE_KEY, "");
    loadFromStorage();
}

std::list<entry>* Highscore::getList() {
    return _scoreboard;
}

void Highscore::writeSampleScores() {
    Highscore* h = new Highscore();
    h->clear();
    h->add({"test23", 921});
    h->add({"Lukas", 651});
    h->add("middleMan", 700);
}
