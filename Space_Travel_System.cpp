#include<iostream>
#include "STS_classes.h"
using namespace std;

int Planet::uid = 0;
int Ticket::uid = 0;
int Traveller::uid = 0;
int SpaceTravel::uid = 0;

extern map<int, Planet> planets;
extern map<int, Passenger> passengers;
extern map<int, Astronaut> astronauts;
extern map<int, Commander> commanders;
extern map<int, SpaceTravel> spaceTravels;
extern map<int, Ticket> waitingList;

void createTravellers() {
    string name = "Passenger";
    for(int i=0;i<11;i++){
        string id = to_string(i+1).length() == 1 ? "0" + to_string(i+1) : to_string(i+1);
        Passenger passenger(name + id);
    }
    Astronaut astronaut1("Astronaut01");
    Astronaut astronaut2("Astronaut02");
    Commander commander1("Commander01");
    Commander commander2("Commander02");
}

void createPlanets() {
    Planet planet1(0, 0, 0, "Earth");
    Planet planet2(4, 7, 5, "Mars");
    Planet planet3(8, 2, 11, "Venus");
}

int main() {
    createTravellers();
    createPlanets();

    cout << "\n\tWelcome To CelestiaX Space Travel!\n";
    cout << "\tToday : 01/01/2030\n\n";

    int flag = 1;

    while(flag){
        cout<<"Enter your role : \n(1) Passenger\n(2) Astronaut\n(3) Commander\n(4) Exit"<<endl;
        int role;
        cin>>role;
        if(role == 1){
            int flag2 = 1;
            cout<<"Please Enter your UID : "<<endl;
            int id;
            cin>>id;
            if(passengers.find(id) == passengers.end()) {
                cout<<"Invalid Passenger UID. Please try again later!"<<endl;
                continue;
            }
            Passenger &passenger = passengers[id];
            while(flag2) {
                cout<<"What you would like to do?\n";
                cout<<"(1) Book Ticket\n(2) Cancel Ticket\n(3) Update Ticket\n(4) View All Tickets\n(5) View All Planets\n(6) View All Astronauts\n(7) View All Commanders\n(8) View Waiting List\n(9) Go back"<<endl;
                int option;
                cin>>option;
                switch (option) {
                    case 1: {
                        passenger.bookTicket();
                        break;
                    }
                    case 2: {
                        passenger.cancelTicket();
                        break;
                    }
                    case 3: {
                        passenger.updateTicket();
                        break;
                    }
                    case 4: {
                        passenger.viewAllTickets();
                        break;
                    }
                    case 5: {
                        viewAllPlanets();
                        break;
                    }
                    case 6: {
                        showAstronauts();
                        break;
                    }
                    case 7: {
                        showCommanders();
                        break;
                    }
                    case 8: {
                        showWaitingList();
                        break;
                    }
                    case 9: {
                        flag2 = 0;
                        break;
                    }
                    default: {
                        flag2 = 0;
                        cout<<"Please choose a valid option!"<<endl;
                        break;
                    }
                }
            }
        }
        else if(role == 2){
            int flag2 = 1;
            cout<<"Please Enter your UID : "<<endl;
            int id;
            cin>>id;
            if(astronauts.find(id) == astronauts.end()) {
                cout<<"Invalid Astronaut UID. Please try again later!"<<endl;
                continue;
            }
            Astronaut &astronaut = astronauts[id];
            while(flag2) {
                cout<<"What you would like to do?\n";
                cout<<"(1) View Ticket\n(2) View All Tickets\n(3) View Waiting List\n(4) Go back"<<endl;
                int option;
                cin>>option;
                switch (option) {
                    case 1: {
                        astronaut.viewTicket();
                        break;
                    }
                    case 2: {
                        astronaut.viewAllTickets();
                        break;
                    }
                    case 3: {
                        showWaitingList();
                        break;
                    }
                    case 4: {
                        flag2 = 0;
                        break;
                    }
                    default: {
                        cout<<"Please choose a valid option!"<<endl;
                        flag2 = 0;
                        break;
                    }
                }
            }
        }
        else if(role == 3){
            int flag2 = 1;
            cout<<"Please Enter your UID : "<<endl;
            int id;
            cin>>id;
            if(commanders.find(id) == commanders.end()) {
                cout<<"Invalid Commander UID. Please try again later!"<<endl;
                continue;
            }
            Commander &commander = commanders[id];
            while(flag2) {
                cout<<"What you would like to do?\n";
                cout<<"(1) View Ticket\n(2) View All Tickets\n(3) View Waiting List\n(4) View Upcoming Travels\n(5) Go back"<<endl;
                int option;
                cin>>option;
                switch (option) {
                    case 1: {
                        commander.viewTicket();
                        break;
                    }
                    case 2: {
                        commander.viewAllTickets();
                        break;
                    }
                    case 3: {
                        showWaitingList();
                        break;
                    }
                    case 4: {
                        showSpaceTravels();
                        break;
                    }
                    case 5: {
                        flag2 = 0;
                        break;
                    }
                    default: {
                        flag2 = 0;
                        cout<<"Please choose a valid option!"<<endl;
                        break;
                    }
                }
            }
        }
        else if(role == 4){
            cout<<"Thank you for your time at CelestiaX Space Travel. See you again!"<<endl;
            flag = 0;
        }
        else {
            cout<<"Please choose a valid option!"<<endl;
            flag = 0;
        }
    }

    return 0;
}