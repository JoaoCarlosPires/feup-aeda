#ifndef AEDA_MENUS_H
#define AEDA_MENUS_H

#include "Competition.h"
#include <string>
/// \brief table with information of all players where is possible to sort.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_allPlayers();

/// \brief Menu for searching Players by Name or Position.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_searchPlayers();

/// \brief Menu to add a new Player.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_addPlayer();

/// \brief Menu to update Players.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_updatePlayers();

/// \brief Menu to remove players.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_removePlayer();

/// \brief All Player information is here.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_players();

/// \brief Menu to view Staff Members.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_view_staff();

/// \brief Menu to Add Staff Members.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_add_staff();

/// \brief Menu to Update Staff Members.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_update_staff();

/// \brief Menu to Remove Staff Members.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_remove_staff();

/// \brief All Staff Member information is here.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_staff();

/// \brief Menu to Search Games.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_searchGame();

/// \brief All Games information is here.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_games();

/// \brief Menu to pay competition fees to players.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_payCompetitions();

/// \brief Show games for one particular competition.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_competitionGames(Competition * comp);

/// \brief Show called players in one competition.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_calledCompetition(Competition* comp);

/// \brief Show detailed information about one competition.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_detailedCompetition(Competition * comp);

/// \brief Menu to select a competition to see detailed information about.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_chooseCompetition();

/// \brief Menu to create a new Competition.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_creatCompetition();

/// \brief Menu to update a Competition.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_updateCompetition();

/// \brief Menu to remove a Competition.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_removeCompetition();

/// \brief This menu show Competition Information.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_tournaments();

/// \brief This menu indicates a Team's stats.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_info();

/// \brief This menu shows the app creators.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_credits();

 /// \brief This menu allows you to move between sub menus in order to use the app properly.
 /// \return if 0 the menu is called again, 1 program ends
int mainMenu(std::string &file_name);

/// \brief Allows the user to open a .txt file referring to a team.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int fileMenu();

/// \brief Allows the user to create a new Team.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int createNewTeamMenu();

/// \brief Menu that either allows the user to open a file or create a new one.
/// \return if 0 the menu is called again, 1 program ends
int initMenu();

/// \brief Menu that allows the user to Search, Add, Update and Remove Coaches.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_coach();

/// \brief Menu to Search Coaches.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_search_coach();

/// \brief Menu to add Coaches.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_add_coach();

/// \brief Menu to update Coaches.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_update_coach();

/// \brief Menu to remove Coaches.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_remove_coach();

/// \brief Menu that allows the user to Search, Add, Update and Remove Providers.
/// \return if 0 the menu is called again, 1 goes back to main menu
int menu_provider();

/// \brief Menu that allows the user to search for a Provider by Name, by Reputation or by Equipment Item.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_search_provider();

/// \brief Menu that allows the user to Add a Provider.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_add_provider();

/// \brief Menu that allows the user to Update a Provider Info.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_update_provider();

/// \brief Menu that allows the user to Remove a Provider.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_remove_provider();

/// \brief Menu that allows the user to Buy Equipment from a Provider.
/// \return if 0 the menu is called again, 1 goes back to the previous menu
int menu_buy_provider();

#endif
