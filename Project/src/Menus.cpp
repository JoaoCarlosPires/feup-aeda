#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>

#include "Menus.h"
#include "Coach.h"
#include "Team.h"
#include "input_utils.h"
#include "Provider.h"

using namespace std;
extern Team *national_team;

//Players Menu

int menu_allPlayers() {
    string toSort;
    national_team->showPlayersTable();
    cout << "To sort write \"sort [ Name | Position | Value ]\" " << endl;
    cout << "Write something else to go back!" << endl;
    getline(cin, toSort);
    if(toSort == "sort Name" || toSort == "sort name"){
        national_team->sortPlayersName();
        return 0;
    }
    if(toSort == "sort Position" || toSort == "sort position"){
        national_team->sortPlayersPosition();
        return 0;
    }
    if(toSort == "sort Value" || toSort == "sort value") {
        national_team->sortPlayersValue();
        return 0;
    }
    return 1;
}

int menu_searchPlayers() {
    char menu;

    cout << "========================================= " << endl;
    cout << "           Search Player Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Search by Name " << endl;
    cout << "2. Search by Position " << endl;
    cout << "0. Return to Player Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu) {
        case '1':
            try {
                string name;
                cout << "Write the name of the player you wish to find: " << endl;
                cout << "0. Return to Player Menu" << endl;
                getline(cin, name);

                vector<Player *> to_print = national_team->findPlayerName(name);
                if (name == "0") return 0;
                for (size_t i = 0; i < to_print.size(); i++) {
                    to_print[i]->info();

                    cout << endl << "Competitions Participated: " << endl;
                    vector<Competition *> v = national_team->getCompetition();
                    for (size_t j = 0; j < v.size(); j++)
                        cout << v[j]->getCompetitionName() << endl;
                    cout << endl << "-----------------------------------" << endl << endl;
                }
            }
            catch (PersonNotFound &er) {
                cout << "Player " << er.getName() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '2':
            try {
                string position;
                cout << "Write the position of the Player(s) you wish to find: " << endl;
                cout << "0. Return to Player Menu" << endl;
                getline(cin, position);
                vector<Player *> to_print = national_team->findPlayerPos(position);
                if (position == "0") return 0;
                cout << endl;
                for (size_t i = 0; i < to_print.size(); i++) {
                    to_print[i]->info();

                    cout << endl << "Competitions Participated: " << endl;
                    vector<Competition *> v = national_team->getCompetition();
                    for (size_t j = 0; j < v.size(); j++)
                        cout << v[j]->getCompetitionName() << endl;
                    cout << endl << "-----------------------------------" << endl;
                }
            }
            catch (PositionNotFound &er) {
                cout << "Players for position " << er.getPosition() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}

int menu_addPlayer(){
    string n, c, pos;
    int wei,hei,val,earn;
    Date d;
    string checker;

    cout << "Write the name of the Player you wish to add: " << endl;
    getline(cin,n);
    cout << "Write " << n << "'s birthday " << endl;
    cin >> d;
    cout << "Write " << n << "'s club " << endl;
    getline(cin,c);
    cout << "Write " << n << "'s position " << endl;
    cin >> pos; checkPosition(pos); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s weight " << endl;
    cin >> wei; failInput(wei); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s height " << endl;
    cin >> hei; failInput(hei); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s value " << endl;
    cin >> val; failInput(val); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s earnings " << endl;
    cin >> earn; failInput(earn);


    PlayerStatistics *stats_virtual;
    if (pos == "Goalkeeper")
        stats_virtual = new GoalkeeperStatistics();

    else if (pos == "Defender")
        stats_virtual = new DefenderStatistics();

    else if (pos == "Midfielder")
        stats_virtual = new MidfielderStatistics();

    else if (pos == "Forward")
        stats_virtual = new ForwardStatistics();

    Player *play = new Player(n,d,c,pos,wei,hei,val,earn, stats_virtual);

    cout << "Do you wish to add " << n << " as a Player?" << endl;
    cout << "1. Add Player " << endl;
    cout << "Any other key cancel adding player " << endl;
    cin.ignore(1000,'\n');
    getline(cin,checker);
    if (checker != "1") {
        cout << "Player was not added!" << endl;
    }
    else{
        national_team->addPlayer(play);
        cout << "Player successfully added!!" << endl;
    }
}

int menu_updatePlayers(){
    unsigned int index;
    vector<Player*> v_players;

    national_team->showPlayersTable();
    cout << "Write the index of the Player you wish to update." << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while (cin >> index && !cin.eof()) {
        v_players = national_team->getPlayers();
        if (index >= v_players.size()) {
            cout << "Invalid index." << endl;
            continue;
        }
        else {
            Player * player = v_players[index];
            string name = player->getName();
            string new_name;
            string club, position;
            Date birthday;
            int weight, height, value;
            double earnings;
            PlayerStatistics *stats = player->getStatistics();
            char n;
            cout << "Which field you want to change in player " << name << endl;
            cout << "Select the correspondent index: " << endl;
            cout << "1. Change name" << endl;
            cout << "2. Change birthday" << endl;
            cout << "3. Change club" << endl;
            cout << "4. Change position" << endl;
            cout << "5. Change weight" << endl;
            cout << "6. Change height" << endl;
            cout << "7. Change value" << endl;
            cout << "8. Change earnings" << endl;
            cout << "9. Change statistics" << endl;

            cin >> n;

            switch(n){
                case '1':
                    cin.ignore(1000, '\n');
                    cout << name << "'s new Name: " << endl;
                    getline(cin, new_name);
                    for (size_t i = 0; i < v_players.size(); i++)
                        if (v_players[i]->getName() == new_name) throw PersonAlreadyExists(new_name);
                    player->setName(new_name);
                    break;
                case '2':
                    cout << name << "'s new birthday " << endl;
                    cin >> birthday;
                    player->setBirthday(birthday);
                    break;
                case '3':
                    cin.ignore(1000, '\n');
                    cout << name << "'s new club " << endl;
                    getline(cin, club);
                    player->setClub(club);
                    break;
                case '4':
                    cout << name << "'s new position " << endl;
                    cin >> position;
                    checkPosition(position);
                    player->setPosition(position);
                    break;
                case '5':
                    cout << name << "'s new weight " << endl;
                    cin >> weight;
                    failInput(weight);
                    player->setWeight(weight);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '6':
                    cout << name << "'s new height " << endl;
                    cin >> height;
                    failInput(height);
                    player->setHeight(height);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '7':
                    cout << name << "'s new value " << endl;
                    cin >> value;
                    failInput(value);
                    player->setValue(value);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '8':
                    cout << name << "'s new earnings " << endl;
                    cin >> earnings;
                    failInput(earnings);
                    player->setEarnings(earnings);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '9':
                    cin >> stats;
                    break;
                default:
                    cout << "Invalid index" << endl;
                    break;
            }
            cout << "Write the index of another player you wish to update." << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped updating Players!" << endl;
    cin.clear();
    cin.ignore(1000, '\n');
    return 1;
}


int menu_removePlayer() {
    unsigned int index;
    vector<Player*> v_players;
    national_team->showPlayersTable();
    cout << "Write the index of the Player you wish to remove " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while(cin >> index && !cin.eof()){
        v_players = national_team->getPlayers();
        if (index >= v_players.size()) {
            cout << "Index too high!!" << endl;
            continue;
        }
        else {
            string name = v_players[index]->getName();
            national_team->removePlayer(v_players[index]);
            national_team->showPlayersTable();
            cout << name << " was successfully removed!!" << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped removing Players!!" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    waitInput();
    return 1;
}

int menu_players()
{
    char menu;


    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)
    cout << "========================================= " << endl;
    cout << "               Player Menu                " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View all players" << endl;
    cout << "2. Search Players " << endl;
    cout << "3. Add Player " << endl;
    cout << "4. Update Player " << endl;
    cout << "5. Remove Player " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu)
    {
        case '1':
            while(!menu_allPlayers());
            return 0;
        case '2':
            while(!menu_searchPlayers());
            return 0;
        case '3':
            try {
                while(!menu_addPlayer());
            }
            catch(PersonAlreadyExists &er) {
                cout << "Player " << er.getName() << " already exists" << endl;
            }
            catch(CantUseThatName &er){
                cout << "Can't use " << er.getName() << " has a name" << endl;
            }
            waitInput();
            return 0;
        case '4':
            try {
                while(!menu_updatePlayers());
                }
            catch (PersonAlreadyExists &er) {
                cout << "Player named " << er.getName() << " already exists!" << endl;
                }
            waitInput();
            return 0;
        case '5':
            while(!menu_removePlayer());
            return 0;
        case '0':
            return 1;
        default:     //Invalid input
            return 0;
    }
}

// Staff

int menu_view_staff(){
    char menu;
    cout << "========================================= " << endl;
    cout << "          View Staff Members Menu         " << endl;
    cout << "========================================= \n" << endl;
    cout << "1. View current staff members" << endl;
    cout << "2. View old staff members" << endl;
    cout << "3. View all staff members" << endl;
    cout << "4. View all staff members sorted by Name" << endl;
    cout << "5. View all staff members sorted by Function" << endl;
    cout << "0. Return to Staff Menu" << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');
    switch(menu) {
        case '1':
            national_team->showStaffTable();
            waitInput();
            return 0;
        case '2':
            national_team->showStaffRemoved();
            waitInput();
            return 0;
        case '3':
            national_team->showStaff();
            waitInput();
            return 0;
        case '4':
            national_team->sortStaffName();
            waitInput();
            return 0;
        case '5':
            national_team->sortStaffFunction();
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;

    }
}

int menu_add_staff(){
    try{
        string n, f, checker;
        double w;
        Date d;

        cout << "Write the name of the Staff Member you wish to add: " << endl;
        getline(cin, n);
        cout << "Write " << n << "'s birthday " << endl;
        cin >> d;
        cout << "Write " << n << "'s wage " << endl;
        cin >> w;
        failInput(w);
        cin.ignore(1000,'\n');
        cout << "Write " << n << "'s function " << endl;
        getline(cin,f);

        Staff *s = new Staff(n, d, w, f, true);
        cout << "Do you wish to add the Staff Member you have created?: " << endl;
        cout << "1. Add Staff Member " << endl;
        cout << "Any other key. Cancel adding Staff Member." << endl;
        getline(cin,checker);
        if (checker != "1"){
            cout << "Staff Member was not added!!" << endl;
        }
        else{
            national_team->addStaff(s);
            cout << n << " was successfully added as a Staff member!!" << endl;
        }
    }
    catch (PersonAlreadyExists & er) {
        cerr << "Staff Member named " << er.getName() << " already exists!!" << endl;
    }
    waitInput();
    return 1;
}

int menu_search_staff(){
    char menu;

    cout << "========================================= " << endl;
    cout << "           Search Staff Menu              " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Search by Name " << endl;
    cout << "2. Search by Staff Function " << endl;
    cout << "0. Return to Staff Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu){
        case '1':
            try{
                string n;
                cout << "Write the name of the Staff Member you wish to find: " << endl;
                getline(cin, n);
                vector<Staff> v_staff = national_team->findStaffName(n);
                cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
                cout << setw(12) << "Function" << " | " << setw(9) << "Salary" << " | " <<setw(6) <<  "Index" << " |" << endl;;
                auto it = v_staff.begin();
                for(int i = 0;it!= v_staff.end();i++,it++){
                    it->infoTable();
                    cout << setw(6) <<  i << " |" << endl;
                }
            }
            catch(PersonNotFound & er){
                cout << "No Staff Member named " << er.getName() << endl;
            }
            waitInput();
            return 0;
        case '2':
            try{
                string f;
                cout << "Write the function of the Staff Member you wish to find: " << endl;
                getline(cin, f);
                vector<Staff> v_staff = national_team->findStaffFunction(f);
                cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
                cout << setw(12) << "Function" << " | " << setw(9) << "Salary" << " | " <<setw(6) <<  "Index" << " |" << endl;;
                auto it = v_staff.begin();
                for(int i = 0;it!= v_staff.end();i++,it++){
                    it->infoTable();
                    cout << setw(6) <<  i << " |" << endl;
                }
            }
            catch(FunctionNotFound & er){
                cout << "No Staff with function" << er.getFunction() << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}

int menu_update_staff(){
    try{
        unsigned int index;
        national_team->showStaff();
        tabH table = national_team->getStaff();

        cout << "Write the index of the Staff Member you wish to update." << endl;
        cout << "Press [a] or other letter to exit." << endl;

        while (cin >> index && !cin.eof()) {

            if (index >= national_team->getStaff().size()) {
                cout << "Invalid index" << endl;
                cin.ignore(1000, '\n');
                continue;
            } else {

                cin.ignore(1000,'\n');
                auto it = national_team->getStaff().begin();
                for(int i = 0; i < index ;i++, it++){}
                string name = it->getName();
                auto staff = new Staff(name,it->getBirthday(),it->getSalary(),it->getFunction(), it->isWorking1());
                national_team->removeStaff(*staff);

                string new_name, changed = "nothing", checker;
                string function;
                Date birthday;
                double salary;
                char n;
                cout << "Which field do you want to change in staff member " << name << "?" << endl;
                cout << "Select the correspondent index: " << endl;
                cout << "1. Change name" << endl;
                cout << "2. Change birthday" << endl;
                cout << "3. Change function" << endl;
                cout << "4. Change salary" << endl;
                cout << "5. Change Working Status" << endl << endl;

                cin >> n;
                cin.ignore(1000, '\n');

                switch(n) {
                    case '1':
                        cout << name << "'s new Name: " << endl;
                        getline(cin, new_name);
                        staff->setName(new_name);
                        changed = "name";
                        break;
                    case '2':
                        cout << name << "'s new birthday " << endl;
                        cin >> birthday;
                        staff->setBirthday(birthday);
                        changed = "birthday";
                        break;
                    case '3':
                        cout << name << "'s new function " << endl;
                        getline(cin,function);
                        staff->setFunction(function);
                        changed = "function";
                        break;
                    case '4':
                        cout << name << "'s new salary " << endl;
                        cin >> salary; failInput(salary); cin.ignore(1000,'\n');
                        staff->setSalary(salary);
                        changed = "salary";
                        break;
                    case '5':
                        if(staff->isWorking1()){
                            cout << name << " is currently working, do you want do dismiss him?" << endl;
                            cout << "Press 1 to dismiss him " << endl;
                            cout << "Press any other key to do keep his working status" << endl;
                            getline(cin,checker);
                            if (checker != "1"){
                                changed = "working status was not changed!!";
                            }
                            else{
                                staff->setIsWorking(false);
                                cout << name << " was dismissed!!" << endl;
                                changed = "working status";
                            }
                        }
                        else{
                            cout << name << " is a former Staff Member, do you want do hire him again?" << endl;
                            cout << "Press 1 to hire him, any other key otherwise" << endl;
                            cout << "Press any other key to do keep his working status" << endl;
                            getline(cin,checker);
                            if (checker != "1"){
                                changed = "working status was not changed!!";
                            }
                            else{
                                staff->setIsWorking(true);
                                cout << name << " was hired again!!" << endl;
                                changed = "working status";
                            }
                        }
                    default:
                        break;
                }
                national_team->addStaff(staff);
                national_team->showStaff();
                if(changed == "working status was not changed!!"){
                    cout << changed << endl;
                }
                else if (changed != "nothing")
                    cout << name << "'s " << changed << " was sucessfully changed." << endl;
                else cout << "Invalid Index!! No changes were made." << endl;
                cout << "Write the index of another Player you wish to update." << endl;
                cout << "Press [a] or other letter to exit." << endl;
            }
        }
        cout << "Stopped updating Staff Members!!" << endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }
    catch(PersonAlreadyExists & er){
        cerr << "Staff Member named " << er.getName() << " already exists!!" << endl;
    }
    waitInput();
    return 1;
}

int menu_remove_staff() {

    unsigned int index;
    vector<Staff*> v_staff;
    vector<int> vec = national_team->showStaffTable();

    cout << "Write the index of the Staff Member you wish to remove " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while(cin >> index && !cin.eof()){
        tabH table = national_team->getStaff();
        cin.ignore(1000,'\n');
        if (index >= table.size() || find(vec.begin(),vec.end(),index) == vec.end()) {
            cout << "Invalid index" << endl;
            continue;
        }
        else {
            auto it = table.begin();
            for(int i = 0; i < index ;i++, it++){}
            string name = it->getName();
            auto temp = new Staff(it->getName(),it->getBirthday(),it->getSalary(),it->getFunction(), false);
            national_team->setStaffNotWorking(*temp);
            vec = national_team->showStaffTable();
            cout << name << " was successfully removed!!" << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped removing Staff Members!!" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    waitInput();
    return 1;
}

int menu_staff() {
    char menu;
    cout << "========================================= " << endl;
    cout << "          Staff Menu           " << endl;
    cout << "========================================= \n" << endl;
    cout << "1. View Staff Members" << endl;
    cout << "2. Search Members" << endl;
    cout << "3. Add Staff Members" << endl;
    cout << "4. Update Staff Members" << endl;
    cout << "5. Remove Staff Members" << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu){
        case '1':
            while(!menu_view_staff());
            return 0;
        case '2':
            while(!menu_search_staff());
            return 0;
        case '3':
            while(!menu_add_staff());
            return 0;
        case '4':
            while(!menu_update_staff());
            return 0;
        case '5':
            while(!menu_remove_staff());
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}
//Competition!

int menu_searchGame() {
    cout << "Write the name of the opponent: " << endl;
    string opponent;
    Date d;
    getline(cin, opponent);
    cout << "Write the Date of Game: " << endl;
    cin >> d;

    vector<Game *> all_games = national_team->getGames();
    for(size_t i = 0; i < all_games.size(); i++) {
        if(all_games[i]->getOpponent() == opponent && all_games[i]->getDate().isEqualTo(d)){
            all_games[i]->info();
            waitInput();
            return 1;
        }
    }
    throw (GameNotFound(opponent, d));
}

int menu_games(){
    char menu;
    vector<Game *> print_it = national_team->getGames(); // Vector to show all games! Can't be initialized in switch case
    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "             Games Menu                   " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all games " << endl;
    cout << "2. Search a Game" << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');


    switch(menu) {
        case '1':
            for(size_t i = 0; i < print_it.size(); i++){
                print_it[i]->info();
                cout << endl;
            }
            waitInput();
            return 0;
        case '2':
            try {
                while(!menu_searchGame());
            }
            catch(GameNotFound & er) {
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game wasn't found" << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:     //Invalid input
            return 0;
    }
}

int menu_payCompetitions(){
    try {
        cout << "National Football Team Competitions" << endl;
        for(int i = 0; i < (national_team->getCompetition()).size(); i++){
            cout << i << ". " << national_team->getCompetition()[i]->getCompetitionName();
            if (national_team->getCompetition()[i]->getPaid())
                cout << " - Paid!" << endl;
            else cout << " - Not paid!" << endl;
        }
        int index;
        cout << "Choose one competition to pay" << endl;
        cout << "Press [a] or other letter to exit." << endl;
        while (cin >> index && !cin.eof()) {
            if(index >= national_team->getCompetition().size()) {
                cout << "Invalid index" << endl;
                continue;
            }
            else {
                national_team->getCompetition()[index]->payPlayers();
                cout << "Competition successfully paid!" << endl;
            }
        }
        cin.clear();
        cin.ignore(1000, '\n');
        return 1;
    }
    catch(AlreadyPaid &er) {
        cout << "The " << er.getName() << " has already been paid to players." << endl;
        return 1;
    }
}

int menu_competitionGames(Competition * comp){
    char menu;
    unsigned int index;
    vector<Game *> v_games = comp->getGames();
    cout << "========================================= " << endl;
    cout << "             Games Menu                   " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all games from this competition" << endl;
    cout << "2. Search a Game" << endl;
    cout << "3. Add a Game" << endl;
    cout << "4. Update a Game " << endl;
    cout << "5. Remove a Game " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu) {
        case '1':
            comp->showGames();
            waitInput();
            return 0;
        case '2':
            try {
                cout << "Write the name of the Game's Opponent: " << endl;
                string opponent;
                Date d;
                getline(cin, opponent);
                cout << "Write the Date of Game: " << endl;
                cin >> d;
                comp->findGame(opponent, d)->info();
            }
            catch(GameNotFound &er) {
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game wasn't found" << endl;
            }
            waitInput();
            return 0;
        case '3':
            try{
                string country,city,stadium,opponent,checker;
                Date d;
                Statistics stats;

                cout << "Write the Game's opponent " << endl;
                getline(cin,opponent);
                cout << "Write the Game's country " << endl;
                getline(cin,country);
                cout << "Write the Game's city " << endl;
                getline(cin,city);
                cout << "Write the Game's stadium " << endl;
                getline(cin,stadium);
                cout << "Write the Game's date " << endl;
                cin >> d;
                Game *game = new Game(opponent,country,city,stadium, d, comp->getCalled(), stats);
                game->info();

                cout << "Do you wish to add this game? " << endl;
                cout << "1. Add Game " << endl;
                cout << "Any other key. Cancel adding Game " << endl;
                getline(cin,checker);
                if (checker != "1"){
                    cout << "Game was not added!" << endl;
                }
                else{

                    comp->addGame(game);
                    cout << "Game successfully added!!" << endl;
                }
            }
            catch(GameAlreadyExists &er){
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Country: " << er.getCountry() << endl;
                cout << "City: " << er.getCity() << endl;
                cout << "Stadium: " << er.getStadium() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game already exists!!" << endl;
            }
            waitInput();
            return 0;
        case '4':
            try{
                for(size_t i = 0; i < v_games.size(); i++){
                    cout << "Game number: " << i << endl;
                    cout << "Opponent " << v_games[i]->getOpponent() << endl;
                    cout << "Date: " << v_games[i]->getDate() << endl << endl;
                }

                cout << "Write the number of the Game you wish to update " << endl;
                cout << "Press [a] or other letter to exit." << endl;

                while(cin >> index && !cin.eof()){

                    if (index >= v_games.size()) {
                        cout << "Index too high!!" << endl;
                        continue;
                    }
                    else {
                        v_games = comp->getGames();
                        Game* game = v_games[index];
                        int goalS, goalsC, shots, ballP, yellowC, redC, injured, freeKicks, cornerKicks;
                        string country,city,stadium,opponent, checker;
                        Date d;
                        Statistics stats;

                        char n;
                        cout << "Which field you want to change in this game? " << endl;
                        cout << "Select the correspondent index: " << endl;
                        cout << "1 -> Change opponent" << endl;
                        cout << "2 -> Change country" << endl;
                        cout << "3 -> Change city" << endl;
                        cout << "4 -> Change stadium" << endl;
                        cout << "5 -> Change date" << endl;
                        cout << "6 -> Change Statistics" << endl;

                        cin >> n;
                        switch(n) {
                            case '1':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's opponent " << endl;
                                getline(cin, opponent);
                                game->setOpponent(opponent);
                                break;
                            case '2':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's country " << endl;
                                getline(cin, country);
                                game->setCountry(country);
                                break;
                            case '3':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's city " << endl;
                                getline(cin, city);
                                game->setCity(city);
                                break;
                            case '4':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's stadium " << endl;
                                getline(cin, stadium);
                                game->setStadium(stadium);
                                break;
                            case '5':
                                cout << "Write the Game's date " << endl;
                                cin >> d;
                                game->setGameDate(d);
                                break;
                            case '6':
                                cout << "Number of goals scored: " << endl;
                                cin >> goalS; failInput(goalS); cin.ignore(1000,'\n');
                                stats.setGoalsScored(goalS);
                                cout << "Number of goals conceded: " <<  endl;
                                cin >> goalsC;failInput(goalsC); cin.ignore(1000,'\n');
                                stats.setGoalsConceded(goalsC);
                                cout << "Number of shots: " <<endl;
                                cin >> shots;failInput(shots); cin.ignore(1000,'\n');
                                stats.setShots(shots);
                                cout << "Percentage of ball possession: "  << endl;
                                cin >> ballP;failInput(ballP); cin.ignore(1000,'\n');
                                stats.setBallPossession(ballP);
                                cout << "Number of yellow cards: "  << endl;
                                cin >> yellowC;failInput(yellowC); cin.ignore(1000,'\n');
                                stats.setYellowCards(yellowC);
                                cout << "Number of red cards: "  << endl;
                                cin >> redC;failInput(redC); cin.ignore(1000,'\n');
                                stats.setRedCards(redC);
                                cout << "Number of Injured players: " << endl;
                                cin >> injured;failInput(injured); cin.ignore(1000,'\n');
                                stats.setInjured(injured);
                                cout << "Number of free kicks: "  << endl;
                                cin >> freeKicks;failInput(freeKicks); cin.ignore(1000,'\n');
                                stats.setFreeKicks(freeKicks);
                                cout << "Number of corner kicks: " << endl;
                                cin >> cornerKicks;failInput(cornerKicks);  cin.ignore(1000,'\n');
                                stats.setCornerKicks(cornerKicks);
                                game->setStats(stats);
                                break;
                            default:
                                cout << "Invalid index" << endl;
                                break;
                        }
                        cout << "Game was successfully updated!!" << endl;
                        cout << "Press [a] or other letter to exit." << endl;
                    }
                }
                cout << "Stopped updating Games!!" << endl;
                cin.clear();
                cin.ignore(1000,'\n');
            }
            catch(GameAlreadyExists &er){
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Country: " << er.getCountry() << endl;
                cout << "City: " << er.getCity() << endl;
                cout << "Stadium: " << er.getStadium() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game already exists!!" << endl;
            }
            waitInput();
            return 0;
        case '5':
            //É preciso meter os jogos numa tabela com Oponentes , Date e indexs
            //comp->showGamesTable();
            for(size_t i = 0; i < v_games.size(); i++){
                cout << "Game number: " << i << endl;
                cout << "Opponent " << v_games[i]->getOpponent() << endl;
                cout << "Date: " << v_games[i]->getDate() << endl << endl;
            }

            cout << "Write the index of the Game you wish to remove " << endl;
            cout << "Press [a] or other letter to exit." << endl;

            while(cin >> index && !cin.eof()){

                if (index >= v_games.size()) {
                    cout << "Index too high!!" << endl;
                    continue;
                }
                else {
                    string opponent = v_games[index]->getOpponent();
                    comp->removeGame(v_games[index]);
                    v_games = comp->getGames();
                    //comp->showGamesTable();
                    for(size_t i = 0; i < v_games.size(); i++){
                        cout << "Game number: " << i << endl;
                        cout << "Opponent " << v_games[i]->getOpponent() << endl;
                        cout << "Date: " << v_games[i]->getDate() << endl << endl;
                    }
                    cout << "Game vs " << opponent << " was successfully removed!!" << endl;
                    cout << "Press [a] or other letter to exit." << endl;
                }
            }
            cout << "Stopped removing Games!!" << endl;
            cin.clear();
            cin.ignore(1000,'\n');
            waitInput();
            return 0;
        case '0':
            return 1;
        default:     //Invalid input
            return 0;
    }

}

int menu_calledCompetition(Competition* comp){
    map<Player *, int> m = comp->getCalledInjured();
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Club" << " | " << setw(10) << "Position" << " | " << setw(6) << "Weight" << " | ";
    cout << setw(8) << "Height" << " | " << setw(7) << "Value" << " | " << setw(9) <<  "Earnings" << " | ";
    cout << setw(12) << "Days Injured" << " |" << endl;

    for(auto it : m) {
        (it.first)->infoTable();
        cout << setw(13) << (it.second) << " |" <<  endl;
    }
    waitInput();
    return 1;
}

int menu_detailedCompetition(Competition * comp){
    char menu;
    cout << "========================================= " << endl;
    cout << "            Competition Menu              " << endl;
    cout << "========================================= " << endl;
    cout << "This menu is about the Competition:" << endl;
    cout << comp->getCompetitionName() << endl << endl;
    cout << "1. Competition Games" << endl;
    cout << "2. View called Players" << endl;
    cout << "3. Money spent in this competition (Excluding Staff Members Salary)" << endl;
    cout << "0. Return to the previous Competition Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');
    switch(menu){
        case '1':
            while(!menu_competitionGames(comp));
            return 0;
        case '2':
            while(!menu_calledCompetition(comp));
            return 0;
        case '3':
            cout << "Number of days of this competition: " << comp->getStartDate().daysUntil(comp->getEndDate()) << endl;
            cout << "Money spent in Accommodation:  " << comp->getMoneyAccommodation() << endl;
            cout << "Paid to players as Insurances: " << comp->getMoneyInsurance() << endl;
            cout << endl;
            waitInput();
            return 0;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            return 0;
    }
}

int menu_chooseCompetition() {
    vector<Competition*> comp = national_team->getCompetition();
    unsigned int index;
    cout << "Write the number of the Competition you wish to view" << endl;
    cout << "Press [a] or other letter to exit." << endl;

    for(size_t i = 0; i < comp.size(); i++)
        cout << i << ". " <<comp[i]->getCompetitionName() << endl;

    while(cin >> index && !cin.eof()){
        if(index >= comp.size())
            cout << "Invalid index" << endl;
        else{
            while(!menu_detailedCompetition(comp[index]));
            return 1;
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return 1;
}

int menu_creatCompetition() {
    int index;
    string name, players, checker;
    Date start, end;
    map<Player*, int> m_players;
    vector<Player*> team_players = national_team->getPlayers();
    vector<int> v_index;
    double acc;
    size_t n = team_players.size();
    cout << "Write the Competition's name: " << endl;
    getline(cin,name);
    cout << "Write " << name << "'s beginning date: " << endl;
    cin >> start;
    cout << "Write " << name << "'s ending date: " << endl;
    cin >> end;

    while (start.isAfter(end)){
        cout << "Date of end is before of date of start! ";
        cin >> end;
    }
    cout << endl;
    cout << "Write the money for accommodation: " << endl;
    cin >> acc; failInput(acc);
    cin.ignore(1000,'\n');
    national_team->showPlayersTable();
    cout << endl;

    cout << "Write the index of the player you wish to add" << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while(cin >> index && !cin.eof()) {
        if (index >= n) {
            cout << "Index too high!!" << endl;
            continue;
        } else if (find(v_index.begin(), v_index.end(), index) != v_index.end()) {
            cout << team_players[index]->getName() << " was already added" << endl;
            continue;
        } else {
            m_players.insert(pair<Player *, int>(team_players[index], 0));
            v_index.push_back(index);
            cout << team_players[index]->getName() << " was successfully added" << endl;
        }
    }
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "Add games in Competitions Menu." << endl << endl;
    cout << "Are you sure you want to add this competition?" << endl;
    cout << "1. Add the competition: " << name << endl;
    cout << "   Any other key to go back without adding the competition." << endl;

    getline(cin,checker);
    if(checker != "1")
        cout << name << " was not added" << endl;
    else {
        cout << "Competition " <<name << " was added" << endl;
        Competition * comp = new Competition(name, m_players, start, end, acc);
        national_team->addCompetition(comp);
    }
    return 1;
}

int menu_updateCompetition() {
    vector<Competition*> comp = national_team->getCompetition();
    int index;
    cout << "Write the number of the Competition you wish to update " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    for (size_t i = 0; i < comp.size(); i++){
        cout << "Competition number: " << i << " " << comp[i]->getCompetitionName() << endl;
    }

    while(cin >> index && !cin.eof()){
        if (index >= comp.size()) {
            cout << "Invalid index" << endl;
            continue;
        }
        else {
            Competition * co = comp[index];
            if(co->getPaid()) {
                cout << "This competition has already been paid, so it cannot be changed." << endl;
                cin.ignore(1000, '\n');
                waitInput();
                return 1;
            }
            string players, checker;
            Date start,end;
            map<Player*, int> m_players;
            vector<Player*> team_players = national_team->getPlayers();
            vector<int> v_index;
            size_t num = team_players.size();
            string name = co->getCompetitionName();
            string new_name;
            int money;
            cin.ignore(1000,'\n');
            int n, nt;
            int n_switches;
            cout << "Which field you want to change in this competition: " << name << endl;
            cout << "Select the correspondent index: " << endl;
            cout << "1. Change competition name" << endl;
            cout << "2. Change date" << endl;
            cout << "3. Change money paid for accommodation" << endl;
            cout << "4. Change called players" << endl;
            cout << "5. Update player injuries" << endl;
            cout << "Press [a] or other letter to exit." << endl;

            while(cin >> n_switches && !cin.eof()){
                map<Player *, int> m_player = co->getCalledInjured();
                vector<Player *> v_player = co->getCalled();
                if(n_switches >= 6){
                    cout << "Invalid index, please try again!!" << endl;
                }
                else{
                    string message;
                    switch(n_switches) {
                        case 1:
                            cout << "Write the Competition's name: " << endl;
                            cin.ignore(1000, '\n');
                            getline(cin, new_name);
                            co->setName(new_name);
                            message = "Name successfully changed!!";
                            break;
                        case 2:
                            cout << "Write " << name << "'s beginning date: " << endl;
                            cin >> start;
                            cout << "Write " << name << "'s ending date: " << endl;
                            cin >> end;
                            while (start.isAfter(end)){
                                cout << "Date of end is before of date of start! ";
                                cin >> end;
                            }
                            co->setStart(start);
                            co->setEnd(end);
                            message = "Dates successfully changed";
                            break;
                        case 3:
                            cout << "Write " << name << "'s money for accommodation: " << endl;
                            cin >> money; failInput(money); cin.ignore(1000,'\n');
                            co->setMoneyAccommodation(money);
                            message = "Money accommodation successfully changed";
                            break;
                        case 4:
                            national_team->showPlayersTable(); cout << endl;
                            cout << "Select the index of ALL players this competition should call" << endl;
                            cout << "Press [a] or other letter to exit." << endl;
                            n = team_players.size();
                            while(cin >> index && !cin.eof()) {
                                if (index >= n) {
                                    cout << "Invalid index" << endl;
                                    continue;
                                } else if (find(v_index.begin(), v_index.end(), index) != v_index.end()) {
                                    cout << team_players[index]->getName() << " was already added!!" << endl;
                                    continue;
                                } else {
                                    m_players.insert(pair<Player*, int>(team_players[index],0));
                                    v_index.push_back(index);
                                    cout << team_players[index]->getName() << " was successfully added!!" << endl;
                                }
                            }

                            co->setPlayerInjuries(m_players);
                            cin.clear();
                            cin.ignore(1000,'\n');
                            message = "Called Players successfully changed";
                            break;
                        case 5:
                            cout << "Select the index of player you want to update the injured time" << endl;
                            cout << "Press [a] or other letter to exit." << endl;

                            for (size_t i  = 0; i < v_player.size(); i++) {
                                cout << "Index " << i << ": " << v_player[i]->getName() << endl;
                            }

                            n = co->getCalled().size();
                            while(cin >> index && !cin.eof()) {
                                if (index >= n) {
                                    cout << "Invalid index" << endl;
                                    continue;
                                } else {
                                    cout << "Number of days " << v_player[index]->getName() << " was injured in this competition: " << endl;
                                    cin >> nt; failInput(nt);
                                    while(nt > co->getStartDate().daysUntil(co->getEndDate()) || nt < 0) {
                                        cout << "This competition only have " << co->getStartDate().daysUntil(co->getEndDate()) << " days" << endl;
                                        cin >> nt;
                                        failInput(nt);
                                    }
                                    co->updatePlayerInjuries(v_player[index], nt);
                                    cout << "Select the index of player you want to update the injured time" << endl;
                                    cout << "Press [a] or other letter to exit." << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                }
                            }
                            message = "Injured time of player updated!";
                            break;
                        default:
                            break;
                    }
                    cout << message << endl << endl;
                    cout << "Which field you want to change in this competition " << name << endl;
                    cout << "Select the correspondent index: " << endl;
                    cout << "1. Change competition name" << endl;
                    cout << "2. Change date" << endl;
                    cout << "3. Change money paid for accommodation" << endl;
                    cout << "4. Change called players" << endl;
                    cout << "5. Update player injuries" << endl;

                    cout << "Press [a] or other letter to exit." << endl;
                }
            }
        }
    }
    cout << "Stopped updating Competitions" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    return 1;
}

int menu_removeCompetition() {
    int index;
    string name;
    vector<Competition*> comp = national_team->getCompetition();
    cout << "Write the index of the Competition you wish to remove " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    for (size_t i = 0; i < comp.size(); i++){
        cout << "Competition number: " << i << " " << comp[i]->getCompetitionName() << endl;
    }

    while(cin >> index && !cin.eof()){
        if (index >= comp.size()) {
            cout << "Index too high!!" << endl;
            continue;
        }
        else {
            name = comp[index]->getCompetitionName();
            national_team->removeCompetition(comp[index]);
            comp = national_team->getCompetition();
            for (size_t i = 0; i < comp.size(); i++){
                cout << "Competition number: " << i << " " << comp[i]->getCompetitionName() << endl;
            }
            cout << name << " was successfully removed!!" << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped removing Competitions!" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    waitInput();
    return 1;
}

int menu_tournaments()
{
    char menu;
    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "            Competitions Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all competitions" << endl;
    cout << "2. Information about all games" << endl;
    cout << "3. Pay competitions fees" << endl;
    cout << "4. Detailed information about one competition" << endl;
    cout << "5. Create a new Competition " << endl;
    cout << "6. Update a Competition " << endl;
    cout << "7. Remove a Competition " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu)
    {
        case '1':    //Show all competitions
            for(int i = 0; i < (national_team->getCompetition()).size(); i++)
                cout << (*(national_team->getCompetition()[i])) << endl;
            waitInput();
            return 0;
        case '2':
            while(!menu_games());
            return 0;
        case '3':
            while(!menu_payCompetitions());
            return 0;
        case '4':
            while(!menu_chooseCompetition());
            return 0;
        case '5':
            try{
                while(!menu_creatCompetition());
            }
            catch(CompetitionAlreadyExists &er){
                cout << "Competition " << er.getName() << " already exists" << endl;
            }
            return 0;
        case '6':
            try{
                while(!menu_updateCompetition());
            }
            catch(CompetitionAlreadyExists &er){
                cout << "Competition " << er.getName() << " already exists" << endl;
            }
            return 0;
        case '7':
            while(!menu_removeCompetition());
            return 0;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            return 0;
    }
}

int menu_info()
{
    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "            Team Information             " << endl;
    cout << "========================================= \n" << endl;

    cout << "Team Name: " << national_team->getTeamName() << endl;
    cout << "Number of players: " << national_team->getPlayers().size() << endl;
    cout << "Number of working staff members: " << national_team->workingStaff() << endl;
    cout << "Number of Competitions: " << national_team->getCompetition().size() << endl;
    cout << "Competitions not paid: " << national_team->missingPay() << endl;
    cout << "Money spent with accommodation: " << national_team->getMoneyAccommodation() << endl;
    cout << "Money spent with players in competitions: " << national_team->getMoneyPlayers() << endl;
    cout << "Money spent with staff per month: " << national_team->getMoneyStaff() << endl << endl;
    cout << "Equipment:" << endl;
    cout << "Football Kits: " << national_team->getEquipment()->football_kit << endl;
    cout << "Balls: " << national_team->getEquipment()->balls << endl;
    cout << "Football Boots: " << national_team->getEquipment()->football_boots << endl;
    cout << "Cones: " << national_team->getEquipment()->cones << endl;
    cout << "Goal: " << national_team->getEquipment()->goal << endl;
    cout << "Tactics Board: " << national_team->getEquipment()->tactics_board << endl;
    cout << "Medical Kit: " << national_team->getEquipment()->medical_kit << endl;
    cout << "Water Bottles: " << national_team->getEquipment()->water_bottles << endl;

    waitInput();
    return 1;
}

int menu_credits() {
    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)
    cout << "This app was created by:" << endl << endl;
    cout << "Diogo Samuel Fernandes" << endl;
    cout << "Hugo Guimaraes" << endl;
    cout << "Joao Carlos Pires" << endl << endl;

    waitInput();
    return 1;
}

int menu_show_coach() {
    char menu;
    cout << "========================================= " << endl;
    cout << "           Show Coaches Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all coaches " << endl;
    cout << "2. Show coaches with less or equal to a certain number of titles " << endl;
    cout << "3. Show coaches with more than a certain number of titles " << endl;
    cout << "0. Return to Coaches Menu " << endl << endl;
    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    CoachTree *c = national_team->getCoachs();
    int num;
    switch(menu) {
        case '1':
            c->showCoachInfo();
            waitInput();
            return 0;
        case '2':
            try{
                cout << "Number of titles: ";
                cin >> num; failInput(num); cin.ignore(1000,'\n');
                c->showLessTitles(num);
            }
            catch(InvalidNumberTitles & er){
                cout << "No coaches were found with, at most, " << er.getNumTitles() << " titles!" << endl;
            }
            waitInput();
            return 0;
        case '3':
            try{
                cout << "Number of titles: ";
                cin >> num; failInput(num); cin.ignore(1000,'\n');
                c->showMoreTitles(num);
            }
            catch(InvalidNumberTitles & er){
                cout << "No coaches were found with more than " << er.getNumTitles() << " titles!" << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}

int menu_search_coach(){
    char menu;
    cout << "========================================= " << endl;
    cout << "           Search Coaches Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Search by Name " << endl;
    cout << "2. Search by number of Titles " << endl;
    cout << "0. Return to Coaches Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    int num;
    string name_coach;
    vector<Coach> to_print;
    CoachTree *c = national_team->getCoachs();
    switch(menu) {
        case '1':
            try {
                cout << "Coach name:" << endl;
                getline(cin, name_coach);
                to_print = c->searchName(name_coach);
                for (auto &i : to_print) {
                    i.show();
                    cout << "-----------------------------------" << endl;
                }
            }
            catch (PersonNotFound &er) {
                cerr << "Coach named " << er.getName() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '2':
            try {
                cout << "Coach number of Titles:" << endl;
                cin >> num; failInput(num); cin.ignore(1000,'\n');
                to_print = c->searchTitle(num);
                for (auto &i : to_print) {
                    i.show();
                    cout << endl << "-----------------------------------" << endl;
                }
            }
            catch (InvalidNumberTitles &er) {
                cerr << "There are no coaches with " << er.getNumTitles() << " titles" << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}

int menu_add_coach() {
    CoachTree *c = national_team->getCoachs();
    char confirmation;
    string name_coach, name_team , checker;
    int num;
    Coach a;
    Date start, end;
    a.setCurrentCoach(false);
    cout << "Coach name:" << endl;
    getline(cin, name_coach);
    a.setName(name_coach);

    cout << "Titles:" << endl;
    cin >> num;
    failInput(num);
    cin.ignore(1000, '\n');
    a.setTitles(num);

    cout << "This trainer already trained a team? [y/n]" << endl;
    cin >> confirmation; cin.ignore(1000, '\n');
    while (confirmation == 'y') {
        cout << "Write team name: " << endl;
        getline(cin,name_team);
        //Loop
        cout << "Write beginning date: " << endl;
        cin >> start;
        cout << "Write ending date: " << endl;
        cin >> end;
        while (start.isAfter(end)){
            cout << "Date of end is before of date of start! ";
            cin >> end;
        }
        a.addTrainedTeam(name_team, start, end);
        cout << "Add another trainned team? [y/n] " << endl;
        cin >> confirmation; cin.ignore(1000, '\n');
    }
    cout << "Stopped adding trained teams!" << endl;
    cout << "Do you wish to add the Coach you have created?: " << endl;
    cout << "1. Add " << name_coach << endl;
    cout << "Any other key. Cancel adding Coach." << endl;
    getline(cin,checker);
    if (checker != "1"){
        cout << name_coach << " was not added!!" << endl;
    }
    else{
        c->addCoach(a);
        cout << name_coach << " was successfully added as a Coach!!" << endl;
    }
    waitInput();
    return 1;
}

int menu_update_coach() {
    int num;
    string name_coach;
    CoachTree *c = national_team->getCoachs();

    cout << "Coach name:" << endl;
    getline(cin, name_coach);
    vector<Coach> to_print;

    try {
        to_print = c->searchName(name_coach);
        for (size_t i = 0; i < to_print.size(); i++) {
            cout << "Index " << i << endl;
            to_print[i].show();
            cout << "-----------------------------------" << endl << endl;
        }

        cout << "Choose index: " << endl;
        cin >> num;
        failInput(num);
        cin.ignore(1000, '\n');
        while (num >= to_print.size()) {
            cout << "Invalid index. Choose index: " << endl;
            cin >> num;
            failInput(num);
            cin.ignore(1000, '\n');
        }
    }
    catch (PersonNotFound & er) {
        cerr << "No coach named " << er.getName() << " was found!!" << endl;
        waitInput();
        return 1;
    }

    Coach coachChange = to_print[num];

    char menu, menu2;
    cout << "========================================= " << endl;
    cout << "           Update Coach Menu             " << endl;
    cout << "========================================= \n" << endl;

        cout << "Choose the field you want to change: " << endl;
        cout << "1. Change coach name" << endl;
        cout << "2. Change coach birthday" << endl;
        cout << "3. Change number of titles" << endl;
        cout << "4. Change teams trained" << endl;
        cout << "5. Add teams trained" << endl;
        cout << "0. Back to main menu" << endl;

        cin >> menu;
        cin.ignore(1000, '\n');

        int n, index;
        char confirmation;

    Date birth, start, end;
    vector<std::tuple<string, Date, Date>> trainedT = coachChange.getTrainedTeams();
    auto it = trainedT.begin();
    string name = coachChange.getName();
    string name_team;

    switch(menu) {
        case '1':
            cout << "Coach name:" << endl;
            getline(cin, name_coach);
            c->updateCoachName(coachChange, name_coach);
            cout << name << "'s name was successfully changed!!" << endl;
            break;
        case '2':
            cout << "Write coach birthday: " << endl;
            cin >> birth;
            c->removeCoach(coachChange);
            coachChange.setBirthday(birth);
            c->addCoach(coachChange);
            cout << name << "'s Birthday was successfully changed!!" << endl;
            break;
        case '3':
            cout << "New number of titles:" << endl;
            cin >> n;
            failInput(n);
            cin.ignore(1000, '\n');
            c->updateCoachTitle(coachChange, n);
            cout << name << "'s number of titles were successfully changed!!" << endl;
            break;
        case '4':
            if(trainedT.empty()) {
                cout << "No teams to remove/change!" << endl;
                waitInput();
                return 1;
            }
            cout << "Do you wish remove a team from trained teams? [y/n]" << endl;
            cin >> confirmation;
            cin.ignore(1000, '\n');
            while (confirmation == 'y') {
                index = 0;
                for (auto &i : trainedT) {
                    cout << "Index: " << index << endl;
                    cout << " TeamName: " << get<0>(i) << endl;
                    cout << " Start: " << get<1>(i) << endl;
                    cout << " End: " << get<2>(i) << endl << endl;
                    index++;
                }

                cout << "Choose index: " << endl;
                cin >> n;
                failInput(n);
                cin.ignore(1000, '\n');
                while (n >= trainedT.size()) {
                    cout << "Invalid index. Choose index: " << endl;
                    cin >> n;
                    failInput(n);
                    cin.ignore(1000, '\n');
                }

                it = trainedT.begin();
                for(int i = 0; i < n; i++)
                    it++;

                trainedT.erase(it);
                c->updateCoachTeams(coachChange, trainedT);
                if (!trainedT.empty()) {
                    cout << "Remove another trained team? [y/n] " << endl;
                    cin >> confirmation;
                    cin.ignore(1000, '\n');
                } else{
                    confirmation = 'n';
                    cout << "No more teams to remove/change!" << endl;
                    waitInput();
                    return 1;
                }
            }
            //Alterar informação sobre alguma equipa que já treinou anteriormente
            cout << "Do you wish to change a team from trained teams? [y/n]" << endl;
            cin >> confirmation;
            cin.ignore(1000, '\n');

            while (confirmation == 'y') {
                index = 0;
                for (auto &i : trainedT) {
                    cout << "Index: " << index << endl;
                    cout << " TeamName: " << get<0>(i) << endl;
                    cout << " Start: " << get<1>(i) << endl;
                    cout << " End: " << get<2>(i) << endl << endl;
                    index++;
                }

                cout << "Choose index: " << endl;
                cin >> n;
                failInput(n);
                cin.ignore(1000, '\n');
                while (n >= trainedT.size()) {
                    cout << "Invalid index. Choose index: " << endl;
                    cin >> n;
                    failInput(n);
                    cin.ignore(1000, '\n');
                }

                it = trainedT.begin();
                for(int i = 0; i < n; i++)
                    it++;


                cout << "What you want to to change? " << index << endl;
                cout << "1. Team Name " << endl;
                cout << "2. Date " << endl;
                cout << "Any key to not change" << endl;
                cin >> menu2;
                cin.ignore(1000, '\n');
                switch (menu2) {
                    case '1':
                        cout << "Team name:" << endl;
                        getline(cin, name_coach);
                        get<0>(*it) = name_coach;
                        break;
                    case '2':
                        cout << "Write start date" << endl;
                        cin >> start;
                        cout << "Write end date" << endl;
                        cin >> end;
                        while (start.isAfter(end)) {
                            cout << "Date of end is before of date of start! ";
                            cin >> end;
                        }
                        get<1>(*it) = start;
                        get<2>(*it) = end;
                        break;
                    default:
                        break;
                }

                c->updateCoachTeams(coachChange, trainedT);
                if (!trainedT.empty()) {
                    cout << "Change another trained team? [y/n] " << endl;
                    cin >> confirmation;
                    cin.ignore(1000, '\n');
                } else {
                    confirmation = 'n';
                    cout << "No more teams to remove/change!" << endl;
                    waitInput();
                    return 1;
                }
            }
            cout << name << "'s Trained teams were successfully changed!!" << endl;
            break;
        case '5':
            do {
                c->removeCoach(coachChange);
                cout << "Write team name: " << endl;
                getline(cin, name_team);
                cout << "Write beginning date: " << endl;
                cin >> start;
                cout << "Write ending date: " << endl;
                cin >> end;
                while (start.isAfter(end)){
                    cout << "Date of end is before of date of start! ";
                    cin >> end;
                }
                coachChange.addTrainedTeam(name_team, start, end);
                c->addCoach(coachChange);
                cout << "Add another trained team? [y/n] " << endl;
                cin >> confirmation; cin.ignore(1000, '\n');
            }while (confirmation == 'y');
            break;
        default:
            return 1;
    }
    waitInput();
    return 1;
}


int menu_remove_coach(){
    char menu;
    cout << "========================================= " << endl;
    cout << "           Search Remove Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Remove by Name " << endl;
    cout << "2. Remove by number of Titles " << endl;
    cout << "0. Return to Coaches Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    string name_coach;
    int num;
    Coach a;
    CoachTree *coachTree = national_team->getCoachs();
    vector<Coach> to_print;

    switch(menu) {
        case '1':
            try {
                cout << "Coach name:" << endl;
                getline(cin, name_coach);
                to_print = coachTree->searchName(name_coach);
                for (size_t i = 0; i < to_print.size(); i++) {
                    cout << "Index " << i << endl;
                    to_print[i].show();
                    cout << "-----------------------------------" << endl << endl;
                }

                cout << "Choose index: " << endl;
                cin >> num;
                failInput(num);
                cin.ignore(1000,'\n');
                while (num >= to_print.size()) {
                    cout << "Invalid index. Choose index: " << endl;
                    cin >> num; failInput(num); cin.ignore(1000,'\n');
                }
                cout << to_print[num].getName() << " was successfully removed!!" << endl;
                coachTree->removeCoach(to_print[num]);
            }
            catch (PersonNotFound &er) {
                cout << "Coach " << er.getName() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '2':
            try {
                cout << "Coach number of Titles:" << endl;
                cin >> num;
                failInput(num);
                cin.ignore(1000,'\n');

                to_print = coachTree->searchTitle(num);
                for (size_t i = 0; i < to_print.size(); i++) {
                    cout << "Index " << i << endl;
                    to_print[i].show();
                    cout << "-----------------------------------" << endl << endl;
                }

                cout << "Choose index: " << endl;
                cin >> num; failInput(num); cin.ignore(1000,'\n');
                while (num >= to_print.size()) {
                    cout << "Invalid index. Choose index: " << endl;
                    cin >> num; failInput(num); cin.ignore(1000,'\n');
                }

                coachTree->removeCoach(to_print[num]);
            }
            catch (InvalidNumberTitles &er) {
                cout << "There has no coaches with " << er.getNumTitles() << " titles" << endl;
            }
            waitInput();
            return 0;
        case '0':

            return 1;
        default:
            return 0;
    }
}

int menu_select_coach(){
    char menu;
    cout << "========================================= " << endl;
    cout << "           Select Coach Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View actual coach" << endl;
    cout << "2. Select a coach" << endl;
    cout << "3. Dismiss actual coach" << endl;
    cout << "0. Return to Coaches Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    int num;
    CoachTree *coachTree = national_team->getCoachs();
    Coach current;
    Date start, end;
    string name_coach;
    vector<Coach> to_print;
    switch(menu) {
        case '1':
            try {
                current = coachTree->searchCurrentCoach();
                current.show();
            }
            catch(NoCoach &er) {
                er.show();
                cout << "Suggested Coach for this Team: " << endl;
                try {
                    coachTree->suggestedCoach(national_team->getTeamName()).show();
                }
                catch (NoSuggestedCoach &er) {
                    er.show();
                }
            }
            waitInput();
            return 0;
        case '2':
            try {
                current = coachTree->searchCurrentCoach();
                coachTree->removeCoach(current);
                current.setCurrentCoach(false);
                coachTree->addCoach(current);
                cout << "The actual coach was fired! " << endl;
            }
            catch(NoCoach &er) {
                cout << "Select a new Trainer: " << endl;
            }

            try {
                cout << "Coach name:" << endl;
                getline(cin, name_coach);
                to_print = coachTree->searchName(name_coach);
                for (size_t i = 0; i < to_print.size(); i++) {
                    cout << "Index " << i << endl;
                    to_print[i].show();
                    cout << "-----------------------------------" << endl << endl;
                }

                cout << "Choose index: " << endl;
                cin >> num; failInput(num); cin.ignore(1000,'\n');
                if (num >= to_print.size()) {
                    cout << "Invalid index. Choose index: " << endl;
                    cin >> num; failInput(num); cin.ignore(1000,'\n');
                }

                to_print[num].setCurrentCoach(true);
                cout << "Start working in: " << endl;
                cin >> start;
                cout << "End working in: " << endl;
                cin >> end;
                while (start.isAfter(end)){
                    cout << "Date of end is before of date of start! ";
                    cin >> end;
                }

                to_print[num].addTrainedTeam(national_team->getTeamName(), start, end);

                coachTree->removeCoach(to_print[num]);
                coachTree->addCoach(to_print[num]);
                cout << "Coach was successfully changed!!";
                cout << to_print[num].getName() << " is now the new Coach!!" << endl;
            }
            catch (PersonNotFound &er) {
                cout << "Coach " << er.getName() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '3':
            try {
                current = coachTree->searchCurrentCoach();
                coachTree->removeCoach(current);
                current.setCurrentCoach(false);
                coachTree->addCoach(current);
                cout << "Coach was successfully fired!" << endl;
            }
            catch(NoCoach &er) {
                er.show();
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}

int menu_coach() {
    char menu;

    cout << "========================================= " << endl;
    cout << "               Coaches Menu                 " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View all Coaches " << endl;
    cout << "2. Hire a Coach for team " << endl;
    cout << "3. Search Coaches " << endl;
    cout << "4. Add Coaches " << endl;
    cout << "5. Update Coaches " << endl;
    cout << "6. Remove Coaches " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu)
    {
        case '1':
            while(!menu_show_coach());
            return 0;
        case '2':
            while(!menu_select_coach());
            return 0;
        case '3':
            while(!menu_search_coach());
            return 0;
        case '4':
            while(!menu_add_coach());
            return 0;
        case '5':
            while(!menu_update_coach());
            return 0;
        case '6':
            while(!menu_remove_coach());
            return 0;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            return 0;
    }
}


// Provider's Menus

int menu_buy_provider() {

    ProviderPriorityQueue *p = national_team->getProviders();
    Equipment *equip_aux = national_team->getEquipment();

    /* Show the results of the search */
    vector<Provider> to_print;

    int menu = -1;
    int num_item = -1;

    cout << "========================================= " << endl;
    cout << "           Equipment Buy Menu             " << endl;
    cout << "========================================= \n"
         << endl;
    cout << "Please select which item do you want to buy." << endl << endl;
    cout << "1. Football Kit" << endl;
    cout << "2. Balls" << endl;
    cout << "3. Football Boots" << endl;
    cout << "4. Cones" << endl;
    cout << "5. Goal" << endl;
    cout << "6. Tactics Board" << endl;
    cout << "7. Medical Kit" << endl;
    cout << "8. Water Bottles" << endl;
    cout << "0. Return to Main Menu " << endl
         << endl;

    while (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5 && menu != 6 && menu != 7 && menu != 8 && menu != 0)
    {
        cin.clear();
        cin >> menu; failInput(menu); cin.ignore(1000, '\n');
    }

    if (menu == 0) {return 1;}
    to_print = p->searchEquipment(menu);

    if (!to_print.empty()) {
        to_print[0].showItem(menu);
        cout << endl
             << "-----------------------------------" << endl
             << endl;
        while (num_item <= 0) {
            cout << "How many items do you want to buy? (Please write a number equal or higher than 1)" << endl;
            cin >> num_item; failInput(num_item); cin.ignore(1000,'\n');
        }
        int units = 0;
        switch (menu)
        {
            case 1:
                units = to_print[0].getEquipment().football_kit;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Football Kit was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->football_kit += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Football Kit." << endl;
                }
                break;
            case 2:
                units = to_print[0].getEquipment().balls;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Balls was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->balls += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Balls." << endl;
                }
                break;
            case 3:
                units = to_print[0].getEquipment().football_boots;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Football Boots was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->football_boots += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Football Boots." << endl;
                }
                break;
            case 4:
                units = to_print[0].getEquipment().cones;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Cones was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->cones += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Cones." << endl;
                }
                break;
            case 5:
                units = to_print[0].getEquipment().goal;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Goal was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->goal += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Goal." << endl;
                }
                break;
            case 6:
                units = to_print[0].getEquipment().tactics_board;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Tactics Board was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->tactics_board += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Tactics Board." << endl;
                }
                break;
            case 7:
                units = to_print[0].getEquipment().medical_kit;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Medical Kit was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->medical_kit += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Medical Kit." << endl;
                }
                break;
            case 8:
                units = to_print[0].getEquipment().water_bottles;
                if (num_item <= units) {
                    p->updateEquipmentItem(to_print[0], menu, units-num_item);
                    cout << "The item Water Bottles was bought successfully. Number of units selled: " << num_item << endl;
                    equip_aux->water_bottles += num_item;
                } else {
                    cout << "The Provider doesn't have enough items of type Water Bottles." << endl;
                }
                break;
            default:
                break;
        }
        char answer;
        double new_rep = 5.1;
        cout << "Would you like to set a new Reputation of Provider " << to_print[0].getName() << "? [y/n]" << endl;
        cin >> answer;
        cin.ignore(1000, '\n');
        switch (answer) {
            case 'y':
                while (new_rep < 0.0 || new_rep > 5.0) {
                    cout << "(Please write a number between 0.0 and 5.0)" << endl;
                    cin >> new_rep; failInput(new_rep); cin.ignore(1000, '\n');
                }
                p->updateReputation(to_print[0], new_rep);
                cout << "Thanks for your feedback!" << endl;
                break;
            case 'N':
                break;
            default:
                break;
        }
    } else {
        cout << "There's no Provider with that item." << endl;
    }

    return 0;
}

int menu_search_provider()
{
    char menu = '4';

    cout << "========================================= " << endl;
    cout << "         Provider's Search Menu           " << endl;
    cout << "========================================= \n"
         << endl;

    cout << "1. Search By Provider's Name" << endl;
    cout << "2. Search By Provider's Reputation" << endl;
    cout << "3. Search By Equipment Item" << endl;
    cout << "0. Return to Previous Menu" << endl
         << endl;

    while (menu != '1' && menu != '2' && menu != '3' && menu != '0')
    {
        cin.clear();
        cin >> menu;
        cin.ignore(1000, '\n');
    }
    string name_provider;
    double rep = 5.1;
    int equip = 0;
    ProviderPriorityQueue *p = national_team->getProviders();

    /* Show the results of the search */
    vector<Provider> to_print;

    switch (menu)
    {
        case '1':
            // Search By Name
            cout << "Provider name:" << endl;
            getline(cin, name_provider);
            to_print = p->searchName(name_provider);
            for (auto &i : to_print)
            {
                i.showInfo();
                cout << "-----------------------------------" << endl
                     << endl;
            }
            break;
        case '2':
            // Search By Reputation
            while (rep < 0.0 || rep > 5.0) {
                cout << "Provider's Reputation Minimum: (Please write a number between 0.0 and 5.0)" << endl;
                cin >> rep;
                cin.ignore(1000, '\n');
            }
            to_print = p->searchReputation(rep);
            for (auto &i : to_print)
            {
                i.showInfo();
                cout << endl
                     << "-----------------------------------" << endl
                     << endl;
            }
            break;
        case '3':
            // Search All With Item in Equipment
            cout << "Please select the item you want to search:" << endl << endl;
            cout << "1. Football Kit" << endl;
            cout << "2. Balls" << endl;
            cout << "3. Football Boots" << endl;
            cout << "4. Cones" << endl;
            cout << "5. Goal" << endl;
            cout << "6. Tactics Board" << endl;
            cout << "7. Medical Kit" << endl;
            cout << "8. Water Bottles" << endl;

            while (equip != 1 && equip != 2 && equip != 3 && equip != 4 && equip != 5 && equip != 6 && equip != 7 && equip != 8)
            {
                cin.clear();
                cin >> equip; failInput(equip); cin.ignore(1000, '\n');
            }

            to_print = p->searchEquipment(equip);
            for (auto &i : to_print)
            {
                i.showInfo();
                cout << endl
                     << "-----------------------------------" << endl
                     << endl;
            }
            break;
        case '0':
            return 1;
    }

    waitInput();
    return 0;
}

int menu_add_provider()
{
    string name_provider;
    double rep = 5.1;
    Provider p1;
    ProviderPriorityQueue *p = national_team->getProviders();

    cout << "Provider name:" << endl;
    getline(cin, name_provider);
    p1.setName(name_provider);

    while (rep < 0.0 || rep > 5.0) {
        cout << "Provider reputation: (Please write a number between 0.0 and 5.0)" << endl;
        cin >> rep; failInput(rep); cin.ignore(1000,'\n');
    }
    p1.setReputation(rep);

    int nballs, ncones, nfootball_boots, nfootball_kit, ngoal, nmedical_kit, ntactics_board, nwater_bottles;
    cout << "no. Balls:" << endl;
    do{
        cin >> nballs;
        failInput(nballs);
        cin.ignore(1000,'\n');
    } while(nballs < 0);

    cout << "no. Cones:" << endl;
    do {
        cin >> ncones;
        failInput(ncones);
        cin.ignore(1000, '\n');
    }while(ncones < 0);

    cout << "no. Football Boots:" << endl;
    do {
        cin >> nfootball_boots;
        failInput(nfootball_boots);
        cin.ignore(1000, '\n');
    }while(nfootball_boots < 0);

    cout << "no. Football Kits:" << endl;
    do {
        cin >> nfootball_kit;
        failInput(nfootball_kit);
        cin.ignore(1000, '\n');
    }while(nfootball_kit < 0);

    cout << "no. Goals:" << endl;
    do {
        cin >> ngoal;
        failInput(ngoal);
        cin.ignore(1000, '\n');
    }while(ngoal< 0);

    cout << "no. Medical Kits:" << endl;
    do {
        cin >> nmedical_kit;
        failInput(nmedical_kit);
        cin.ignore(1000, '\n');
    }while(nmedical_kit < 0);

    cout << "no. Tactics Boards:" << endl;
    do {
        cin >> ntactics_board;
        failInput(ntactics_board);
        cin.ignore(1000, '\n');
    }while(ntactics_board < 0);

    cout << "no. Water Bottles:" << endl;
    do {
        cin >> nwater_bottles;
        failInput(nwater_bottles);
        cin.ignore(1000, '\n');
    }while(nwater_bottles < 0);

    p1.setEquipment(nballs, ncones, nfootball_boots, nfootball_kit, ngoal, nmedical_kit, ntactics_board, nwater_bottles);

    p->addProvider(p1);

    waitInput();
    return 1;
}

int menu_update_provider()
{
    string name_provider;
    int num,changed;
    double rep = 5.1;
    Equipment equip2;
    Provider p1;
    ProviderPriorityQueue *p = national_team->getProviders();
    vector<Provider> to_print;

    cout << "Provider name:" << endl;
    getline(cin, name_provider);
    to_print = p->searchName(name_provider);
    for (size_t i = 0; i < to_print.size(); i++)
    {
        cout << "Index: " << i << endl;
        to_print[i].showInfo();
        cout << "-----------------------------------" << endl
             << endl;
    }

    if (!to_print.empty()) {
    cout << "Choose index: " << endl;
    cin >> num; failInput(num); cin.ignore(1000, '\n');

    if (num < to_print.size()) {

        p->removeProvider(to_print[num]);
        char choice;

        cout << "Which field you want to change in Provider "  << endl;
        cout << "Select the correspondent index: " << endl;
        cout << "0. Change name" << endl;
        cout << "1. Change reputation" << endl;
        cout << "2. Change football kit" << endl;
        cout << "3. Change balls" << endl;
        cout << "4. Change football boots" << endl;
        cout << "5. Change cones" << endl;
        cout << "6. Change goal" << endl;
        cout << "7. Change tactics board" << endl;
        cout << "8. Change medical kit" << endl;
        cout << "9. Change water bottles" << endl << endl;

        cin >> choice;
        cin.ignore(1000,'\n');

        switch(choice){
            case '0':
                cout << "Provider name:" << endl;
                getline(cin, name_provider);
                to_print[num].setName(name_provider);
                cout << "Name successfully changed!!" << endl;
                break;
            case '1':
                while (rep < 0.0 || rep > 5.0) {
                    cout << "Reputation: (Please write a number between 0.0 and 5.0)" << endl;
                    cin >> rep; failInput(rep); cin.ignore(1000,'\n');
                }
                to_print[num].setReputation(rep);
                cout << "Reputation successfully changed!!" << endl;
                break;
            case '2':
                cout << "no. Football Kits:" << endl;
                do {
                    cin >> changed;
                    failInput(changed);
                    cin.ignore(1000, '\n');
                }while(changed < 0);
                to_print[num].setEquipment2(1,changed);
                cout << "no. Football Kits successfully changed!!" << endl;
                break;
            case '3':
                cout << "no. Balls:" << endl;
                do {
                    cin >> changed;
                    failInput(changed);
                    cin.ignore(1000, '\n');
                }while(changed < 0);
                to_print[num].setEquipment2(2,changed);
                cout << "no. Balls successfully changed!!" << endl;
                break;
            case '4':
                cout << "no. Football Boots:" << endl;
                do {
                    cin >> changed;
                    failInput(changed);
                    cin.ignore(1000, '\n');
                }while(changed < 0);
                to_print[num].setEquipment2(3,changed);
                cout << "no. Football Boots successfully changed!!" << endl;
                break;
            case '5':
                cout << "no. Cones:" << endl;
                do{
                cin >> changed;
                failInput(changed);
                cin.ignore(1000,'\n');
                }while(changed < 0);
                to_print[num].setEquipment2(4,changed);
                cout << "no. Cones successfully changed!!" << endl;
                break;
            case '6':
                cout << "no. Goals:" << endl;
                do{
                cin >> changed;
                failInput(changed);
                cin.ignore(1000,'\n');
                }while(changed < 0);
                to_print[num].setEquipment2(5,changed);
                cout << "no. Goals successfully changed!!" << endl;
                break;
            case '7':
                cout << "no. Tactics Boards:" << endl;
                do{
                cin >> changed;
                failInput(changed);
                cin.ignore(1000,'\n');
                }while(changed < 0);
                to_print[num].setEquipment2(6,changed);
                cout << "no. Tactics Boards successfully changed!!" << endl;
                break;
            case '8':
                cout << "no. Medical Kits:" << endl;
                do{
                cin >> changed;
                failInput(changed);
                cin.ignore(1000,'\n');
                }while(changed < 0);
                to_print[num].setEquipment2(7,changed);
                cout << "no. Medical Kits successfully changed!!" << endl;
                break;
            case '9':
                cout << "no. Water Bottles:" << endl;
                do{
                cin >> changed;
                failInput(changed);
                cin.ignore(1000,'\n');
                }while(changed < 0);
                to_print[num].setEquipment2(8,changed);
                cout << "no. Water Bottles successfully changed!!" << endl;
                break;
            default:
                cout << "Invalid Field Index !!" << endl;
                break;

        }

        p->addProvider(to_print[num]);
    } else {
        cout << "Index invalid" << endl;
    }
    } else {
        cout << "The Provider " << name_provider << " doesn't exist." << endl;
    }
    waitInput();
    return 1;
}
int menu_remove_provider()
{
    string name_provider;
    double rep = 5.1;
    int n;
    ProviderPriorityQueue *p = national_team->getProviders();
    vector<Provider> to_print;

    char menu = '3';

    cout << "========================================= " << endl;
    cout << "         Provider's Remove Menu           " << endl;
    cout << "========================================= \n"
         << endl;

    cout << "1. Remove By Provider's Name" << endl;
    cout << "2. Remove By Provider's Reputation" << endl;
    cout << "0. Return to Previous Menu" << endl
         << endl;

    while (menu != '1' && menu != '2' && menu != '0')
    {
        cin.clear();
        cin >> menu;
        cin.ignore(1000, '\n');
    }

    switch (menu)
    {
        case '1':
            cout << "Provider name:" << endl;
            getline(cin, name_provider);

            to_print = p->searchName(name_provider);
            for (size_t i = 0; i < to_print.size(); i++)  {
                cout << "Index: " << i << endl;
                to_print[i].showInfo();
                cout << "-----------------------------------" << endl
                     << endl;
            }

            break;
        case '2':
            while (rep < 0.0 || rep > 5.0) {
                cout << "Provider's Reputation: (Please write a number between 0.0 and 5.0)" << endl;
                cin >> rep;
                failInput(rep);
                cin.ignore(1000,'\n');
            }

            to_print = p->searchReputation(rep);
            for (size_t i = 0; i < to_print.size(); i++)
            {
                cout << "Index: " << i << endl;
                to_print[i].showInfo();
                cout << "-----------------------------------" << endl
                     << endl;
            }
            break;
        case '0':
            return 1;
    }
    if (!to_print.empty()) {
        cout << "Choose index: " << endl;
        cin >> n; failInput(n); cin.ignore(1000, '\n');
        if (n < to_print.size()) {
            p->removeProvider(to_print[n]);
            cout << "Removed successfully!" << endl;
        }
        else {
            cout << "Index invalid" << endl;
        }
    } else if (menu == '1') {
        cout << "The Provider " << name_provider << " doesn't exist." << endl;
    } else {
        cout << "There's no Provider with a reputation equal or higher than " << rep << "." << endl;
    }
    waitInput();
    return 0;
}

int menu_provider()
{
    char menu;

    cout << "========================================= " << endl;
    cout << "               Provider Menu              " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View all Providers" << endl;
    cout << "2. Buy Equipment" << endl;
    cout << "3. Search Provider" << endl;
    cout << "4. Add Provider" << endl;
    cout << "5. Update Provider" << endl;
    cout << "6. Remove Provider" << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000, '\n');

    ProviderPriorityQueue *p = national_team->getProviders();
    switch (menu)
    {
    case '1':
        p->print();
        waitInput();
        return 0;
    case '2':
        while (!menu_buy_provider());
        return 0;
    case '3':
        while (!menu_search_provider());
        return 0;
    case '4':
        while (!menu_add_provider());
        return 0;
    case '5':
        while (!menu_update_provider());
        return 0;
    case '6':
        while (!menu_remove_provider());
        return 0;
    case '0': // Exit
        return 1;
    default: // Invalid input
        return 0;
    }
}

int mainMenu(string &file_name) {
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)
    cout << "========================================= " << endl;
    cout << "          National Football Team          " << endl;
    cout << "                Main Menu                 " << endl;
    cout << "========================================= \n" << endl;
    cout << "1. Player Menu" << endl;
    cout << "2. Staff Menu" << endl;
    cout << "3. Coaches Menu" << endl;
    cout << "4. Providers Menu" << endl;
    cout << "5. Competitions Menu" << endl;
    cout << "6. View Team Stats" << endl;
    cout << "7. Save Information" << endl;
    cout << "8. App Info" << endl;

    cout << "0. Exit" << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');
    switch(menu)
    {
        case '1':    //View player info
            while(!menu_players());
            return 0;
        case '2':    //View staff info
            while(!menu_staff());
            return 0;
        case '3': //Coaches Menu
            while(!menu_coach());
            return 0;
        case '4': // Providers menu
            while(!menu_provider());
            return 0;
        case '5':    //View app info
            while(!menu_tournaments());
            return 0;
        case '6':    //View app info
            while(!menu_info());
            return 0;
        case '7':
            national_team->updateFile(file_name);
            cout << endl << "Information saved successfully in file: " << file_name << endl;
            waitInput();
            return 0;
        case '8':  //View app info
            while(!menu_credits());
            return 0;
        case '0':    //Exit function
            char confirmation;
            cout << "Are you sure you want to exit? [y/n] \nDon't forget to save your work before you leave." << endl;
            cin.clear();
            cin >> confirmation;
            cin.ignore(1000,'\n');
            if (confirmation == 'y') {
                exit(0);
            }
            return 0;
        default:     //Invalid input
            return 0;
    }
}

int fileMenu(){
    ifstream teamFile;
    string filename;

    cout << "   Write the filename you wish to read: " << endl;
    cout << "0. Go back to the previous menu" << endl;
    cin.clear();
    cin >> filename;
    cin.ignore(1000,'\n');
    teamFile.open(filename);

    if(filename == "0") return 1;

    while (teamFile.fail())
    {
        cin.clear();
        cout << "Incorrect filename, please enter again: " << endl;
        cin >> filename;
        teamFile.open(filename);

        if(filename == "0") return 1;
    }
    national_team = new Team(filename);
    while(!mainMenu(filename));
    return 1;
}

int createNewTeamMenu(){
    string team_name;

    cout << "   Write the name of your Team: " << endl;
    cout << "0. Go back to the previous menu" << endl;
    cin.clear();
    cin >> team_name;
    cin.ignore(1000,'\n');

    if(team_name == "0") return 1;

    national_team = new Team();
    national_team->setTeamName(team_name);
    string file_name = team_name + ".txt";
    while(!mainMenu(file_name));
    return 1;
}

int initMenu(){
    char menu;
    cout << "========================================= " << endl;
    cout << "          National Football Team          " << endl;
    cout << "========================================= \n" << endl;
    cout << "Choose and option:" << endl;
    cout << "1. Select the team file to read " << endl;
    cout << "2. Create a new team file " << endl;
    cout << "0. Exit program" << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu){
        case '1': //Select the Team File to read
            while(!fileMenu());
            return 0;
        case '2': //Create a new Team File
            while(!createNewTeamMenu());
            return 0;
        case '0': //Exits program
            return 1;
        default:  //Goes back
            return 0;
    }
}
