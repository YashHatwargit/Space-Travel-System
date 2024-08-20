#ifndef STS_classes_CPP
#define STS_classes_CPP

#include<iostream>
#include<math.h>
#include<cstdlib>
#include<algorithm>
#include "STS_classes.h"
using namespace std;

map<int, Planet> planets;
map<int, Passenger> passengers;
map<int, Astronaut> astronauts;
map<int, Commander> commanders;
map<int, SpaceTravel> spaceTravels;
map<int, Ticket> waitingList;

Date::Date() {}

Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

string Date::getDate() {
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

bool Date::operator==(const Date &date){
    return this->day == date.day && this->month == date.month && this->year == date.year;
}

int Date::operator-(const Date &date) {
    int days = ((this->year - date.year) * 360 + (this->month - date.month) * 30 + (this->day - date.day));
    return days;
}

Planet::Planet() {}

Planet::Planet(int x, int y, int z, string name) : Planet() {
    uid++;
    this->id = uid;
    this->x = x;
    this->y = y;
    this->z = z;
    this->name = name;
    planets[id] = *this;
}

vector<int> Planet::getCoordinates() {
    return {x, y, z};
}

string Planet::getName() {
    return name;
}

void Planet::viewPlanet() {
    cout<<"********************"<<endl;
    cout<<"ID of planet : "<<id<<endl;
    cout<<"Name of planet : "<<name<<endl;
    cout<<"Planet Coordiantes : {"<<x<<", "<<y<<", "<<z<<"}"<<endl;
    cout<<"********************"<<endl;
}

Ticket::Ticket() {}

Ticket::Ticket(int srcPlanet, int destPlanet, Date date, Traveller* traveller) : Ticket() {
    uid++;
    this->id = uid;
    this->srcPlanet = srcPlanet;
    this->destPlanet = destPlanet;
    this->date = date;
    this->traveller = traveller;
    this->price = calPrice();
}

int Ticket::calPrice() {
    int x1 = planets[srcPlanet].getCoordinates()[0];
    int y1 = planets[srcPlanet].getCoordinates()[1];
    int z1 = planets[srcPlanet].getCoordinates()[2];
    int x2 = planets[destPlanet].getCoordinates()[0];
    int y2 = planets[destPlanet].getCoordinates()[1];
    int z2 = planets[destPlanet].getCoordinates()[2];
    
    int distance = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
    distance = sqrt(distance);
    return distance * 100;
}

int Ticket::getId() {
    return id;
}

int Ticket::getPrice() {
    return price;
}

void Ticket::setPrice(int price) {
    this->price = price;
}

void Ticket::viewTicket() {
    cout<<endl;
    cout<<"**************************"<<endl;
    cout<<"ID of ticket : "<<id<<endl;
    cout<<"Traveller : "<<(*traveller).name<<endl;
    cout<<"Source Planet : "<<planets[srcPlanet].getName()<<endl;
    cout<<"Destination Planet : "<<planets[destPlanet].getName()<<endl;
    cout<<"Price of ticket : "<<this->getPrice()<<endl;
    cout<<"Travel Date : "<<date.getDate()<<endl;
    cout<<"**************************"<<endl;
    cout<<endl;
}

bool Ticket::operator==(const Ticket &ticket) {
    return (this->srcPlanet == ticket.srcPlanet &&
    this->destPlanet == ticket.destPlanet &&
    this->date == ticket.date);
}

Traveller::Traveller() {}

Traveller::Traveller(string name) : Traveller() {
    uid++;
    this->id = uid;
    this->name = name;
    this->tickets = {};
}

string Traveller::getName() {
    return name;
}

int Traveller::getId() {
    return id;
}

void Traveller::viewTicket() {
    cout<<"Enter UID of ticket to view : "<<flush;
    int id;
    cin>>id;
    if(tickets.find(id) == tickets.end()) {
        cout<<"Sorry, You have no ticket with UID "<<id<<endl;
    }
    else {
        Ticket ticket = tickets[id];
        ticket.viewTicket();
    }
}

void Traveller::viewAllTickets() {
    if(tickets.empty()){
        cout<<"Sorry, you do not have any tickets"<<endl;
        return;
    }
    for(auto &ticket : tickets) {
        ticket.second.viewTicket();
    }
}

void Traveller::cancelTicket() {
    cout<<"Enter UID of your ticket to cancel : "<<flush;
    int id;
    cin>>id;
    if(tickets.find(id) == tickets.end()) {
        cout<<"Sorry, You have no ticket with UID "<<id<<endl;
    }
    else{
        tickets.erase(id);
        cout<<"Your ticket has been cancelled successfully"<<endl;
    }
}

void Traveller::bookTicket() {
    Date today(1, 1, 2023);
    int day, month, year, src, dest;
    cout<<"Enter date of journey in dd mm yyyy format : "<<flush;
    cin>>day>>month>>year;
    Date date(day, month, year);
    if(date - today > 3600){
        cout<<"Sorry, only tickets upto 10 years are allowed. Please try again later."<<endl;
        return ;
    }
    else if(date - today <= 0){
        cout<<"Invalid date! Enter a future date!"<<endl;
        return ;
    }
    cout<<"Enter UID of source planet : "<<flush;
    cin>>src;
    if(planets.find(src) == planets.end()) {
        cout<<"Invalid UID of source planet. Please try again later."<<endl;
        return ;
    }
    cout<<"Enter UID of destination planet : "<<flush;
    cin>>dest;
    if(planets.find(dest) == planets.end()) {
        cout<<"Invalid UID of destination planet. Please try again later."<<endl;
        return ;
    }

    Traveller *traveller = new Traveller();
    *traveller = *this;
    Ticket ticket(src, dest, date, traveller);
    tickets[ticket.getId()] = ticket;

    cout<<"Ticket booked successfully!"<<endl;
    ticket.viewTicket();

    bookTravel(ticket);

    cout<<"Do you want to book a return ticket? (yes/no)"<<endl;

    string bookReturn;
    cin>>bookReturn;
    
    if(bookReturn == "yes") {
        // Booking the Return Ticket
        cout<<"Enter date of return in dd mm yyyy format : "<<flush;
        cin>>day>>month>>year;
        Date returnDate(day, month, year);
        Ticket returnTicket(dest, src, returnDate, this);
        tickets[returnTicket.getId()] = returnTicket;

        cout<<"Return Ticket booked successfully!"<<endl;
    }
    
    cout<<"Have a nice Journey!"<<endl;
}

void Traveller::updateTicket() {
    cout<<"Enter UID of your ticket to update : "<<flush;
    int id;
    cin>>id;
    if(tickets.find(id) == tickets.end()) {
        cout<<"Sorry, You have no ticket with UID "<<id<<endl;
    }
    else{
        cout<<"Enter new Date of Journey in dd mm yyyyy format : "<<flush;
        int day, month, year, dest;
        cin>>day>>month>>year;
        Date date(day, month, year);
        cout<<"Enter UID of destination Planet : "<<flush;
        cin>>dest;
        if(planets.find(dest) == planets.end()) {
            cout<<"Invalid UID of destination planet. Please try again later."<<endl;
            return ;
        }

        Ticket &ticket = tickets[id];
        ticket.date = date;
        ticket.destPlanet = dest;
        tickets[id] = ticket;

        cout<<"Ticket updated successfully!"<<endl;
    }
}

Passenger::Passenger() : Traveller() {}

Passenger::Passenger(string name) : Traveller(name) {
    passengers[id] = *this;
}

void Passenger::showPassenger() {
    cout<<"**********************"<<endl;
    cout<<"Passenger ID : "<<id<<endl;
    cout<<"Passenger name : "<<name<<endl;
    cout<<"**********************"<<endl;
}

Astronaut::Astronaut() : Traveller() {
    this->experience = rand() % 10 + 2;
}

Astronaut::Astronaut(string name) : Traveller(name) {
    this->experience = rand() % 10 + 2;
    astronauts[id] = *this;
}

void Astronaut::showAstronaut() {
    cout<<"**********************"<<endl;
    cout<<"Astronaut ID : "<<id<<endl;
    cout<<"Astronaut name : "<<name<<endl;
    cout<<"Experience : "<<experience<<" Years"<<endl;
    cout<<"**********************"<<endl;
}

Commander::Commander() : Traveller() {
    this->experience = rand() % 10 + 2;
    this->licenseId = rand() + 1;
}

Commander::Commander(string name) : Traveller(name) {
    this->experience = rand() % 10 + 2;
    this->licenseId = rand() + 1;
    commanders[id] = *this;
}

void Commander::showCommander() {
    cout<<"**********************"<<endl;
    cout<<"Commander ID : "<<id<<endl;
    cout<<"Commander Name : "<<name<<endl;
    cout<<"License Id: " << licenseId<<endl;
    cout<<"Experience :" << experience <<" Years" << endl;
    cout<<"**********************"<<endl;
}

SpaceTravel::SpaceTravel() {}

SpaceTravel::SpaceTravel(int srcPlanet, int destPlanet, Date date) : SpaceTravel() {
    uid++;
    this->id = uid;
    this->srcPlanet = srcPlanet;
    this->destPlanet = destPlanet;
    this->date = date;
    spaceTravels[id] = *this;
}

void SpaceTravel::addPassenger(int id) {
    vector<int>::iterator index = find(passengersList.begin(), passengersList.end(), id);
    if(index != passengersList.end()) {
        cout<<"Passenger with UID "<<id<<" already exists in this Space Travel!"<<endl;
    }
    else{
        passengersList.push_back(id);
        cout<<"Successfully added the Passenger!"<<endl;
    }
}

void SpaceTravel::removePassenger(int id) {
    vector<int>::iterator index = find(passengersList.begin(), passengersList.end(), id);
    if(index == passengersList.end()) {
        cout<<"No Passenger with UID "<<id<<" exists in this Space Travel!"<<endl;
    }
    else{
        passengersList.erase(index);
        cout<<"Successfully removed the Passenger!"<<endl;
    }
}

void SpaceTravel::showTravellers() {
    cout<<"Commander details : "<<endl;
    commanders[commander].showCommander();
    cout<<endl;
    cout<<"Astronaut details : "<<endl;
    astronauts[astronaut].showAstronaut();
    cout<<endl;
    cout<<"Passengers details : "<<endl;
    for(auto passenger : passengersList){
        passengers[passenger].showPassenger();
        cout<<endl;
    }
}

void SpaceTravel::getAstronaut(int id) {
    astronauts[id].showAstronaut();
}

void SpaceTravel::getCommander(int id) {
    commanders[id].showCommander();
}

void SpaceTravel::setAstronaut(int id) {
    astronaut = id;
}

void SpaceTravel::setCommander(int id) {
    commander = id;
}

void SpaceTravel::showTravel() {
    if(passengersList.empty()){
        cout<<"No Space Travel!"<<endl;
        return;
    }
    cout<<"********************************"<<endl;
    cout<<"Space Travel ID : "<<id<<endl;
    cout<<"Source Planet : "<<planets[srcPlanet].getName()<<endl;
    cout<<"Destination Planet : "<<planets[destPlanet].getName()<<endl;
    cout<<"Travel Date : "<<date.getDate()<<endl;
    cout<<"Commander : "<<commanders[commander].getName()<<endl;
    cout<<"Astronaut : "<<astronauts[astronaut].getName()<<endl;
    cout<<"Number of Passengers : "<<passengersList.size()<<endl;
    cout<<"********************************"<<endl;
    cout<<endl;
}

void viewAllPlanets() {
    cout<<"*************************"<<endl;
    for(auto planet : planets) {
        planet.second.viewPlanet();
        cout<<endl;
    }
    cout<<"*************************"<<endl;
}

int findCommander(Ticket &ticket) {
    for(auto &commander : commanders) {
        int found = 1;
        for(auto &commanderTicket : commander.second.tickets) {
            if(commanderTicket.second.date == ticket.date) found = 0;
        }
        if(found){
            return commander.first;
        }
    }
    return -1;
}

int findAstronaut(Ticket &ticket) {
    for(auto &astronaut : astronauts) {
        int found = 1;
        for(auto &astronautTicket : astronaut.second.tickets) {
            if(astronautTicket.second.date == ticket.date) found = 0;
        }
        if(found){
            return astronaut.first;
        }
    }
    return -1;
}

int findWaiting(Ticket &ticket) {
    for(auto &waiting : waitingList) {
        if(waiting.second.srcPlanet == ticket.srcPlanet && waiting.second.destPlanet == ticket.destPlanet && waiting.second.date == ticket.date) {
            return waiting.first;
        }
    }
    return -1;
}

int findTravel(Ticket &ticket) {
    for(auto &spaceTravel : spaceTravels) {
        if(spaceTravel.second.srcPlanet == ticket.srcPlanet && spaceTravel.second.destPlanet == ticket.destPlanet && spaceTravel.second.date == ticket.date) {
            return spaceTravel.first;
        }
    }
    return -1;
}

void bookTravel(Ticket &ticket) {
    int travelId = findTravel(ticket);
    if(travelId != -1) {
        SpaceTravel &spaceTravel = spaceTravels[travelId];
        spaceTravel.addPassenger(ticket.traveller->id);
        cout<<"Your Space Travel is successfully booked with UID "<<travelId<<endl;
        cout<<endl;
        cout<<"Your Space Travel details : "<<endl;
        spaceTravel.showTravel();
        return ;
    }

    int waitingId = findWaiting(ticket);
    int commanderId = findCommander(ticket);
    int astronautId = findAstronaut(ticket);

    cout<<"Waiting Id : "<<waitingId<<endl;
    cout<<"Commander Id : "<<commanderId<<endl;
    cout<<"Astronaut Id : "<<astronautId<<endl;

    if(waitingId == -1 || commanderId == -1 || astronautId == -1) {
        waitingList[ticket.id] = ticket;
        cout<<"Your ticket has been added to waiting List. We will confirm your Space Travel when there is atleast one passenger with same Ticket."<<endl;
        return ;
    }
    else {
        Commander &commander = commanders[commanderId];
        Astronaut &astronaut = astronauts[astronautId];
        Ticket commanderTicket(ticket.srcPlanet, ticket.destPlanet, ticket.date, &commander);
        Ticket astronautTicket(ticket.srcPlanet, ticket.destPlanet, ticket.date, &astronaut);
        commander.tickets[commanderTicket.id] = commanderTicket;
        astronaut.tickets[astronautTicket.id] = astronautTicket;

        SpaceTravel spaceTravel(ticket.srcPlanet, ticket.destPlanet, ticket.date);
        spaceTravel.addPassenger(ticket.traveller->id);
        spaceTravel.addPassenger(waitingList[waitingId].traveller->id);
        spaceTravel.setAstronaut(astronautId);
        spaceTravel.setCommander(commanderId);
        waitingList.erase(waitingId);
        spaceTravels[spaceTravel.id] = spaceTravel;
        cout<<"Your SpaceTravel is successfully booked with UID "<<spaceTravel.id<<endl;
        cout<<endl;
        spaceTravel.showTravel();
    }
}

void showCommanders() {
    for(auto &commander : commanders) {
        commander.second.showCommander();
    }
}

void showAstronauts() {
    for(auto &astronaut : astronauts) {
        astronaut.second.showAstronaut();
    }
}

void showWaitingList() {
    if(waitingList.empty()) {
        cout<<"No one in Waiting List!"<<endl;
        return;
    }
    for(auto &waiting : waitingList) {
        waiting.second.viewTicket();
    }
}

void showSpaceTravels() {
    for(auto &spaceTravel : spaceTravels) {
        spaceTravel.second.showTravel();
    }
}

#endif