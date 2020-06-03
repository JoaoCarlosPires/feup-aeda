#ifndef AEDA_INPUT_UTILS_H
#define AEDA_INPUT_UTILS_H

#include <iostream>
#include <string>

template <class form>
void failInput(form &input)
{
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        std::cin.ignore(1000, '\n');
        std::cout << "Not a valid number. Please reenter: ";
        std::cin >> input;
    }
}

void waitInput(){
    std::string waiting;
    std::cout << "Press any key to continue: " << std::endl;
    getline(std::cin,waiting);

}

void checkPosition(std::string &position){
    while(position != "Goalkeeper" && position != "Defender" &&
          position != "Midfielder" && position != "Forward"){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Not a valid position. Please reenter: " << std::endl;
        std::cout << "Goalkeeper/Defender/Midfielder/Forward" << std::endl;
        std::cin >> position;
    }
}
std::vector<Player*> addCalled(Team* team){
    std::vector<Player*> team_players = team->getPlayers();
    std::vector<Player*> v_players;
    std::vector<int> v_index;
    unsigned int n = team_players.size();
    unsigned int index;

    team->showPlayersTable(); std::cout << std::endl;

    std::cout << "Write the index of the player you wish to add" << std::endl;
    std::cout << "Press any char that is not a number to stop adding " << std::endl;
    std::cout << "Example: Press [a] to exit" << std::endl;
    while(std::cin >> index && !std::cin.eof()) {
        if (index >= n) {
            std::cout << "Index too high!!" << std::endl;
            continue;
        } else if (find(v_index.begin(), v_index.end(), index) != v_index.end()) {
            std::cout << team_players[index]->getName() << " was already added!!" << std::endl;
            continue;
        } else {
            v_players.push_back(team_players[index]);
            v_index.push_back(index);
            std::cout << team_players[index]->getName() << " was successfully added!!" << std::endl;
        }
    }
    std::cin.clear();
    std::cin.ignore(1000,'\n');
    return v_players;
}

#endif //AEDA_INPUT_UTILS_H
