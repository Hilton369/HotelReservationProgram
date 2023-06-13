/**
 * Room header file
 * Author: Hilton Wong 100385078
 * Date: 11JUN23
*/
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
        static int totalBeds; // Number of unoccupied beds across all rooms
};

int Room::totalBeds = 0;

// Default constructor
Room::Room(){}

// Constructor with number of beds in the room
Room::Room(int b){
    beds = b;
}

// Getter for customer ID
std::string const Room::getCustID(){
    return c.getCustID();
}

// Getter for total number of unoccupied beds in all rooms
int Room::getTotalBeds(){
    return totalBeds;
}

// Getter for number of beds in room
int const Room::getBeds(){
    return beds;
}

// Getter for check in date
tm const Room::getCheckin(){
    return checkin;
}

// Getter for check out date
tm const Room::getCheckout(){
    return checkout;
}

/**
 * Function to add customer info to an empty room
 * Input: Customer ID, no. of requested beds, checkin date, duration of stay
*/
void Room::addCust(std::string custName, int reqBeds, tm chkin, int duration){
    c = Customer(custName, reqBeds);
    checkin = checkout = chkin;
    checkout.tm_mday = checkin.tm_mday + duration;
}

/**
 * Function to decrease total number of unoccupied beds across all rooms
 * Input: no. of beds to decrease total by
*/
void Room::minusBeds(int x){
    totalBeds -= x;
}

/**
 * Function to increase total number of unoccupied beds across all rooms
 * Input: no. of beds to increase total by
*/
void Room::addBeds(int x){
    totalBeds += x;
}

/**
 * Copy constructor
*/
Room::Room(const Room& other) {
    c = other.c;
    beds = other.beds;
    checkin = other.checkin;
    checkout = other.checkout;
}

/**
 * Overloaded assignment operator
*/
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

/**
 * Destructor
*/
Room::~Room(){}


#endif