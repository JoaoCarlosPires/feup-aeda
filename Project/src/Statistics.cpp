#include <iostream>
#include "Statistics.h"

using namespace std;

Statistics::Statistics(): goals_scored(0), goals_conceded(0), shots(0), ball_possession(0), yellow_cards(0), red_cards(0),
                            injured(0), free_kicks(0), corner_kicks(0) {
}


Statistics::Statistics(int goalsScored, int goalsConceded, int shots, int ballPossession, int yellowCards, int redCards,int injured, int freeKicks, int cornerKicks) :
    goals_scored(goalsScored), goals_conceded(goalsConceded),
    shots(shots), ball_possession(ballPossession),
    yellow_cards(yellowCards), red_cards(redCards),
    injured(injured), free_kicks(freeKicks),
    corner_kicks(cornerKicks) {
}

int Statistics::getGoalsScored() const {
    return goals_scored;
}

void Statistics::setGoalsScored(int goalsScored) {
    goals_scored = goalsScored;
}

int Statistics::getGoalsConceded() const {
    return goals_conceded;
}

void Statistics::setGoalsConceded(int goalsConceded) {
    this->goals_conceded = goalsConceded;
}

int Statistics::getShots() const {
    return shots;
}

void Statistics::setShots(int shots) {
    Statistics::shots = shots;
}

int Statistics::getBallPossession() const {
    return ball_possession;
}

void Statistics::setBallPossession(int ballPossession) {
    ball_possession = ballPossession;
}

int Statistics::getYellowCards() const {
    return yellow_cards;
}

void Statistics::setYellowCards(int yellowCards) {
    yellow_cards = yellowCards;
}

int Statistics::getRedCards() const {
    return red_cards;
}

void Statistics::setRedCards(int redCards) {
    red_cards = redCards;
}

int Statistics::getInjured() const {
    return injured;
}

void Statistics::setInjured(int injured) {
    Statistics::injured = injured;
}

int Statistics::getFreeKicks() const {
    return free_kicks;
}

void Statistics::setFreeKicks(int freeKicks) {
    free_kicks = freeKicks;
}

int Statistics::getCornerKicks() const {
    return corner_kicks;
}

void Statistics::setCornerKicks(int cornerKicks) {
    corner_kicks = cornerKicks;
}

void Statistics::info() const {
    cout << "Goal Scored: " << goals_scored << endl;
    cout << "Goal Conceded: " << goals_conceded << endl;
    cout << "Shots: " <<shots << endl;
    cout << "Ball Possession: " <<ball_possession << endl;
    cout << "Yellow Cards: " <<yellow_cards << endl;
    cout << "Red Cards: " << red_cards << endl;
    cout << "Injured Players: " << injured << endl;
    cout << "Free Kicks: " << free_kicks << endl;
    cout << "Corner Kicks: " << corner_kicks << endl;

}

std::ostream &operator<<(std::ostream &os, const Statistics &statistics) {
    os << statistics.goals_scored << endl;
    os << statistics.goals_conceded << endl;
    os << statistics.shots << endl;
    os << statistics.ball_possession << endl;
    os << statistics.yellow_cards << endl;
    os << statistics.red_cards << endl;
    os << statistics.injured << endl;
    os << statistics.free_kicks << endl;
    os << statistics.corner_kicks;

    return os;
}

void GoalkeeperStatistics::info() const {
    cout << "Saves: " << saves << endl;
    cout << "Clearances: " << clearances << endl;
    cout << "Yellow Cards: " <<yellow_cards << endl;
    cout << "Red Cards: " << red_cards << endl;
}

void GoalkeeperStatistics::writeStats(std::ostream &os) const {
    os << saves << endl;
    os << clearances << endl;
    os  <<yellow_cards << endl;
    os  << red_cards;
}

void GoalkeeperStatistics::updateStats(std::istream &in) {
    cout << "Saves: " << endl;
    cin >> saves;
    cout << "Clearances: " << endl;
    cin >> clearances;
    cout << "Yellow Cards: " << endl;
    cin >> yellow_cards;
    cout << "Red Cards: " << endl;
    cin >> red_cards;
}

void DefenderStatistics::info() const {
    cout << "Disarms: " << disarm << endl;
    cout << "Fouls: " << fouls << endl;
    cout << "Yellow Cards: " <<yellow_cards << endl;
    cout << "Red Cards: " << red_cards << endl;
}

void DefenderStatistics::writeStats(std::ostream &os) const {
    os << disarm << endl;
    os << fouls << endl;
    os << yellow_cards << endl;
    os << red_cards;
}

void DefenderStatistics::updateStats(std::istream &in) {
    cout << "Disarm: " << endl;
    cin >> disarm;
    cout << "Fouls: " << endl;
    cin >> fouls;
    cout << "Yellow Cards: " <<  endl;
    cin >> yellow_cards;
    cout << "Red Cards: " << endl;
    cin >> red_cards;
}

void MidfielderStatistics::info() const {
    cout << "Passing Accuracy: " << passing_accuracy << endl;
    cout << "Shots: " << shots << endl;
    cout << "Yellow Cards: " <<yellow_cards << endl;
    cout << "Red Cards: " << red_cards;
}

void MidfielderStatistics::writeStats(std::ostream &os) const {
    os << passing_accuracy << endl;
    os << shots << endl;
    os << yellow_cards << endl;
    os << red_cards;
}

void MidfielderStatistics::updateStats(std::istream &in) {
    cout << "Passing Accuracy: " << endl;
    cin >> passing_accuracy;
    cout << "Shots: " << endl;
    cin >> shots;
    cout << "Yellow Cards: " << endl;
    cin >> yellow_cards;
    cout << "Red Cards: " << endl;
    cin >> red_cards;
}

void ForwardStatistics::info() const {
    cout << "Goals: " << total_goals << endl;
    cout << "Shots: " << shots << endl;
    cout << "Yellow Cards: " << yellow_cards << endl;
    cout << "Red Cards: " << red_cards << endl;
}

void ForwardStatistics::writeStats(std::ostream &os) const {
    os << total_goals << endl;
    os << shots << endl;
    os << yellow_cards << endl;
    os << red_cards;
}

void ForwardStatistics::updateStats(std::istream &in) {
    cout << "Goals: " << endl;
    cin >> total_goals;
    cout << "Shots: " << endl;
    cin >> shots;
    cout << "Yellow Cards: " << endl;
    cin >> yellow_cards;
    cout << "Red Cards: " << endl;
    cin >> red_cards;
}

std::ostream &operator<<(std::ostream &os, const PlayerStatistics * p) {
    p->writeStats(os);
    return os;
}

std::istream &operator>>(std::istream &in, PlayerStatistics * p) {
    p->updateStats(in);
    return in;
}
