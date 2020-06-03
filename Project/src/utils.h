#ifndef AEDA_UTILS_H
#define AEDA_UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "Game.h"
#include "Person.h"
#include "Staff.h"
#include "Player.h"
#include "Statistics.h"
#include "Provider.h"
#include "Team.h"

CoachTree read_coachs(std::string file) {
    CoachTree coachs;
    ifstream info(file);
    std::vector<std::string> tempVec;
    string str_temp, name_tmp, start_tmp, end_tmp;

    while (getline(info, str_temp)) {
        if (str_temp != "-----") tempVec.push_back(str_temp);
        else{
            Date tempBirth(tempVec[1]);
            Coach c(tempVec[0], tempVec[1], stoi(tempVec[2]), stoi(tempVec[3]));

            for (size_t i = 4; i < tempVec.size(); i++) {
                std::stringstream tmp(tempVec[i]);
                getline(tmp, name_tmp, '!');
                getline(tmp, start_tmp, '!');
                getline(tmp, end_tmp, '!');

                c.addTrainedTeam(name_tmp, Date(start_tmp), Date(end_tmp));
            }
            coachs.addCoach(c);
            tempVec.clear();
        }
    }
    return coachs;
}

/// \brief Reads a provider from a .txt file.
/// \param info .txt file containing a Set of Providers
/// \return Vector of Providers belonging to a national team
ProviderPriorityQueue read_providers(std::string info){
    std::ifstream providers_info(info);
    ProviderPriorityQueue providers;
    std::vector<std::string> tempVec;
    std::string str_temp;

    while (getline(providers_info, str_temp)){
        if (str_temp != "-----") tempVec.push_back(str_temp);
        else{
            Equipment equip3;
            equip3.football_kit = stoi(tempVec[2]);
            equip3.balls = stoi(tempVec[3]);
            equip3.football_boots = stoi(tempVec[4]);
            equip3.cones = stoi(tempVec[5]);
            equip3.goal = stoi(tempVec[6]);
            equip3.tactics_board = stoi(tempVec[7]);
            equip3.medical_kit = stoi(tempVec[8]);
            equip3.water_bottles = stoi(tempVec[9]);
            Provider *p = new Provider(tempVec[0], stod(tempVec[1]), equip3);
            providers.addProvider(*p);
            tempVec.clear();
        }
    }

    return providers;
}

/// \brief Reads a equipment from a .txt file.
/// \param info .txt file containing all Equipment Items
/// \return Equipment Structure belonging to a national team
Equipment read_equipment(std::string info){
    std::ifstream equipment_info(info);
    Equipment aux;
    std::string str_temp;

    getline(equipment_info, str_temp);
    aux.football_kit = stoi(str_temp);
    getline(equipment_info, str_temp);
    aux.balls = stoi(str_temp);
    getline(equipment_info, str_temp);
    aux.football_boots = stoi(str_temp);
    getline(equipment_info, str_temp);
    aux.cones = stoi(str_temp);
    getline(equipment_info, str_temp);
    aux.goal = stoi(str_temp);
    getline(equipment_info, str_temp);
    aux.tactics_board = stoi(str_temp);
    getline(equipment_info, str_temp);
    aux.medical_kit = stoi(str_temp);
    getline(equipment_info, str_temp);
    aux.water_bottles = stoi(str_temp);


    return aux;
}


/// \brief Reads a player from a .txt file.
/// \param info .txt file containing a Team of Players
/// \return Vector of Players belonging to a team
std::vector<Player *> read_player(std::string info){
    std::ifstream players_info(info);
    std::vector<Player *> players;
    std::vector<std::string> tempVec;
    std::string str_temp;
    while (getline(players_info, str_temp)){
        if (str_temp != "-----") tempVec.push_back(str_temp);
        else{
            Date tempBirth(tempVec[1]);

            PlayerStatistics *stats_virtual;
            if (tempVec[3] == "Goalkeeper")
                stats_virtual = new GoalkeeperStatistics(stoi(tempVec[8]), stoi(tempVec[9]), stoi(tempVec[10]), stoi(tempVec[11]));

            if (tempVec[3] == "Defender")
                stats_virtual = new DefenderStatistics(stoi(tempVec[8]), stoi(tempVec[9]), stoi(tempVec[10]), stoi(tempVec[11]));

            if (tempVec[3] == "Midfielder")
                stats_virtual = new MidfielderStatistics(stoi(tempVec[8]), stoi(tempVec[9]), stoi(tempVec[10]), stoi(tempVec[11]));

            if (tempVec[3] == "Forward")
                stats_virtual = new ForwardStatistics(stoi(tempVec[8]), stoi(tempVec[9]), stoi(tempVec[10]), stoi(tempVec[11]));


            Player *p = new Player(tempVec[0], tempBirth, tempVec[2], tempVec[3], stoi(tempVec[4]), stoi(tempVec[5]), stoi(tempVec[6]), stoi(tempVec[7]), stats_virtual);
            players.push_back(p);
            tempVec.clear();
        }
    }
    return players;
}
/// \brief Reads a Staff Member from a .txt file.
/// \param info .txt file containing Staff Members
/// \return Vector of Staff Members belonging to a team
tabH read_staff(std::string info){
    std::ifstream staff_info(info);
    std::vector<std::string> tempVec;
    std::string str_temp;
    tabH table;

    while (getline(staff_info, str_temp)){
        if (str_temp != "-----") tempVec.push_back(str_temp);
        else{
            Date tempBirth(tempVec[1]);
            Staff *p = new Staff(tempVec[0], tempBirth, stod(tempVec[2]), tempVec[3], stoi(tempVec[4]));
            table.insert(*p);
            tempVec.clear();
        }
    }
    return table;
}
/// \brief Reads a Game from a .txt file.
/// \param info .txt file containing Games
/// \param called_players Vector of Players called for these Games
/// \return Vector of Games stored in the file
std::vector<Game *> read_games(std::string info, std::vector<Player *> called_players){
    std::ifstream game_info(info);
    std::vector<Game *> games;
    std::vector<std::string> tempVec;
    std::string str_temp;
    while (getline(game_info, str_temp)){
        if (str_temp != "-----") tempVec.push_back(str_temp);
        else{
            Date game_day(tempVec[4]);
            Statistics game_stats(stoi(tempVec[5]),stoi(tempVec[6]),stoi(tempVec[7]),stoi(tempVec[8]),stoi(tempVec[9]),stoi(tempVec[10]),stoi(tempVec[11]),stoi(tempVec[12]), stoi(tempVec[13]));
            Game *g = new Game(tempVec[0], tempVec[1], tempVec[2], tempVec[3], game_day, called_players, game_stats);
            games.push_back(g);
            tempVec.clear();
        }
    }
    return games;
}
/// \brief Reads a Competition from a .txt file.
/// \param info .txt file containing the Competition
/// \param t Team Whose Competition is being read
/// \return Vector of Competition stored in the file
std::vector<Competition *> read_competion(std::string info, Team * t){
    std::ifstream competion_info(info);
    std::vector<Competition *> competion;
    std::vector<std::string> tempVec;
    std::string str_temp;
    while (getline(competion_info, str_temp)){

        if (str_temp != "-----") tempVec.push_back(str_temp);
        else{
            //Ler Convocados
            std::vector<Player *> comp_convocado;
            std::ifstream called(tempVec[1]);
            std::map<Player *, int> map_injuries;
            std::vector<std::string> called_vec;
            std::vector<int> days_injured;
            while (getline(called, str_temp)){
                std::stringstream tmp(str_temp);
                getline(tmp, str_temp, '!');
                called_vec.push_back(str_temp);
                getline(tmp, str_temp, '!');
                days_injured.push_back(stoi(str_temp));
            }

            for(size_t i = 0; i < called_vec.size(); i++) {
                comp_convocado.push_back(t->findPlayer(called_vec[i]));
                map_injuries.insert(std::pair<Player *, int>(t->findPlayer(called_vec[i]), days_injured[i]));
            }
            //Ler Jogos
            std::vector<Game *> competion_games = read_games(tempVec[2], comp_convocado);
            //Data de começo e fim
            Date startcomp(tempVec[3]);
            Date endcomp(tempVec[4]);
            Competition *tempComp = new Competition(tempVec[0], map_injuries, competion_games, startcomp, endcomp, stod(tempVec[5]), stoi(tempVec[6]));
            competion.push_back(tempComp);
            tempVec.clear();
        }
    }
    return competion;
}

/// \brief Compares the name of 2 Persons
/// \param p1 Pointer to Person1
/// \param p2 Pointer to Person2
/// \return true if name of Person1 come first alphabetically
bool cmpName(const Person * p1, const Person * p2){
    return p1->getName() < p2->getName();
}

/// \brief Compares the position of 2 Players
/// \param p1 Pointer to Player1
/// \param p2 Pointer to Player2
/// \return true if position of player 1 come first in this order: Goalkeeper > Defender > Midfielder > Forward
bool cmpPosition(const Player * p1, const Player * p2){
    std::string pos[4] = {"Goalkeeper", "Defender", "Midfielder", "Forward"};
    int p1v, p2v;
    for(size_t i = 0; i < 4; i++)
        if (pos[i] == p1->getPosition()) p1v = i;

    for(size_t i = 0; i < 4; i++)
        if (pos[i] == p2->getPosition()) p2v = i;

    return p1v < p2v;
}

/// \brief Compares the value of 2 Players
/// \param p1 Pointer to Player1
/// \param p2 Pointer to Player2
/// \return true if the value of Player1 is higher than Player2
bool cmpValue(const Player * p1, const Player * p2){
    return p1->getValue() > p2->getValue();
}
/// \brief Compares the name of 2 Staff Members
/// \param s1 Staff Member 1
/// \param s2 Staff Member 2
/// \return True if p1's name is first alphabetically, false otherwise
bool cmpStaffName(const Person s1, const Person s2){
    return s1.getName() < s2.getName();
}
/// \brief Compares the function of 2 Staff Members
/// \param s1 Staff Member 1
/// \param s2 Staff Member 2
/// \return True if s1's function is first alphabetically, false otherwise
bool cmpFunction(const Staff s1 , const Staff s2){
    return s1.getFunction() < s2.getFunction();
}
#endif //AEDA_UTILS_H
