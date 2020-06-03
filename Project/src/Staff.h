#ifndef AEDA_STAFF_H
#define AEDA_STAFF_H

#include <string>
#include "Person.h"

/// \brief Class for a Staff.
class Staff : public Person
{
private:
    double salary;           ///< Staff's salary
    std::string function;    ///< Staff's function
    bool isWorking;          ///< Staff's working status
public:
    /// \brief Staff Constructor.
    /// \param name Staff's name
    /// \param birth Staff's birthday
    /// \param salary Staff's salary in euros
    /// \param function Staff's function
    Staff(std::string name, Date birth, double salary, std::string function, bool active);
    /// \brief Get Method.
    /// \return Staff's salary in euros
    double getSalary() const;
    /// \brief Get Method.
    /// \return Staff's function
    std::string getFunction() const;
    /// \brief Set Method.
    /// \param salary Staff's salary
    void setSalary(double salary);
    /// \brief Set Method.
    /// \param function Staff's function
    void setFunction(std::string function);
    /// \brief Shows Staff's info as a table.
    void infoTable() const;
    /// \brief Shows Staff's info.
    void info() const;
    /// \brief Overload of operator "<<" to allow showing a Staff Member.
    /// \param out Ostream
    /// \param s Staff Member that will be shown
    /// \return Ostream to llow showing Staff Member's data
    friend std::ostream &operator<<(std::ostream &out, const Staff &s);
    /// \brief Overload of operator == to compare Staff Members by name.
    /// \param s2 Staff Member to compare with
    /// \return true if s2 has the same name as the object, false otherwise
    bool operator == (const Staff &s2);
    /// \brief Overload of operator < to sort Staff Member's by name, alphabetically.
    /// \param s2 Staff member to compare with
    /// \return true if the object is first, alphabetically, false otherwise
    bool operator < (const Staff &s2);
    /// \brief Equivalent to a Get Method.
    /// \return true if Staff memberis working, false otherwise
    bool isWorking1() const;
    /// \brief Set Method.
    /// \param isWorking new working status for the Staff Member
    void setIsWorking(bool isWorking);
};

/// \brief Class for throwing exception when no Staff Member with such function was found.
class FunctionNotFound{
private:
    std::string function; ///< function that doesn't exist
public:
    /// \brief Class constructor for throwing exception when no Staff Member with such function was found.
    /// \param function function that doesn't exist
    FunctionNotFound(std::string function): function(function) {}
    /// \brief Get Method
    /// \return function that doesn't exist
    std::string getFunction() const{
        return function;
    }
};

#endif
