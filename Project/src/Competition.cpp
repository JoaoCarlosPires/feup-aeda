#include <iomanip>
#include "Competition.h"

using namespace std;


Competition::Competition(string name, std::map<Player *, int> called_injured, Date start, Date end, double moneyAccomodation):
        name(name), called_injured(called_injured),start(start),end(end), moneyAccommodation(moneyAccomodation) {
    this->paid = 0;
}

Competition::Competition(string name, std::map<Player *, int> called_injured, std::vector<Game *> team_games, Date start, Date end, double moneyAccommodation, bool paid):
    name(name), called_injured(called_injured), team_games(team_games),
    start(start), end(end), moneyAccommodation(moneyAccommodation), paid(paid) {
}

string Competition::getCompetitionName() const {
    return name;
}

std::map<Player *, int> Competition::getCalledInjured() const {
    return called_injured;
}

vector<Game *> Competition::getGames() const {
    return team_games;
}

ostream &operator<<(ostream &out, const Competition &comp) {
    out << "Competition name: " << comp.name << endl;
    out << "Number of Games: " << comp.team_games.size() << endl;
    out << "Start Date: " << comp.start << endl;
    out << "End Date: " << comp.end << endl;
    return out;
}


bool Competition::getPaid() const {
    return paid;
}


double Competition::getMoneyInsurance() const {
    double value = 0;
    int numDays = start.daysUntil(end);
    for (auto i : called_injured) {
        value += (i.first)->getInsurance() * (numDays - i.second) + (i.first)->getInsurance() * i.second * 3;
    }
    return value;
}


void Competition::payPlayers() {
    if(!paid) {
        int numDays = start.daysUntil(end);
        for (auto i : called_injured) {
            double value = (i.first)->getInsurance() * (numDays - i.second) + (i.first)->getInsurance() * i.second * 3;
            (i.first)->setEarnings(value);
        }
        paid = true;
    }
    else throw(AlreadyPaid(name));

}

Date Competition::getStartDate() const {
    return start;
}

Date Competition::getEndDate() const{
    return end;
}

double Competition::getMoneyAccommodation() const {
    return moneyAccommodation;
}

vector<Player *> Competition::getCalled() const {
    vector<Player *> called;
    for(auto i : called_injured)
        called.push_back(i.first);
    return called;
}

void Competition::showPlayers() const {
    for (auto i : called_injured)
       i.first->info();
}

void Competition::showGames() const {
    for(size_t i = 0; i < team_games.size();i++){
        team_games[i]->info();
    }
}

void Competition::addGame(Game * g) {
    for(size_t i = 0;i < team_games.size();i++ ){
        if(team_games[i]->getOpponent() == g->getOpponent()&&
           team_games[i]->getCountry() == g->getCountry()&&
           team_games[i]->getCity() == g->getCity()&&
           team_games[i]->getStadium() == g->getStadium()&&
           team_games[i]->getDate().isEqualTo(g->getDate())){
            throw GameAlreadyExists(g->getOpponent(),g->getCountry(),g->getCity(),g->getStadium(),g->getDate());
        }
    }
    team_games.push_back(g);
}

Game * Competition::findGame(string opponent, Date date) const {

    for(size_t i = 0 ; i < team_games.size(); i++){
        if( team_games[i]->getOpponent().find(opponent) != string::npos &&
            team_games[i]->getDate().isEqualTo(date)){
            return team_games[i];
        }
    }
    throw GameNotFound(opponent,date);
}

void Competition::removeGame(string opponent, Date date) {
    bool found = false;
    for(size_t i = 0 ; i < team_games.size(); i++){
        if( team_games[i]->getOpponent().find(opponent) != string::npos &&
            team_games[i]->getDate().isEqualTo(date)){
            team_games.erase(team_games.begin() + i);
            found = true;
        }
    }
    if(!found){
        throw GameNotFound(opponent,date);
    }
}

void Competition::removeGame(Game *g) {
    for(size_t i = 0 ; i < team_games.size(); i++) {
        if (team_games[i]->getOpponent() == g->getOpponent() &&
            team_games[i]->getDate().isEqualTo(g->getDate())) {
            team_games.erase(team_games.begin() + i);
        }
    }
}

std::istream &operator>>(std::istream &in, Competition &comp) {

    return in;
}

void Competition::setName(const string &name) {
    Competition::name = name;
}

void Competition::setStart(const Date &start) {
    Competition::start = start;
}

void Competition::setEnd(const Date &end) {
    Competition::end = end;
}

void Competition::setMoneyAccommodation(double moneyAccommodation) {
    Competition::moneyAccommodation = moneyAccommodation;
}

void Competition::setPlayerInjuries(std::map<Player *, int> inj) {
    this->called_injured = inj;
}

void Competition::updatePlayerInjuries(Player * p, int i) {
    this->called_injured[p] = i;
}



