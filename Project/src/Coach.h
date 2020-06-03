#ifndef COACH_H
#define COACH_H

#include <string>
#include <vector>
#include <tuple>

#include "bst.h"
#include "Date.h"
#include "Person.h"

/// \brief Class for Team's Coach
class Coach: public Person{
private:
    double numTitles; ///< Coach's number of titles
    bool currentCoach; ///< Coach's number of titles
    vector<std::tuple<string, Date, Date>> trainedTeams; ///< Coach's trained teams
public:
    /// \brief Coach empty constructor
    Coach() {}
    /// \brief Coach constructor
    /// \param name Coach's name
    /// \param birth Coach's birthday
    /// \param current Coach's current Coach
    /// \param titles Coach's number of titles
    Coach(std::string name, Date birth, bool current, double titles);
    /// \brief Shows Coach's info
    void show() const;
    /// \brief Adds a trained team to the Coach
    /// \param name Team's Name
    /// \param start Start date from the coaching period
    /// \param end Ending date from the coaching period
    void addTrainedTeam(string name, Date start, Date end);
    /// \brief Set Method
    /// \param c New Value for current Coach
    void setCurrentCoach(bool c);
    /// \brief Get Method
    /// \return Coach's number of titles
    double getTitles() const;
    /// \brief Get Method
    /// \return Coach's current coach
    bool getCurrentCoach() const;
    /// \brief Set Method
    /// \param t New Trained Teams
    void setTrainedTeam(vector<std::tuple<string, Date, Date>> t);
    /// \brief Get Method
    /// \return Coach's trained Teams
    vector<std::tuple<string, Date, Date>> getTrainedTeams() const;
    /// \brief Set Method
    /// \param n Coach's new Number of titles
    void setTitles(double n);
    /// \brief Overload of operator <, comparing Coaches by number of titles, and name if tied
    /// \param c1 Coach to compare the object with
    /// \return True if the object has less titles, or is name is before c1 alphabetically, if tied
    bool operator < (const Coach &c1) const;
    /// \brief Overload of operator ==, comparing Coaches by name
    /// \param c1 Coach to compare the object with
    /// \return True if Coaches have the same name, false otherwise
    bool operator == (const Coach &c1) const;

};
/// \brief Class for throwing exception when no Coach with such number of titles was found
class InvalidNumberTitles {
private:
    double numTitles; ///< Number of titles which is not associated with any coach
public:
    /// \brief Class constructor for throwing exception when no Coach with such number of titles was found
    /// \param num Number of titles which is not associated with any coach
    InvalidNumberTitles (double num): numTitles(num) {}
    /// \brief Get Method
    /// \return Number of titles which is not associated with any coach
    double getNumTitles() const {return numTitles;}
};

/// \brief Class for throwing exception when the team has no Coach
class NoCoach {
public:
    /// \brief Class constructor for throwing exception when the team has no Coach
    NoCoach() {}
    /// \brief Method for showing that the exception means that the team has no Coach
    void show() const {
        cout << "This team don't have a main coach! " << endl;
    }
};

/// \brief Class for throwing exception when the team has no Coaches in database
class NoSuggestedCoach {
public:
    /// \brief Class constructor for throwing exception when the team has no Coach
    NoSuggestedCoach() {}
    /// \brief Method for showing that the exception means that the team has no Coach
    void show() const {
        cout << "No coaches suggested since all are former national team coaches" << endl;
    }
};

/// \brief Class for saving coaches in a BST
class CoachTree
{
private:
    BST<Coach> tree; ///< BST of Coaches
public:
    CoachTree(): tree(Coach("", Date(), false,-1)) {}; //Ver isto melhor depois
    /// \brief Adds a Coach to the tree
    /// \param c Coach tobe added
    void addCoach(Coach &c);
    /// \brief Get Method
    /// \return BST of Coaches
    BST<Coach> getTree();
    /// \brief Finds Coach Members whose name contains the substring name
    /// \param name Substring used to find Coaches
    /// \return Vector of Coaches containing substring name
    vector<Coach> searchName(std::string name);
    /// Finds Coach Members that have a certain number of tiles
    /// \param num number of titles as a search parametre
    /// \return  Vector of Coaches with num titles
    vector<Coach> searchTitle(double num);
    /// \brief Searches the current Coach
    /// \return Current Coach
    Coach searchCurrentCoach();
    /// \brief Updates Coach name
    /// \param c Coach to be updated
    /// \param name Coach's new name
    void updateCoachName(Coach c, std::string name);
    /// \brief Updates Coach's number of titles
    /// \param c Coach to be updated
    /// \param titles Coach's new number of titles
    void updateCoachTitle(Coach c, double titles);
    /// \brief Updates Coach's Trained teams
    /// \param c Coach to be updated
    /// \param t Coach's new trained teams
    void updateCoachTeams(Coach c, vector<std::tuple<string, Date, Date>> t);
    /// \brief Removes a Coach from the tree
    /// \param c Coach to be removed
    void removeCoach(Coach c);
    /// \brief Shows Coaches with at most num titles
    /// \param num limit number of titles
    void showLessTitles(int num);
    /// \brief Shows Coaches with more than num titles
    /// \param num Minimum number of titles
    void showMoreTitles(int num);
    /// \brief Prints Coaches info
    void showCoachInfo() const;
    /// \brief Show the suggested Coach
    /// \return Coach with most number of titles who didn't work on national team
    Coach suggestedCoach(std::string teamName);
};

#endif
