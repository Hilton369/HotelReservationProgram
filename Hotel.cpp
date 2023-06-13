/*  Hotel.cpp file
    Author: Hilton Wong 100385078
    Date: 11JUN23
*/

#include "Customer.h"
#include "Room.h"
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include "DLL.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>

/**
 * Function to read text file of customer bookings
 * Input: Name of the file as string
 * Output: Queue with each booking being a separate element in the queue
*/
LinkedQueue<std::string> readFile(std::string name){
    std::ifstream fin;
    std::string s;
    LinkedQueue<std::string> bookings;
    fin.open(name);
    if(fin.is_open()){
        std::getline(fin, s);
        while(std::getline(fin, s)){
            bookings.enqueue(s);
        }
        fin.close();
    }
    return bookings;
}

/**
 * Function to split string into parts for easier usability
 * Input: String to split, Delimiter string
 * Output: Substring up until first occurence of delimiter
*/
std::string splitString(std::string& s, std::string d){
    std::string result = s.substr(0, s.find(d));
    int len = result.length() + d.length();
    s.erase(0, len);
    return result;
}

/**
 * Function to convert date from string to tm struct
 * Input: Date string in the form of DD/MM/YY
 * Output: tm object for the matching date
*/
tm calcTime(std::string s){
    std::string date = splitString(s, ", ");
    tm time{};
    time.tm_mday = stoi(splitString(date, "/"));
    time.tm_mon = stoi(splitString(date,"/")) - 1;
    time.tm_year = stoi(date) - 1900;
    return time;
}

/**
 * Function to check if a booking can be assigned to a room and chooses what kind of room (1 bed/2 bed/3 bed) would best suit customer
 * Input: Booking string, stack of available 1 bed rooms, stack of available 2 bed rooms, stack of available 3 bed rooms, 
 * vector of occupied rooms
 * Output: True if customer has been assigned to a room, false if not
*/
bool assignRoom(std::string s, LinkedStack<Room>& available1, LinkedStack<Room>& available2, LinkedStack<Room>& available3, std::vector<Room>& occupied){
    std::string date = splitString(s, ", ");
    std::string name = splitString(s, ", ");
    int reqBeds = stoi(splitString(s, ", "));
    int totalReqBeds = reqBeds;
    int dur = stoi(s);
    tm time{};
    time = calcTime(date);
    Room temp;
    if(temp.getTotalBeds() >= reqBeds && !(available3.empty() && available2.empty() && available1.empty())){
        while(reqBeds > 0){
            if(reqBeds % 3 == 0 && !available3.empty()){
                Room r;
                r = available3.top();
                available3.pop();
                r.addCust(name, totalReqBeds, time, dur);
                occupied.push_back(r);
                reqBeds -= 3;
                r.minusBeds(3);
            }else if(reqBeds % 2 == 0 && !available2.empty()){
                Room r;
                r = available2.top();
                available2.pop();
                r.addCust(name, totalReqBeds, time, dur);
                occupied.push_back(r);
                reqBeds -= 2;
                r.minusBeds(2);
            }else if(!available1.empty()){
                Room r;
                r = available1.top();
                available1.pop();
                r.addCust(name, totalReqBeds, time, dur);
                occupied.push_back(r);
                reqBeds -= 1;
                r.minusBeds(1);
            }else if(!available2.empty()){
                Room r;
                r = available2.top();
                available2.pop();
                r.addCust(name, totalReqBeds, time, dur);
                occupied.push_back(r);
                reqBeds -= 2;
                r.minusBeds(2);
            }else{
                Room r;
                r = available3.top();
                available3.pop();
                r.addCust(name, totalReqBeds, time, dur);
                occupied.push_back(r);
                reqBeds -= 3;
                r.minusBeds(3);
            }
        }
        return true;    
    }else{
        std::cout << "Customer ID: " << name << " refused!" << std::endl;
        return false;
    }
}

/**
 * Function to check out customers at the end of day and push the now empty rooms back into the available stacks
 * Input: Current date, stack of available 1 bed rooms, stack of available 2 bed rooms, stack of available 3 bed rooms, 
 * vector of occupied rooms
 * Output: Number of rooms freed up after all checkouts for that day
*/
int freeRooms(tm time, LinkedStack<Room>& available1, LinkedStack<Room>& available2, LinkedStack<Room>& available3, std::vector<Room>& occupied){
    int noOfFreeRooms = 0;
    for(int i = 0; i < occupied.size(); i++){
        tm chkout = occupied[i].getCheckout();
        if(difftime(mktime(&time), mktime(&chkout)) > 0){
            if(occupied[i].getBeds() == 3){
                Room r(3);
                available3.push(r);
                r.addBeds(3);
            }else if(occupied[i].getBeds() == 2){
                Room r(2);
                available2.push(r);
                r.addBeds(2);
            }else{
                Room r(1);
                available1.push(r);
                r.addBeds(1);
            }
            occupied.erase(occupied.begin() + i);
            noOfFreeRooms++;
            i--;
        }
    }
    return noOfFreeRooms;
}

/**
 * Function to count the number of unique customers staying at the hotel
 * Input: Vector of occupied rooms
 * Output: Number of unique customers
*/
int countCust(std::vector<Room>& occupied){
    int count = 0;
    if(occupied.size() >= 1){
        count++;
        for(int i = 0; i < occupied.size() - 1; i++){
            int j = i + 1;
            if(occupied[i].getCustID().compare(occupied[j].getCustID()) == 0)
                count++;
        }
    }
    return count;
}

/**
 * Main driver of function, progresses through time day by day, assigning rooms then checking out customers at the end of day.
 * Prints a log.txt containing information on how many customers served, refused, no. of checkouts and no. of available rooms
 * post-checkout.
 * Input: Current date, queue of all bookings, stack of available 1 bed rooms, stack of available 2 bed rooms, stack of available
 * 3 bed rooms, vector of occupied rooms.
 * Output: log.txt file containing daily hotel information.
*/
void incrementTime(tm time, LinkedQueue<std::string>& bookings, LinkedStack<Room>& available1, LinkedStack<Room>& available2, LinkedStack<Room>& available3, std::vector<Room>& occupied){
    std::ofstream fout;
    fout.open("log.txt");
    int served = 0, refused = 0;
    while(!bookings.isEmpty()){
        tm bookingTime{};
        bookingTime = calcTime(bookings.front());
        if(difftime(mktime(&time), mktime(&bookingTime)) == 0){
            if(assignRoom(bookings.front(), available1, available2, available3, occupied)){
                served++;
            }else{
                refused++;
            }
            bookings.dequeue();
        }else{
            time.tm_mday += 1;
            int noOfCust = countCust(occupied);
            int noOfFreeRooms = freeRooms(time, available1, available2, available3, occupied);
            noOfCust = noOfCust - countCust(occupied);
            tm yday = time;
            yday.tm_mday -= 1;
            fout << asctime(&yday);
            fout << "No. of customers served: " << std::to_string(served) << "\n";
            fout << "No. of customers refused: " << std::to_string(refused) << "\n";
            fout << "No. of customers who checked out at the end of day: " << std::to_string(noOfCust) << "\n";
            fout << "No. of available rooms again at the end of day: " << std::to_string(noOfFreeRooms) << "\n";
            served = refused = 0;
        }
    }
    fout.close();
}



int main(){
    LinkedQueue<std::string> bookings = readFile("Customers.txt");
    LinkedStack<Room> availableRooms1;
    LinkedStack<Room> availableRooms2;
    LinkedStack<Room> availableRooms3;
    std::vector<Room> occupiedRooms;
    for(int i = 0; i < 100; i++){
        Room r(1);
        availableRooms1.push(r);
        r.addBeds(1);
    }
    for(int j = 0; j < 50; j++){
        Room r(2);
        availableRooms2.push(r);
        r.addBeds(2);
    }
    for(int k = 0; k < 30; k++){
        Room r(3);
        availableRooms3.push(r);
        r.addBeds(3);
    }

    tm time{};  // start date of first booking
    time.tm_mday = 1;
    time.tm_mon = 0;
    time.tm_year = 2018-1900;

    incrementTime(time, bookings, availableRooms1, availableRooms2, availableRooms3, occupiedRooms);


    return 0;
}