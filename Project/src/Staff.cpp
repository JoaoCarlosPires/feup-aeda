#include <string>
#include "Staff.h"
#include <iomanip>

using namespace std;


Staff::Staff(string name, Date birth, double salary, string function, bool active) : Person(name,birth),
                                                                       salary(salary), function(function),
                                                                       isWorking(active) {}

double Staff::getSalary() const {
    return salary;
}
string Staff::getFunction() const {
    return function;
}

void Staff::infoTable() const {
    Person::infoTable();
    cout << setw(12) << this->function << " | " << setw(9) << this->salary << " | ";
}

void Staff::info() const{
    Person::info();
    cout << "Position: " << this->function << endl;
    cout << "Earnings: " << this->salary << endl;
}

std::ostream &operator<<(std::ostream &out, const Staff &s) {
    out << s.getName() << endl;
    out << s.getBirthday() << endl;
    out << s.salary << endl;
    out << s.function << endl;
    out << s.isWorking;

    return out;
}

void Staff::setSalary(double salary) {
    this->salary = salary;
}

void Staff::setFunction(std::string function){

    this->function = function;
}

bool Staff::operator==(const Staff &s2) {
    return Person::getName() == s2.getName();
}

bool Staff::operator<(const Staff &s2) {
    return Person::getName() < s2.getName();
}

bool Staff::isWorking1() const {
    return isWorking;
}

void Staff::setIsWorking(bool isWorking) {
    Staff::isWorking = isWorking;
}
