#ifndef INC_1_2_CLIENTS_COMPARASION_H
#define INC_1_2_CLIENTS_COMPARASION_H

#include "Clients.h"
#include <sstream>
#include "string"

PHONE::PHONE(int number)
        : number(number) {}

std::ostream& operator<<(std::ostream& os, const PHONE& ph) {
    os << ph.number;
    return os;
}

FIO::FIO(std::string surname, std::string name, std::string f_name)
        : surname(std::move(surname)), name(std::move(name)), f_name(std::move(f_name)) {}

bool FIO::operator>(const FIO& other) const {
    return surname > other.surname ||
           (surname == other.surname && name > other.name) ||
           (surname == other.surname && name == other.name && f_name > other.f_name);
}

bool FIO::operator==(const FIO& other) const {
    return surname == other.surname && name == other.name && f_name == other.f_name;
}

bool FIO::operator<(const FIO& other) const {
    return other > *this;
}

bool FIO::operator>=(const FIO& other) const {
    return !(*this < other);
}

bool FIO::operator<=(const FIO& other) const {
    return !(*this > other);
}

bool FIO::operator!=(const FIO& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const FIO& fio) {
    os << fio.surname << " " << fio.name << " " << fio.f_name;
    return os;
}

DB::DB(int day, int month, int year) : day(day), month(month), year(year) {}

bool DB::operator>(const DB& other) const {
    return year > other.year || (year == other.year && month > other.month) ||
           (year == other.year && month == other.month && day > other.day);
}

bool DB::operator==(const DB& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool DB::operator<(const DB& other) const {
    return other > *this;
}

bool DB::operator>=(const DB& other) const {
    return !(*this < other);
}

bool DB::operator<=(const DB& other) const {
    return !(*this > other);
}

bool DB::operator!=(const DB& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const DB& db) {
    os << db.day << "." << db.month << "." << db.year;
    return os;
}

Adress::Adress(std::string address) : address(std::move(address)) {}

bool Adress::operator>(const Adress& other) const {
    return address > other.address;
    //return address.compare(other.address);
}

bool Adress::operator==(const Adress& other) const {
    //return address.compare(other.address);
    return address == other.address;
}

bool Adress::operator<(const Adress& other) const {
    return other > *this;
}

bool Adress::operator>=(const Adress& other) const {
    return !(*this < other);
}

bool Adress::operator<=(const Adress& other) const {
    return !(*this > other);
}

bool Adress::operator!=(const Adress& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Adress& address) {
    os << address.address;
    return os;
}

Person::Person(int phone, std::string surname, std::string name, std::string f_name, int day,
               int month, int year, std::string address)
        : phone(phone),
          fio(std::move(surname), std::move(name), std::move(f_name)),
          date(day, month, year),
          address(std::move(address)) {}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.phone << " " << person.fio << " " << person.date << " " << person.address;
    return os;
}

std::vector<Person*> ReadFromFile(std::string h) {
    std::ifstream inputFile(h);
    std::vector<Person*> people;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);

        int phone;
        std::string surname, name, f_name;
        int day, month, year;
        std::string address;

        iss >> phone;
        iss >> surname;
        iss >> name;
        iss >> f_name;

        std::string date;
        iss >> date;
        std::istringstream dateStream(date);
        char dot;
        dateStream >> day >> dot >> month >> dot >> year;

        // Считываем оставшуюся часть строки в переменную address
        std::getline(iss >> std::ws, address);

        Person* person = new Person(phone, surname, name, f_name, day, month, year, address);
        people.push_back(person);
    }

    inputFile.close();

    return people;
}

#endif //INC_1_2_CLIENTS_COMPARASION_H