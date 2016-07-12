
#include "Highscore.h"

// json lib https://github.com/nlohmann/json
#include "../helpers/json.hpp"

using json = nlohmann::json;

Highscore::Highscore() {
    _storage = cocos2d::UserDefault::getInstance();
    _scoreboard = new std::list<entry>();
    loadFromStorage();
}

void Highscore::add(entry newItem) {

    // set timestamp as name
    time_t now = time(NULL);   // get time now

    // TODO make time more pretty
    char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), "%d-%m-%Y %H:%M", std::localtime(&now));
    
    newItem.name = mbstr;
    
    // create iterator
    std::list<entry>::iterator it;

    for (it=_scoreboard->begin(); it!=_scoreboard->end(); ++it) {
        // wait for position when score can be inserted
        if (it->score >= newItem.score) {
            _scoreboard->insert(it, newItem);
            break;
        }
        // last player
    }
    if (it==_scoreboard->end()) {
        _scoreboard->push_back(newItem);
    }

    // delete entries which fall out of the ranking
    _scoreboard = trim(_scoreboard, 5);

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



// helper to cut off list
std::list<entry>* Highscore::trim(std::list<entry> *list, int index) {

    // if index is bigger than list there's no need to run the function
    if (list->size() < index) return list;

    std::list<entry> *newList = new std::list<entry>;
    std::list<entry>::iterator it = list->begin();
    int i = 0;

    while (it != list->end()) {
        newList->push_back({it->name, it->score});

        if (i >= index -1){
            return newList;
        }

        i++; it++;
    }
    return list;
}