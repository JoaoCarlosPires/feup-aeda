#ifndef AEDA_COMPETITION_H
#define AEDA_COMPETITION_H

#include "Player.h"
#include "Game.h"
#include <string>
#include <vector>
#include <map>

/// \brief Class for a Competition
class Competition{
private:
    std::string name;                        ///< Competition's name
    std::map<Player *, int> called_injured;  ///< Competition's called players associated in a map with number of days injured during competition
    std::vector<Game *> team_games;          ///< Competition's Games
    Date start;                              ///< Competition's starting Date
    Date end;                                ///< Competition's ending Date
    double moneyAccommodation;               ///< Competition's money accommodation
    bool paid;                               ///< Competition's paid status

public:
    /// \brief Competition Constructor without games.
    /// \param name Competition's name
    /// \param called Competition's called players
    /// \param start Competition's starting date
    /// \param end Competition's ending date
    /// \param moneyAccomodation Competition's money accommodation
    Competition(std::string name, std::map<Player *, int> called_injured, Date start, Date end, double moneyAccomodation);
    /// \brief Competition Constructor without games.
    /// \param name Competition's name
    /// \param called Competition's called players as Player pointers
    /// \param team_games Competition's games as Game pointers
    /// \param start Competition's starting date
    /// \param end Competition's ending date
    /// \param moneyAccommodation Competition's money accommodation
    /// \param paid Competition's money paid
    Competition(std::string name, std::map<Player *, int> called_injured, std::vector<Game *> team_games, Date start, Date end, double moneyAccommodation, bool paid);
    /// \brief Get Method.
    /// \return Competition's name
    std::string getCompetitionName() const;
    /// \brief Pays all Players for being called to this Competition
    void payPlayers();
    /// \brief Get Method.
    /// \return Competition's paid
    bool getPaid() const;
    /// \brief Get Method.
    /// \return Competition's money insurance
    double getMoneyInsurance() const;
    /// \brief Get Method.
    /// \return Competition's money accommodation
    double getMoneyAccommodation() const;
    /// \brief Get Method.
    /// \return Competition's Players with their number of injured days in a map
    std::map<Player *, int> getCalledInjured() const;
    /// \brief Get Method.
    /// \return Competition's Games
    std::vector<Game *> getGames() const;
    /// \brief Get Method.
    /// \return Competition's starting Date
    Date getStartDate() const;
    /// \brief Get Method.
    /// \return Competition's ending Date
    Date getEndDate() const;
    /// \brief Get Method.
    /// \return Competition's called players
    std::vector<Player *> getCalled() const;
    /// \brief Set Method.
    /// \param name Competition's name.
    void setName(const std::string &name);
    /// \brief Set Method.
    /// \param start Competition's starting date
    void setStart(const Date &start);
    /// \brief Set Method.
    /// \param end Competition's ending date
    void setEnd(const Date &end);
    /// \brief Set Method.
    /// \param inj Competition's injured players map
    void setPlayerInjuries(std::map<Player *, int> inj);
    /// \brief Method for updating injuries.
    /// \param p Player that will be updated
    /// \param i number of days injured
    void updatePlayerInjuries(Player * p, int i);
    /// \brief Set Method.
    /// \param moneyAccommodation Competition's money accommodation
    void setMoneyAccommodation(double moneyAccommodation);
    /// \brief Overloads the "<<" operator to enable using the competition as an ostream.
    /// \param out ostream for the overload
    /// \param comp Competition object that will be shown
    /// \return the overload of the operator (Shows comp's info)
    friend std::ostream & operator<<(std::ostream &out, const Competition &comp);
    /// \brief Overloads the operator ">>" to enable inputing data
    /// \param in Istream
    /// \param comp Competition where the data will be input
    /// \return Istream with changed Competition
    friend std::istream& operator>>(std::istream& in, Competition &comp);
    /// \brief Shows all PLayers from the Competition.
    void showPlayers() const;
    /// \brief Show all Games from the Competition.
    void showGames() const;
    /// \brief Adds a Game to the Competition.
    /// \param g Game pointer to be added
    void addGame(Game * g);
    /// \brief Removes a game from this Competition.
    /// \param opponent opponent from Game to be removed
    /// \param date Date from the Game to be removed
    void removeGame( std::string opponent, Date date);
    /// \brief Removes a Game in the Competition.
    /// \param g Game to be removed
    void removeGame(Game * g);
    /// \brief Finds a Game with an opponent and a Date.
    /// \param opponent Game's opponent
    /// \param date Game's date
    /// \return Game found with these opponent and Date, throws an exception otherwise
    Game * findGame(std::string opponent, Date date) const;
};
/// \brief Class for throwing exception when the Competition is already paid.
class AlreadyPaid{
    std::string name; ///< name of the Competition that is already paid
public:
    /// \brief Class constructor for throwing exception when the Competition is already paid.
    /// \param namename of the Competition that is already paid
    AlreadyPaid(std::string name): name(name){}
    /// \brief Get Method.
    /// \return name of the Competition that is already paid
    std::string getName(){return name;}
};
/// \brief Class for throwing exception when the Competition wasn't found.
class CompetitionNotFound{
private:
    std::string name; ///< name of the Competition that wasn't found
public:
    /// \brief Constructor for throwing exception when the Competition wasn't found.
    CompetitionNotFound(std::string name): name(name) {}
    /// \brief Get Method.
    /// \return name of the Competition that wasn't found
    std::string getName() const{
        return name;
    }
};

/// \brief Class for throwing exception when the Competition already exists.
class CompetitionAlreadyExists{
private:
    std::string name; ///< Name of the Competition that already exists
public:
    /// \brief Class constructor for throwing exception when the Competition already exists.
    /// \param name Name of the Competition that already exists
    CompetitionAlreadyExists(std::string name): name(name) {}
    /// \brief Get Method
    /// \return Name of the Competition that already exists
    std::string getName() const{
        return name;
    }
};


#endif
