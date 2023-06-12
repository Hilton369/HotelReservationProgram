#ifndef ROOM_H
#define ROOM_H
#include "Customer.h"
#include <iostream>
#include <ctime>

class Room{
    public:
        Room();
        Room(int b);
        std::string const getCustID();
        int const getBeds();
        tm const getCheckin();
        tm const getCheckout();
        void addCust(std::string custName, int reqBeds, tm chkin, int duration);
        int getTotalBeds();
        void minusBeds(int x);
        void addBeds(int x);
        Room(const Room& other);  // Copy constructor
        Room& operator=(const Room& other);  // Assignment operator
        ~Room();

    private:
        Customer c;
        int beds;   // Number of beds
        tm checkin;     // Check-in date
        tm checkout;     // Check-out date
        static int totalBeds;
};

int Room::totalBeds = 0;

Room::Room(){}

Room::Room(int b){
    beds = b;
}

std::string const Room::getCustID(){
    return c.getCustID();
}

int Room::getTotalBeds(){
    return totalBeds;
}

int const Room::getBeds(){
    return beds;
}

tm const Room::getCheckin(){
    return checkin;
}

tm const Room::getCheckout(){
    return checkout;
}

void Room::addCust(std::string custName, int reqBeds, tm chkin, int duration){
    c = Customer(custName, reqBeds);
    checkin = checkout = chkin;
    checkout.tm_mday = checkin.tm_mday + duration;
}

void Room::minusBeds(int x){
    totalBeds -= x;
}

void Room::addBeds(int x){
    totalBeds += x;
}

Room::Room(const Room& other) {
    c = other.c;
    beds = other.beds;
    checkin = other.checkin;
    checkout = other.checkout;
}

Room& Room::operator=(const Room& other) {
    if (this == &other) {
        return *this;
    }
    c = other.c;
    beds = other.beds;
    checkin = other.checkin;
    checkout = other.checkout;
    return *this;
}

Room::~Room(){}


#endif