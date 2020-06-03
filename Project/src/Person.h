#ifndef AEDA_PERSON_H
#define AEDA_PERSON_H

#include <string>
#include "Date.h"

/// \brief Class for a Person
class Person {
private:
    std::string name; ///< Person's name
	Date birth;       ///< Person's date of birth
public:
    /// \brief An empty constructor for a Person.
    Person();
    /// \brief Person Constructor with the following data.
    /// \param name Person's name
    /// \param birth Person's birthday
	Person(std::string name, Date birth);
    /// \brief Get Method.
    /// \return Person's name
    std::string getName() const;
    /// \brief Get Method.
    /// \return Person's birthday
	Date getBirthday() const;
	/// \brief Set Method.
	/// \param name sets this name as the Person's name
	void setName(std::string name);
    /// \brief Set Method.
    /// \param birth sets this Date as the Person's birthday
	void setBirthday(Date birth);
    /// \brief Shows Person's data in a table.
	virtual void infoTable() const;
	/// \brief Shows Person's data.
    virtual void info() const;
};

/// \brief Class for throwing exceptions when a Person is not found
class PersonNotFound{
private:
    std::string name; ///< Name of the Person that wasn't found
public:
    /// \brief Class constructor for throwing exceptions when a Person is not found.
    /// \param name
    PersonNotFound(std::string name): name(name) {}
    /// \brief Get Method
    /// \return Name of the Person that wasn't found
    std::string getName() const{
        return name;
    }
};

/// \brief Class for throwing exceptions a Player already exists.
class PersonAlreadyExists{
private:
    std::string name; ///< Name of the Player that already exists
public:
    /// \brief Class constructor for throwing this exception.
    /// \param name Name of the Player that already exists
    PersonAlreadyExists(std::string name): name(name) {}
    /// \brief Get Method
    /// \return Name of the Player that already exists
    std::string getName() const{
        return name;
    }
};

/// \brief Class for throwing exceptions an incorrect Player name is used.
class CantUseThatName{
private:
    std::string name; ///< Name that causes error
public:
    /// \brief Class constructor for throwing this exception.
    /// \param name Name that causes error
    CantUseThatName(std::string name): name(name) {}
    /// \brief Get Method.
    /// \return Name that causes error
    std::string getName() const{
        return name;
    }
};

#endif
