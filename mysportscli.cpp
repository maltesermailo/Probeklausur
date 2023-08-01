#include "mysportscli.h"
#include "mysports.h"

#include <iostream>


using namespace std;

//Global object
MySports mySports;

void athleteAnlegen() {
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    cin.clear();

    std::string Name;
    int Id;
    double time;
    char type;

    std::string input;

    cout << "Name: ";
    std::getline(cin, Name);

    cout << "(R)unner oder (S)wimmer";
    cin >> type;

    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    cin.clear();

    cout << "Start ID (> 100000): ";
    std::getline(cin, input);

    try {
        Id = stoi(input);

        if(Id < 100000) {
            cout << "Start ID ist kleiner als 100000!" << endl;
            return;
        }
    } catch(std::invalid_argument& e) {
        cout << "Start ID ist keine Nummer!" << endl;
        return;
    }

    cout << "Bestzeit (s.ms): ";
    std::getline(cin, input);

    try {
        time = stod(input);
    } catch(std::invalid_argument& e) {
        cout << "Bestzeit ist keine Nummer!" << endl;
        return;
    }

    if(mySports.getAthlete(Id) != nullptr) {
        cout << "Athlete mit der ID " << Id << " existiert bereits!" << endl;
        return;
    }

    if(type == 'r' || type == 'R') {
        mySports.addRunner(Name, Id, time);

        cout << "Runner angelegt." << endl;
    } else {
        mySports.addSwimmer(Name, Id, time);

        cout << "Swimmer angelegt" << endl;
    }
}

void athleteZuordnen() {
    int id;

    cout << "ID: " << endl;
    cin >> id;

    Athlete* athlete = mySports.getAthlete(id);

    if(athlete == nullptr) {
        cout << "ID " << id << " existiert nicht!";
        return;
    }

    int license;

    cout << "Trainer License: " << endl;
    cin >> license;

    Trainer* trainer = mySports.getTrainer(license);

    if(trainer == nullptr) {
        cout << "Trainer " << id << " existiert nicht!";
        return;
    }

    if(dynamic_cast<Swimmer*>(athlete) != nullptr) {
        Swimmer* swimmer = dynamic_cast<Swimmer*>(athlete);

        swimmer->setTrainer(trainer);
    } else if (dynamic_cast<Runner*>(athlete) != nullptr) {
        Runner* runner = dynamic_cast<Runner*>(athlete);

        runner->setTrainer(trainer);
    }

    trainer->addAthlete(athlete);

    cout << "Der Athlet mit der ID " << id << " wurde dem Trainer mit der Lizenz " << license << " zugeordnet." << endl;
}

void athleteAusgeben() {
    int id;

    cout << "ID: " << endl;
    cin >> id;

    Athlete* athlete = mySports.getAthlete(id);

    if(athlete == nullptr) {
        cout << "ID " << id << " existiert nicht!";
        return;
    }

    if(dynamic_cast<Swimmer*>(athlete) != nullptr) {
        Swimmer* swimmer = dynamic_cast<Swimmer*>(athlete);

        cout << "-- Swimmer " << swimmer->GetStartId() << " --" << endl;
        cout << "Name = " << swimmer->GetName() << endl;
        cout << "Bestzeit = " << swimmer->getTime() << " s" << endl;

        if(swimmer->getTrainer() != nullptr) {
            cout << "Trainer-Lizenz = " << swimmer->getTrainer()->getLicense() << endl;
            cout << "Trainer-Name = " << swimmer->getTrainer()->getName() << endl;
        }
    } else if (dynamic_cast<Runner*>(athlete) != nullptr) {
        Runner* runner = dynamic_cast<Runner*>(athlete);

        cout << "-- Runner " << runner->GetStartId() << " --" << endl;
        cout << "Name = " << runner->GetName() << endl;
        cout << "Bestzeit = " << runner->getTime() << " s" << endl;

        if(runner->getTrainer() != nullptr) {
            cout << "Trainer-Lizenz = " << runner->getTrainer()->getLicense() << endl;
            cout << "Trainer-Name = " << runner->getTrainer()->getName() << endl;
        }
    }
}

void athletesAusgeben() {
    std::cout << "**** Liste aller Athlete ****" << endl;

    for(std::vector<Athlete*>::iterator it = mySports.getAthletes().begin(); it != mySports.getAthletes().end(); it++) {
        Athlete* athlete = (*it);

        if(dynamic_cast<Swimmer*>(athlete) != nullptr) {
            Swimmer* swimmer = dynamic_cast<Swimmer*>(athlete);

            cout << "-- Swimmer " << swimmer->GetStartId() << " --" << endl;
            cout << "Name = " << swimmer->GetName() << endl;
            cout << "Bestzeit = " << swimmer->getTime() << " s" << endl;

            if(swimmer->getTrainer() != nullptr) {
                cout << "Trainer-Lizenz = " << swimmer->getTrainer()->getLicense() << endl;
                cout << "Trainer-Name = " << swimmer->getTrainer()->getName() << endl;
            }
        } else if (dynamic_cast<Runner*>(athlete) != nullptr) {
            Runner* runner = dynamic_cast<Runner*>(athlete);

            cout << "-- Runner " << runner->GetStartId() << " --" << endl;
            cout << "Name = " << runner->GetName() << endl;
            cout << "Bestzeit = " << runner->getTime() << " s" << endl;

            if(runner->getTrainer() != nullptr) {
                cout << "Trainer-Lizenz = " << runner->getTrainer()->getLicense() << endl;
                cout << "Trainer-Name = " << runner->getTrainer()->getName() << endl;
            }
        }
    }
}

void athleteMenu() {
    char auswahl;

    cout << "--- mySports - Athlete ---\n" << endl;
    cout << "(a) Athlet anlegen" << endl <<
        "(b) Athlet zuordnen " << endl <<
        "(c) Athlet (einzeln) ausgeben " << endl <<
        "(d) Athlet (alle) ausgeben " << endl <<
        "(x) Zurück zum Hauptmenü" << endl;

    do {
        cout << ">> ";
        cin >> auswahl;

        switch(auswahl) {
        case 'a':
        {
            athleteAnlegen();
            break;
        }
        case 'b':
        {
            athleteZuordnen();
            break;
        }
        case 'c':
        {
            athleteAusgeben();
            break;
        }
        case 'd':
        {
            athletesAusgeben();
            break;
        }
        case 'x':
        {
            return;
        }
        default: {
            continue;
        }
        }
    } while(true);
}

void trainerAnlegen() {
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    cin.clear();

    std::string Name;
    int License;

    std::string input;

    cout << "Name: ";
    std::getline(cin, Name);

    cout << "License (> 90000): ";
    std::getline(cin, input);

    try {
        License = stoi(input);

        if(License < 90000) {
            cout << "License ist kleiner als 90000!" << endl;
            return;
        }
    } catch(std::invalid_argument& e) {
        cout << "License ist keine Nummer!" << endl;
        return;
    }

    if(mySports.getTrainer(License) != nullptr) {
        cout << "Trainer mit der Lizenz " << License << " existiert bereits!" << endl;
        return;
    }

    mySports.addTrainer(Name, License);

    cout << "Trainer angelegt." << endl;
}

void trainerZuordnen() {
    int id;

    cout << "ID des Athleten: " << endl;
    cin >> id;

    Athlete* athlete = mySports.getAthlete(id);

    if(athlete == nullptr) {
        cout << "ID " << id << " existiert nicht!";
        return;
    }

    int license;

    cout << "Trainer License: " << endl;
    cin >> license;

    Trainer* trainer = mySports.getTrainer(license);

    if(trainer == nullptr) {
        cout << "Trainer " << id << " existiert nicht!";
        return;
    }

    if(dynamic_cast<Swimmer*>(athlete) != nullptr) {
        Swimmer* swimmer = dynamic_cast<Swimmer*>(athlete);

        swimmer->setTrainer(trainer);
    } else if (dynamic_cast<Runner*>(athlete) != nullptr) {
        Runner* runner = dynamic_cast<Runner*>(athlete);

        runner->setTrainer(trainer);
    }

    trainer->addAthlete(athlete);

    cout << "Der Athlet mit der ID " << id << " wurde dem Trainer mit der Lizenz " << license << " zugeordnet." << endl;
}

void trainerAusgeben() {
    int id;

    cout << "License: " << endl;
    cin >> id;

    Trainer* trainer = mySports.getTrainer(id);

    if(trainer == nullptr) {
        cout << "Lizenz " << id << " existiert nicht!";
        return;
    }

    cout << "-- Trainer " << trainer->getLicense() << " --" << endl;
    cout << "Name = " << trainer->getName() << endl;
}

void trainersAusgeben() {
    std::cout << "**** Liste aller Trainer ****" << endl;

    std::vector<Trainer *>::iterator it;
    for(it = mySports.getTrainers().begin(); it != mySports.getTrainers().end(); it++) {
        Trainer* trainer = (*it);

        cout << "-- Trainer " << trainer->getLicense() << " --" << endl;
        cout << "Name = " << trainer->getName() << endl;
    }
}

void trainerMenu() {
    char auswahl;

    cout << "--- mySports - Trainer ---\n" << endl;
    cout << "(a) Trainer anlegen" << endl <<
        "(b) Trainer zuordnen " << endl <<
        "(c) Trainer (einzeln) ausgeben " << endl <<
        "(d) Trainer (alle) ausgeben " << endl <<
        "(x) Zurück zum Hauptmenü" << endl;

        do {
        cout << ">> ";
        cin >> auswahl;

        switch(auswahl) {
        case 'a':
        {
            trainerAnlegen();
            break;
        }
        case 'b':
        {
            trainerZuordnen();
            break;
        }
        case 'c':
        {
            trainerAusgeben();
            break;
        }
        case 'd':
        {
            trainersAusgeben();
            break;
        }
        case 'x':
        {
            return;
        }
        default: {
            continue;
        }
        }
    } while(true);
}

void openCLI()
{

    int auswahl;

    cout << "--- mySports ---\n" << endl;
    cout << "(1) Athlet " << endl <<
        "(2) Trainer " << endl <<
        "(0) Beenden" << endl;

    do {
        cout << ">> ";
        cin >> auswahl;

        switch(auswahl) {
        case 1:
        {
            athleteMenu();
            break;
        }
        case 2:
        {
            trainerMenu();
            break;
        }
        case 0:
        {
            return;
        }
        default: {
            continue;
        }
        }
    } while(true);

}
