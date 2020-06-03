#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "Team.h"
#include "utils.h"

using namespace std;

Team::Team(){
}

Team::Team(string file_name) {
    ifstream info(file_name);
    vector<string> file_info;
    string str_temp;

    while (getline(info, str_temp)) file_info.push_back(str_temp);

    this->teamName = file_info[0];
    this->team_players = read_player(file_info[1]);
    this->team_staff = read_staff(file_info[2]);
    this->team_competitions = read_competion(file_info[3], this);
    this->team_coaches = read_coachs(file_info[4]);
    this->team_providers = read_providers(file_info[5]);
    this->team_equipment = read_equipment(file_info[6]);
}

void Team::updateFile(string file_name) {

    ofstream init(file_name);
    init << teamName << endl;
    init << teamName + "players.txt" << endl;
    init << teamName + "staff.txt" << endl;
    init << teamName + "competition.txt" << endl;
    init << teamName + "coaches.txt" << endl;
    init << teamName + "providers.txt" << endl;
    init << teamName + "equipment.txt" << endl;


    ofstream p(teamName + "players.txt");
    for (size_t i = 0; i < team_players.size(); i++) {
        p << (*team_players[i]) << endl;
        p << "-----" << endl;
    }

    ofstream s(teamName + "staff.txt");
    auto itTable = team_staff.begin();
    for(;  itTable  != team_staff.end(); itTable ++){
        s << (* itTable )<< endl;
        s << "-----" << endl;
    }


    ofstream c(teamName + "competition.txt");

    int num = 0;
    for (size_t i = 0; i < team_competitions.size(); i++) {
        c << team_competitions[i]->getCompetitionName() << endl;

        ofstream call(teamName + "called" + to_string(num) + ".txt");
        c <<teamName + "called" + to_string(num) + ".txt" << endl;

        map<Player *, int> called_write = team_competitions[i]->getCalledInjured();
        for(auto i : called_write)
            call << i.first->getName() << "!" << i.second << endl;

        ofstream gam(teamName + "games" + to_string(num) + ".txt");
        c << teamName + "games" + to_string(num) + ".txt" << endl;

        vector<Game *> games_write = team_competitions[i]->getGames();
        for(size_t j = 0; j < games_write.size(); j++) {
            gam << (*games_write[j]) << endl;
            gam << "-----" << endl;
        }
        num++;
        c << team_competitions[i]->getStartDate() << endl;
        c << team_competitions[i]->getEndDate() << endl;
        c << team_competitions[i]->getMoneyAccommodation() << endl;
        c << team_competitions[i]->getPaid() << endl;
        c << "-----" << endl;
    }

    ofstream coach_w(teamName + "coaches.txt");
    BST<Coach> coach_tree = team_coaches.getTree();
    BSTItrIn<Coach> it(coach_tree);
    while (!it.isAtEnd()) {
        coach_w << it.retrieve().getName() << endl;
        coach_w << it.retrieve().getBirthday() << endl;
        coach_w << it.retrieve().getCurrentCoach() << endl;
        coach_w << it.retrieve().getTitles() << endl;
        vector<std::tuple<string, Date, Date>> tr = it.retrieve().getTrainedTeams();
        for(auto &i : tr) {
            coach_w << get<0>(i) << "!" <<get<1>(i) << "!" <<get<2>(i) <<endl;
        }
        coach_w << "-----" << endl;
        it.advance();
    }



    Equipment equip4;
    priority_queue<Provider> aux = team_providers.getProviders();
    ofstream pr(teamName + "providers.txt");
    while (!aux.empty()) {
        pr << aux.top().getName() << endl;
        pr << aux.top().getReputation() << endl;
        equip4 = aux.top().getEquipment();
        pr << equip4.football_kit << endl;
        pr << equip4.balls << endl;
        pr << equip4.football_boots << endl;
        pr << equip4.cones << endl;
        pr << equip4.goal << endl;
        pr << equip4.tactics_board << endl;
        pr << equip4.medical_kit << endl;
        pr << equip4.water_bottles << endl;
        pr << "-----" << endl;
        aux.pop();
    }

    ofstream eq(teamName + "equipment.txt");
    Equipment * equip5 = getEquipment();
    eq << equip5->football_kit << endl;
    eq << equip5->balls << endl;
    eq << equip5->football_boots << endl;
    eq << equip5->cones << endl;
    eq << equip5->goal << endl;
    eq << equip5->tactics_board << endl;
    eq << equip5->medical_kit << endl;
    eq << equip5->water_bottles << endl;
}

void Team::setTeamName(string team_name) {
    this->teamName = team_name;
}


string Team::getTeamName() const {
    return teamName;
}

vector<Player *> Team::getPlayers() const {
    return team_players;
}

const tabH &Team::getStaff() const {
    return team_staff;
}

CoachTree * Team::getCoachs() {
    return &team_coaches;
}

ProviderPriorityQueue * Team::getProviders() {
    return &team_providers;
}

Equipment * Team::getEquipment() {
    return &team_equipment;
}

vector<Competition *> Team::getCompetition() const {
    return team_competitions;
}

vector<Game *> Team::getGames() const {
    vector<Game *> ret_games;
    for (size_t i = 0; i < team_competitions.size(); i++) {
        vector<Game *> competitions_games = team_competitions[i]->getGames();
        for (size_t j = 0; j < competitions_games.size();j++)
            ret_games.push_back(competitions_games[j]);
    }
    return ret_games;
}

double Team::getMoneyPlayers() const {
    double money = 0;
    for (size_t i = 0; i < team_players.size(); i++)
        money += team_players[i]->getEarnings();
    return money;
}

double Team::getMoneyStaff() const {
    double money = 0;
    auto it = team_staff.begin();
    for (;it != team_staff.end(); it++)
        if(it->isWorking1())
            money += it->getSalary();
    return money;
}

int Team::missingPay() {
    double not_paid = 0;
    for (size_t i = 0; i < team_competitions.size(); i++)
        if (!(team_competitions[i]->getPaid()))
            not_paid++;
    return not_paid;
}

void Team::showPlayersTable() const {
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Club" << " | " << setw(10) << "Position" << " | " << setw(6) << "Weight" << " | " << setw(8)
    << "Height" << " | " << setw(7) << "Value" << " | " << setw(9) <<  "Earnings" << " |" <<setw(6) <<  "Index" << " |" << endl;
    for(int i = 0; i < team_players.size(); i++){
        team_players[i]->infoTable();
        cout << setw(6) <<  i << " |" << endl;
    }
}

vector<int> Team::showStaffTable() const {
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Function" << " | " << setw(9) << "Salary" << " | " <<setw(6) <<  "Index" << " |" << endl;;
    auto it = team_staff.begin();
    vector<int> vec;
    int i = 0;
    for(; it != team_staff.end();i++, it++){
        if(it->isWorking1()){
            it->infoTable();
            cout << setw(6) <<  i << " |" << endl;
            vec.push_back(i);
        }
    }
    return vec;
}

void Team::sortPlayersName() {
    sort(team_players.begin(), team_players.end(), cmpName);
}

void Team::sortPlayersPosition() {
    sort(team_players.begin(), team_players.end(), cmpPosition);
}

void Team::sortPlayersValue() {
    sort(team_players.begin(), team_players.end(), cmpValue);
}

void Team::addPlayer(Player* p) {

    if(p->getName() == "") throw CantUseThatName(p->getName());

    for(size_t i = 0; i < team_players.size();i++){
        if(team_players[i]->getName() == p->getName()){
            throw PersonAlreadyExists(p->getName());
        }
    }
   team_players.push_back(p);
}

void Team::addStaff(Staff *s) {
    auto p = team_staff.insert(*s);
    if (!p.second)
        throw PersonAlreadyExists(s->getName());
}

vector<Player *> Team::findPlayerName(string name) {
    vector<Player *> v_players;
    for (size_t i = 0; i < team_players.size(); i++) {
        if (team_players[i]->getName().find(name) != string::npos) {
            v_players.push_back(team_players[i]);
        }
    }
    if (v_players.empty()) throw(PersonNotFound(name));
    else return v_players;
}

vector<Staff> Team::findStaffName(string name) {
    auto it = team_staff.begin();
    vector<Staff> v_staff;
    for( ; it != team_staff.end(); it++) {
        if (it->getName().find(name) != string::npos)
            v_staff.push_back(*it);
    }

    if (v_staff.empty()) throw(PersonNotFound(name));
    else return v_staff;
}

vector<Player *> Team::findPlayerPos(string position) {
    vector<Player *> v_players;
    for (size_t i = 0; i < team_players.size(); i++) {
        if (team_players[i]->getPosition().find(position) != string::npos) {
            v_players.push_back(team_players[i]);
        }
    }
    if (v_players.empty()) throw(PositionNotFound(position));
    else return v_players;
}

vector<Staff> Team::findStaffFunction(string function) {
    auto it = team_staff.begin();
    vector<Staff> v_staff;
    for( ; it != team_staff.end(); it++) {
        if (it->getFunction() == function)
            v_staff.push_back(*it);
    }

    if (v_staff.empty()) throw(FunctionNotFound(function));
    else return v_staff;
}

Player * Team::findPlayer(string name) {
    for (size_t i = 0; i < team_players.size(); i++)
    {
        if (team_players[i]->getName().find(name) != string::npos)
            return team_players[i];
    }
    throw(PersonNotFound(name));
}

void Team::removePlayer( Player * p) {
    for(size_t i = 0; i < team_players.size();i++){
        if(team_players[i]->getName() == p->getName()){
            team_players.erase(team_players.begin()+i);
        }
    }
}

void Team::removeStaff(Staff s) {
    auto it = team_staff.find(s);
    if(it != team_staff.end())
        team_staff.erase(it);
    else
        throw PersonNotFound(s.getName());
}

double Team::getMoneyAccommodation() const {
    double money = 0;
    for (size_t i = 0; i < team_competitions.size(); i++)
        money += team_competitions[i]->getMoneyAccommodation();
    return money;
}

void Team::addCompetition(Competition *c) {
    for(size_t i = 0; i < team_competitions.size();i++){
        if(team_competitions[i]->getCompetitionName() == c->getCompetitionName()){
            throw CompetitionAlreadyExists(c->getCompetitionName());
        }
    }
    team_competitions.push_back(c);
}

void Team::removeCompetition(Competition *c) {
    bool found = false;
    for (size_t i = 0; i < team_competitions.size(); i++){
        if(team_competitions[i] == c){
            team_competitions.erase(team_competitions.begin() + i);
            found = true;
        }
    }
    if(!found){
        throw CompetitionNotFound(c->getCompetitionName());
    }
}

void Team::setStaffNotWorking(Staff s) {
    auto it = team_staff.find(s);
    if( it != team_staff.end()){
        team_staff.erase(it);
        s.setIsWorking(false);
        team_staff.insert(s);
    }
    else throw PersonNotFound(s.getName());
}

void Team::showStaff() {
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Function" << " | " << setw(9) << "Salary" << " | " <<setw(6) <<  "Index" << " |" << endl;;
    int i = 0;
    auto it = team_staff.begin();
    for(; it != team_staff.end();it++){
        it->infoTable();
        cout << setw(6) <<  i << " |" << endl;
        i++;
    }
}

void Team::showStaffRemoved() {
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Function" << " | " << setw(9) << "Salary" << " | " <<setw(6) <<  "Index" << " |" << endl;;
    auto it = team_staff.begin();
    int i = 0;
    for(; it != team_staff.end();i++, it++){
        if(!it->isWorking1()){
            it->infoTable();
            cout << setw(6) <<  i << " |" << endl;
        }
    }
}

void Team::sortStaffName() {

    auto it = team_staff.begin();
    vector<Staff> v;
    for(;it != team_staff.end();it++){
        v.push_back(*it);
    }
    sort(v.begin(), v.end(), cmpStaffName);
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Function" << " | " << setw(9) << "Salary" << " | " <<setw(6) <<  "Index" << " |" << endl;;

    for(size_t i = 0; i < v.size();i++){
        v[i].infoTable();
        cout << setw(6) <<  i << " |" << endl;
    }

}

void Team::sortStaffFunction() {


    auto it = team_staff.begin();
    vector<Staff> v;
    for(;it != team_staff.end();it++){
        v.push_back(*it);
    }
    sort(v.begin(), v.end(), cmpFunction);
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Function" << " | " << setw(9) << "Salary" << " | " <<setw(6) <<  "Index" << " |" << endl;;

    for(size_t i = 0; i < v.size();i++){
        v[i].infoTable();
        cout << setw(6) <<  i << " |" << endl;
    }
}

int Team::workingStaff() {
    auto it = team_staff.begin();
    int i = 0;
    for(; it != team_staff.end(); it++){
        if(it->isWorking1())
            i++;
    }

    return i;
}









