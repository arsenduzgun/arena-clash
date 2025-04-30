#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <algorithm>

#include "assassin.h"
#include "warrior.h"
#include "healer.h"
#include "fireMeteoriteArena.h"
#include "valhallaArena.h"

using namespace std;

string toLower(const string& str) {
    string lowered = str;
    transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
    return lowered;
}

unique_ptr<Unit> createUnit(const string& type, const string& teamName, int id) {
    string nickName;
    cout << "\nEnter a name for your " << type << ": ";
    getline(cin, nickName);

    if (type == "Assassin") return make_unique<Assassin>(nickName, type, teamName, id);
    if (type == "Warrior") return make_unique<Warrior>(nickName, type, teamName, id);
    if (type == "Healer") return make_unique<Healer>(nickName, type, teamName, id);

    return nullptr;
}

void chooseTeam(vector<unique_ptr<Unit>>& team, const string& teamName) {
    cout << "\nChoose units for " << teamName << ":\n";
    cout << "Options: Assassin | Warrior | Healer\n";

    int counter = 1;
    while (counter <= 3) {
        cout << "Choose unit " << counter << ": ";
        string input;
        getline(cin, input);

        string lowerInput = toLower(input);
        if (lowerInput == "assassin" || lowerInput == "warrior" || lowerInput == "healer") {
            unique_ptr<Unit> unit = createUnit(input, teamName, counter);
            team.push_back(move(unit));
            counter++;
        }
        else {
            cout << "Invalid unit type. Please enter Assassin, Warrior, or Healer.\n";
        }
    }
}

void buildTeams(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
    string teamName1, teamName2;

    cout << "Enter name for the first team: ";
    getline(cin, teamName1);
    chooseTeam(team1, teamName1);

    cout << "\nEnter name for the second team: ";
    getline(cin, teamName2);
    chooseTeam(team2, teamName2);
}

void selectArena(unique_ptr<Arena>& arena) {
    cout << "\nSelect Arena Type:\n";
    cout << "Options: Fire Meteorite Arena | Valhalla Arena\n";

    while (true) {
        cout << "Your choice: ";
        string input;
        getline(cin, input);
        string lowerInput = toLower(input);

        if (lowerInput == "fire meteorite arena") {
            arena = make_unique<FireMeteoriteArena>();
            break;
        }
        else if (lowerInput == "valhalla arena") {
            arena = make_unique<ValhallaArena>();
            break;
        }
        else {
            cout << "Invalid arena. Try again.\n";
        }
    }
}

void flipCoin(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2, unique_ptr<Arena>& arena) {
    cout << "\nFlipping coin...\n";
    this_thread::sleep_for(1s);
    srand(static_cast<unsigned>(time(nullptr)));

    int coin = rand() % 2;
    auto& startingTeam = (coin == 1) ? team1 : team2;
    auto& opponentTeam = (coin == 1) ? team2 : team1;

    cout << startingTeam[0]->getTeamName() << " will start the battle!\n";
    arena->battle(startingTeam, opponentTeam);
}

void displayInfo() {
    cout << R"(
----------------------------------------------------------
                  WELCOME TO THE ARENA CLASH!
----------------------------------------------------------

Game Overview:
- Two teams battle in an arena
- Choose from 3 unit types and 2 arena types

Units:
ASSASSIN
 - HP: 250
 - Attack: 30 - 40
 - Defence: 10 - 15
 - Special: Attacks all opponents (15% chance)

WARRIOR
 - HP: 200
 - Attack: 35 - 45
 - Defence: 10 - 15
 - Special: Critical attack (30% chance)

HEALER
 - HP: 250
 - Attack: 15 - 20
 - Defence: 15 - 20
 - Special: Heals teammates by 10% HP (15% chance)

Arenas:
FIRE METEORITE ARENA
 - 10% chance of meteorite hitting all units for 20 damage each round

VALHALLA ARENA
 - 5% chance to resurrect one dead unit with 20% HP each round
----------------------------------------------------------
)";
    this_thread::sleep_for(1s);
}

int main() {
    displayInfo();

    vector<unique_ptr<Unit>> team1;
    vector<unique_ptr<Unit>> team2;
    buildTeams(team1, team2);

    unique_ptr<Arena> arena;
    selectArena(arena);

    flipCoin(team1, team2, arena);

    return 0;
}
