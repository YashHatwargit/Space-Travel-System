#ifndef STS_classes_H
#define STS_classes_H

#include<string>
#include<vector>
#include<map>
using namespace std;

class Date {
    public:
    int day, month, year;

    Date();
    Date(int day, int month, int year);
    string getDate();
    bool operator==(const Date &date);
    int operator-(const Date &date);
};

class Planet {
    private:
    int x, y, z;
    string name;

    public:
    int id;
    static int uid;

    Planet();
    Planet(int x, int y, int z, string name);
    vector<int> getCoordinates();
    string getName();
    void viewPlanet();
};

class Traveller;

class Ticket {
    private:
    int price;

    public:
    int id;
    int srcPlanet, destPlanet;
    Date date;
    Traveller* traveller;
    static int uid;

    Ticket();
    Ticket(int srcPlanet, int destPlanet, Date date, Traveller* traveller);
    int getId();
    int getPrice();
    int calPrice();
    void setPrice(int price);
    void viewTicket();
    bool operator == (const Ticket &ticket);
};

class Traveller {
    public:
    string name;
    map<int, Ticket> tickets;
    int id;
    static int uid;

    Traveller();
    Traveller(string name);

    string getName();
    int getId();
    void bookTicket();
    void cancelTicket();
    void updateTicket();
    void viewTicket();
    void viewAllTickets();
};

class Passenger : public Traveller {
    public:
    Passenger();
    Passenger(string name);
    void showPassenger();
};

class Astronaut : public Traveller {
    public:
    int experience;

    Astronaut();
    Astronaut(string name);
    void showAstronaut();
};

class Commander : public Traveller {
    public:
    int experience, licenseId;

    Commander();
    Commander(string name);
    void showCommander();
};

class SpaceTravel {
    private:
    vector<int> passengersList;
    int astronaut;
    int commander;

    public:
    int id;
    static int uid;
    Date date;
    int srcPlanet, destPlanet;

    SpaceTravel();
    SpaceTravel(int srcPlanet, int destPlanet, Date date);
    void addPassenger(int id);
    void removePassenger(int id);
    void showTravellers();
    void getAstronaut(int id);
    void getCommander(int id);
    void setAstronaut(int id);
    void setCommander(int id);
    void showTravel();
};

void viewAllPlanets();

int findCommander(Ticket &ticket);

int findAstronaut(Ticket &ticket);

int findWaiting(Ticket &ticket);

int findTravel(Ticket &ticket);

void bookTravel(Ticket &ticket);

void showCommanders();

void showAstronauts();

void showWaitingList();

void showSpaceTravels();

#endif