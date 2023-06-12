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
        // void addCust();
        // void minusCust();
        // int const getNoOfCust();

    private:
        std::string custID;
        int reqBeds;
        // static int totalCust;
};

// int Customer::totalCust = 0;

Customer::Customer(){}

Customer::Customer(std::string s, int r){
    custID = s;
    reqBeds = r;
}

std::string const Customer::getCustID(){
    return custID;
}
int const Customer::getReqBeds(){
    return reqBeds;
}

// void Customer::addCust(){
//     totalCust++;
// }

// void Customer::minusCust(){
//     totalCust--;
// }

// int const Customer::getNoOfCust(){
//     return totalCust;
// }



#endif