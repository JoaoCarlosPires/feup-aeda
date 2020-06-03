#ifndef AEDA_STATISTICS_H
#define AEDA_STATISTICS_H

/// \brief Abstract class for Player Statistics.
class PlayerStatistics{
protected:
    int yellow_cards;///< Number of yellow cards
    int red_cards;   ///< Number of red cards
    /// \brief protected constructor, can't create a instance of abstract class.
    /// \param yellow_cards
    /// \param red_cards
    PlayerStatistics(int yellow_cards, int red_cards) : yellow_cards(yellow_cards), red_cards(red_cards) { }
public:
    /// \brief Class destructor.
    virtual ~PlayerStatistics() {}
    /// \brief Get Method.
    /// \return Number of yellow cards
    int getYellowCards() const {return yellow_cards;}
    /// \brief Get Method.
    /// \return Number of red cards
    int getRedCards() const {return red_cards;}
    /// \brief Purely virtual method for showing Player Statistics.
    virtual void info() const = 0;
    /// \brief Purely virtual method for reading Statistics.
    /// \param os Ostream
    virtual void writeStats(std::ostream& os) const = 0;
    /// \brief Virtual function allowing Statistics update.
    /// \param in Istream of statistics
    virtual void updateStats(std::istream& in) = 0;
    /// \brief Overload of operator "<<" to enable reading Statistics.
    /// \param os Ostream
    /// \param p Player Statistics object where read Statistics will be stored
    /// \return Stream of statistics
    friend std::ostream& operator<< (std::ostream& os, const PlayerStatistics * p);
    /// \brief Overload of operator ">>" to enable input on Statistics.
    /// \param in istream
    /// \param p Player that will be changed
    /// \return Stream of statistics
    friend std::istream & operator>>(std::istream &in,  PlayerStatistics *p);
};

/// \brief class about Goalkeeper Statistics, derived from Player Statistics.
class GoalkeeperStatistics : public PlayerStatistics {
private:
    int saves;       ///< Number of saves by a Goalkeeper
    int clearances;  ///< Number of clearances by a Goalkeeper

public:
    /// \brief Empty constructor for Goalkeeper Statistics.
    GoalkeeperStatistics():  PlayerStatistics(0, 0),  saves(0), clearances(0) {}
    /// \brief Constructor for Goalkeeper Statistics.
    /// \param saves Number of saves by a Goalkeeper
    /// \param clearances Number of clearances by a Goalkeeper
    /// \param yellow_cards Number of yellow cards by a Goalkeeper
    /// \param red_cards Number of red cards by a Goalkeeper
    GoalkeeperStatistics(int saves, int clearances, int yellow_cards, int red_cards): PlayerStatistics(yellow_cards, red_cards), saves(saves), clearances(clearances) {}
    /// \brief Void Method for showing Goalkeeper's Statistics.
    void info() const;
    /// \brief Method for reading Goalkeeper's Statistics.
    /// \param os Ostream
    void writeStats(std::ostream& os) const;
    /// \brief Function allowing Statistics update.
    /// \param in Istream of statistics
    void updateStats(std::istream& in);
};
/// \brief class about Defender Statistics, derived from Player Statistics.
class DefenderStatistics : public PlayerStatistics {
private:
    int disarm;          ///< Number of disarms by a Defender
    int fouls;            ///< Defender's fouls

public:
    /// \brief Empty constructor for Defender Statistics.
    DefenderStatistics(): PlayerStatistics(0, 0), disarm(0), fouls(0) {}
    /// \brief Constructor for Defender Statistics.
    /// \param disarm Number of disarms by a Defender
    /// \param passing_accuracy Defender's passing accuracy, in percentage
    /// \param yellow_cards Number of yellow cards by a Defender
    /// \param red_cards Number of red cards by a Defender
    DefenderStatistics(int disarm, int fouls ,int yellow_cards, int red_cards): PlayerStatistics(yellow_cards, red_cards), disarm(disarm), fouls(fouls) {}
    /// \brief Void Method for showing Defender's Statistics.
    void info() const;
    /// \brief Method for reading Defender's Statistics.
    /// \param os Ostream
    void writeStats(std::ostream& os) const;
    /// \brief Function allowing Statistics update.
    /// \param in Istream of statistics
    void updateStats(std::istream& in);
};

/// \brief class about Midfielder Statistics, derived from Player Statistics.
class MidfielderStatistics : public PlayerStatistics {
private:
    int passing_accuracy;///< Midfielder's passing accuracy, in percentage
    int shots;           ///< Number of shots by a Midfielder

public:
    /// \brief Empty constructor for Midfielder Statistics.
    MidfielderStatistics():PlayerStatistics(0, 0), passing_accuracy(0), shots(0) {}

    /// \brief Constructor for Midfielder Statistics.
    /// \param passing_accuracy Midfielder's passing accuracy, in percentage
    /// \param shots Number of shots by a Midfielder
    /// \param yellow_cards Number of yellow cards by a Midfielder
    /// \param red_cards Number of red cards by a Midfielder
    MidfielderStatistics(int passing_accuracy, int shots, int yellow_cards, int red_cards): PlayerStatistics(yellow_cards, red_cards), passing_accuracy(passing_accuracy), shots(shots) {}
    /// \brief Void Method for showing Midfielder's Statistics.
    void info() const;
    /// \brief Method for reading Midfielder's Statistics.
    /// \param os
    void writeStats(std::ostream& os) const;
    /// \brief Function allowing Statistics update.
    /// \param in Istream of statistics
    void updateStats(std::istream& in);
};

/// \brief class about Forward Statistics, derived from Player Statistics.
class ForwardStatistics : public PlayerStatistics{
private:
    int total_goals; ///< Number of goals by a Forward
    int shots;       ///< Number of shots by a Forward

public:
    /// \brief Empty constructor for Forward Statistics.
    ForwardStatistics(): PlayerStatistics(0, 0), total_goals(0), shots(0) {}
    /// \brief Constructor for Forward Statistics.
    /// \param total_goals Number of goals by a Forward
    /// \param shots Number of shots by a Forward
    /// \param yellow_cards Number of yellow cards by a Forward
    /// \param red_cards  Number of red cards by a Forward
    ForwardStatistics(int total_goals, int shots, int yellow_cards, int red_cards): PlayerStatistics(yellow_cards, red_cards), total_goals(total_goals), shots(shots) {}
    /// \brief Void Method for showing Forward's Statistics.
    void info() const;
    /// \brief Method for reading Forward's Statistics.
    /// \param os
    void writeStats(std::ostream& os) const;
    /// \brief Function allowing Statistics update.
    /// \param in Istream of statistics
    void updateStats(std::istream& in);
};

/// \brief This class refers to the Team Statistics of a Team during a Game
class Statistics {
private:
    int goals_scored;   ///<  Number of goals scored
    int goals_conceded; ///<  Number of goals conceded
    int shots;          ///<  Number of shots on goal
    int ball_possession;///<  Ball possession as percentage
    int yellow_cards;   ///<  Number of yellow cards received
    int red_cards;      ///<  Number of red cards received
    int injured;        ///<  1 if injured, 0 otherwise
    int free_kicks;     ///<  Number of free kicks
    int corner_kicks;   ///<  Number of corners
public:
    /// \brief Statistics empty constructor.
    Statistics();
    /// \brief Statistics constructor
    /// \param goalsScored Number of goals scored
    /// \param goalsConceded Number of goals conceded
    /// \param shots  Number of shots on goal
    /// \param ballPossession Ball possession as percentage
    /// \param yellowCards Number of yellow cards received
    /// \param redCards Number of red cards received
    /// \param injured 1 if injured, 0 otherwise
    /// \param freeKicks Number of free kicks
    /// \param cornerKicks Number of corners
    Statistics(int goalsScored, int goalsConceded, int shots, int ballPossession, int yellowCards, int redCards,
               int injured, int freeKicks, int cornerKicks);
    /// \brief Get Method.
    /// \return Number of goals scored
    int getGoalsScored() const;
    /// \brief Get Method.
    /// \return Number of goals conceded
    int getGoalsConceded() const;
    /// \brief Get Method.
    /// \return Number of shots on goal
    int getShots() const;
    /// \brief Get Method.
    /// \return Ball possession as percentage
    int getBallPossession() const;
    /// \brief Get Method.
    /// \return Number of yellow cards received
    int getYellowCards() const;
    /// \brief Get Method.
    /// \return Number of red cards received
    int getRedCards() const;
    /// \brief Get Method.
    /// \return 1 if injured, 0 otherwise
    int getInjured() const;
    /// \brief Get Method.
    /// \return Number of free kicks
    int getFreeKicks() const;
    /// \brief Get Method.
    /// \return Number of corners
    int getCornerKicks() const;
    /// \brief Set Method.
    /// \param goalsScored Number of goals scored
    void setGoalsScored(int goalsScored);
    /// \brief Set Method.
    /// \param goalsConceded Number of goals conceded
    void setGoalsConceded(int goalsConceded);
    /// \brief Set Method.
    /// \param shots Number of shots on goal
    void setShots(int shots);
    /// \brief Set Method.
    /// \param ballPossession Ball possession as percentage
    void setBallPossession(int ballPossession);
    /// \brief Set Method.
    /// \param yellowCards Number of yellow cards received
    void setYellowCards(int yellowCards);
    /// \brief Set Method.
    /// \param redCards Number of red cards received
    void setRedCards(int redCards);
    /// \brief Set Method.
    /// \param injured 1 if injured, 0 otherwise
    void setInjured(int injured);
    /// \brief Set Method.
    /// \param freeKicks Number of free kicks
    void setFreeKicks(int freeKicks);
    /// \brief Set Method.
    /// \param cornerKicks Number of corners
    void setCornerKicks(int cornerKicks);
    /// \brief Shows Statistics
    void info() const;
    /// \brief overload of operator "<<" allowing to write Statistics.
    /// \param os
    /// \param statistics
    /// \return Ostream for showing Statistics
    friend std::ostream& operator<<(std::ostream& os, const Statistics & statistics);
};



#endif