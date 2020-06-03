#include "Game.h"

using namespace std;

//Constructor(s)

Game::Game(string opponent, string country, string city, string stadium, Date gameDate,
        vector<Player *> called_players, Statistics stats): opponent(opponent), country(country), city(city), stadium(stadium), gameDate(gameDate),
                                                                      called_players(called_players), game_stats(stats) {
}

//Get Methods
string Game::getCountry() const {
    return country;
}
string Game::getCity() const {
    return city;
}
string Game::getStadium() const {
    return stadium;
}

Date Game::getDate() const {
    return gameDate;
}

vector<Player *> Game::getCalledPlayers() const {
    return called_players;
}

void Game::info() const {
    cout << "------------------------------------------------ Game ---------------------------------------------------" <<endl;
    cout << "Opponent: "  << opponent << endl;
    cout << "Country: " << country << endl;
    cout << "City: " <<city << endl;
    cout << "Stadium: " <<stadium << endl;
    cout << "Date: " <<gameDate << endl;
    cout << "--------------------------------------------- Called Players -------------------------------------------" <<endl;
    for (auto it = called_players.begin(); it != called_players.end(); it++){
        (*it)->infoTable();
        cout << endl;
    }
    cout << "--------------------------------------------- Game Statistics -------------------------------------------" <<endl;
    game_stats.info();
    cout << "---------------------------------------------------------------------------------------------------------" <<endl;
}

string Game::getOpponent() const {
    return opponent;
}

void Game::setStats(Statistics stats) {
    this->game_stats = stats;
}

Statistics Game::getStatistics() const {
    return this->game_stats;
}

std::ostream &operator<<(std::ostream &out, const Game &g) {
    out << g.opponent << endl;
    out << g.country << endl;
    out << g.city << endl;
    out << g.stadium << endl;
    out << g.gameDate << endl;
    out << g.game_stats;
    return out;
}

void Game::setOpponent(const string &opponent) {
    Game::opponent = opponent;
}

void Game::setCountry(const string &country) {
    Game::country = country;
}

void Game::setCity(const string &city) {
    Game::city = city;
}

void Game::setStadium(const string &stadium) {
    Game::stadium = stadium;
}

void Game::setGameDate(const Date &gameDate) {
    Game::gameDate = gameDate;
}

void Game::setCalledPlayers(const vector<Player *> &calledPlayers) {
    called_players = calledPlayers;
}

void Game::setGameStats(const Statistics &gameStats) {
    game_stats = gameStats;
}



