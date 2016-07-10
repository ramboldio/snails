
#include "Highscore.h"

// json lib https://github.com/nlohmann/json
#include "../helpers/json.hpp"
using json = nlohmann::json;



Highscore::Highscore() {
    _storage = cocos2d::UserDefault::getInstance();
    _scoreboard = new std::list<entry>();
    loadFromStorage();

    // sample set
    add({"test23", 921});
    add({"Lukas", 651});
    add("middleMan", 700);
}

void Highscore::add(entry newItem) {
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

    // TODO remove test
    loadFromStorage();
}

void Highscore::add(std::string name, int score) {
    add({name, score});
}

void Highscore::loadFromStorage() {
    try {
        auto response = json::parse(_storage->getStringForKey(SCORE_KEY));
        // std::cout << json.dump(4) << std::endl;
        // _scoreboard = json.at(0);
        // TODO properly parse json string to list
        for (json::iterator it = response.begin(); it != response.end(); ++it) {
            std::cout << it.key() << " : " << it.value() << "\n";
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
