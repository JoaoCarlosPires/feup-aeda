#ifndef AEDA_PLAYER_H
#define AEDA_PLAYER_H

#include <string>
#include "Person.h"
#include "Statistics.h"

/// \brief Class for a Player.
class Player : public Person
{
private:
    std::string club;     ///< Player's club.
    std::string position; ///< Player's position.
	int weight;           ///< Player's weight in kg.
	int height;           ///< Player's height in cm.
	int value;            ///< Player's value in million euros.
    double earnings;      ///< Player's earnings in euros.
    double insurance;     ///< Player's insurance in euros. Its equal to value * 2
    PlayerStatistics *player_stats; ///< Player's statistics.


public:
    /// \brief Player empty constructor.
    Player();
    /// \brief Player constructor with all parameters
    /// \param name Player's name.
    /// \param birth Player's birthday.
    /// \param club Player's club.
    /// \param position Player's position Goalkeeper/Defender/Midfielder/Forward.
    /// \param weight Player's weight in Kg.
    /// \param height Player's height in cm.
    /// \param value Player's value in million euros.
    /// \param earnings Player's in euros.
    /// \param player_stats Player's individual statistics.
    Player(std::string name, Date birth, std::string club, std::string position, int weight, int height, int value, double earnings, PlayerStatistics *player_stats);
	/// \brief GetMethod.
	/// \return Player's club
	std::string getClub() const;
	/// \brief Get Method.
	/// \return Player's position Goalkeeper/Defender/Midfielder/Forward
    std::string getPosition() const;
    /// \brief Get Method.
    /// \return Player's weight in Kg
	int getWeight() const;
	/// \brief Get Method.
	/// \return Player's height in cm
	int getHeight() const;
	/// \brief Get Method.
	/// \return Player's Value in euros
	int getValue() const;
	/// \brief Get Method.
	/// \return Player's earnings in euros
	double getEarnings() const;
	/// \brief Get Method.
	/// \return Player's insurance in euros
    double getInsurance() const;
    /// \brief Get Method.
    /// \return Player's Statistics
    PlayerStatistics * getStatistics() const;
    /// \brief Set Method.
    /// \param club Player's club
	void setClub(std::string club);
    /// \brief Set Method.
    /// \param pos Player's position
    void setPosition(std::string pos);
    /// \brief Set Method.
    /// \param weight Player's weight in kg
	void setWeight(int weight);
    /// \brief Set Method.
    /// \param height Player's height in cm
	void setHeight(int height);
    /// \brief Set Method.
    /// \param value Player's value in euros
	void setValue(int value);
    /// \brief Set Method.
    /// \param value Player's value in euros
	void setEarnings(double value);
	/// \brief Shows Player's attributes in a table.
    void infoTable() const;
    /// \brief Shows Player's attributes.
    void info() const;
    /// \brief Operator "<<" overload for showing Player's info.
    /// \param out Ostream
    /// \param p Player that is shown
    /// \return Ostream for PLayer info
    friend std::ostream& operator<<(std::ostream& out, const Player &p);

};
/// \brief Class for throwing exceptions when no position is found.
class PositionNotFound{
private:
    std::string position; ///< Position that wasn't found
public:
    /// \brief Class constructor for throwing exceptions when no position was found.
    /// \param position Position that wasn't found
    PositionNotFound(std::string position): position(position) {}
    /// \brief Get Method.
    /// \return Position that wasn't found
    std::string getPosition() const{
        return position;
    }
};


#endif //AEDA_UTILS_H
