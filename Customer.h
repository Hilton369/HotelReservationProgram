/**
 * Customer class header file
 * Author: Hilton Wong 100385078
 * Date: 11JUN23
*/
#ifndef CUST_H
#define CUST_H
#include <iostream>
#include <ctime>

class Customer{
    public:
        Customer();
        Customer(std::string, int);
        std::string const getCustID();
        int const getReqBeds();
    private:
        std::string custID;
        int reqBeds;
};

/**
 * Default constructor
*/
Customer::Customer(){}

/**
 * Constructor with parameters for customer ID and number of requested beds
*/
Customer::Customer(std::string s, int r){
    custID = s;
    reqBeds = r;
}

/**
 * Getter for customer ID
*/
std::string const Customer::getCustID(){
    return custID;
}

/**
 * Getter for number of requested beds
*/
int const Customer::getReqBeds(){
    return reqBeds;
}


#endif