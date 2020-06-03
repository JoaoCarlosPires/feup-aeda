//
// Created by diogo on 16/10/2019.
//

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <vector>

/// \brief Class for a Date.
class Date{

private:
    unsigned day;  ///< Day
    unsigned month;///< Month.
    unsigned year; ///< Year.

public:
    /// \brief Date's empty constructor.
    Date();
    /// \brief Date's constructor using a string.
    /// \param date DD/MM/AAAA
    Date(std::string date);
    /// \brief Dates constructor using int numbers
    /// \param day Date's day
    /// \param month Date's month
    /// \param year Date's year
    Date(unsigned short day, unsigned short month, unsigned year);
    /// \brief Get Method.
    /// \return day
    unsigned short getDay() const;
    /// \brief Get Method.
    /// \return month
    unsigned short getMonth() const;
    /// \brief Get Method.
    /// \return year
    unsigned getYear() const;
    /// \brief Get Method.
    /// \return Date as a string (format DD/MM/AAAA)
    std::string getDate() const;
    /// \brief Set Method.
    /// \param day new day
    void setDay(unsigned short day);
    /// \brief Set Method.
    /// \param month new month
    void setMonth(unsigned short month);
    /// \brief Set Method.
    /// \param year new year
    void setYear(unsigned year);
    /// \brief Checks if 2 dates are equal.
    /// \param date checks object Date with this date
    /// \return true if Dates are equal, false otherwise
    bool isEqualTo(const Date &date);
    /// \brief Checks if the Date rom the class is after the one given by parameter.
    /// \param date compares object date with this date
    /// \return true if the Date is after date, false otherwise
    bool isAfter(const Date &date);
    /// \brief Checks if the Date rom the class is before the one given by parameter.
    /// \param date compares object date with this date
    /// \return true if the Date is before date, false otherwise
    bool isBefore(const Date &date);
    /// \brief Counts the days until Date reaches date.
    /// \param date days until this date
    /// \return Number of days until date is reached
    int daysUntil(const Date &date) const;
    /// \brief Overloads the "<<" operator by showing the Date's members.
    /// \param out ostream
    /// \param date this date which will shown
    /// \return shows date's day, month and year
    friend std::ostream& operator<<(std::ostream& out, const Date & date);
    /// \brief Overloads the ">>" operator by generating a new Date given by user input
    /// \param in istream
    /// \param date date that will be created
    /// \return creates a new date
    friend std::istream& operator>>(std::istream& in, Date & date);

};


#endif //DATE_H
