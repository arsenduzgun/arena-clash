#include <iostream> 
#include "assassin.h"
#include "warrior.h"
#include "healer.h"
#include "fireMeteoriteArena.h"
#include "valhallaArena.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

void buildTeams(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
	string teamName;
	int counter = 1;
	string input;
	string nickName;
	cout << "\nPlease enter the first team name: ";
	getline(cin, teamName);
	cout << "\nChoose units of " << teamName << endl;
	cout << "\nPlease type and enter Assassin to choose a Assassin" << endl;
	cout << "\nPlease type and enter Warrior to choose a Warrior" << endl;
	cout << "\nPlease type and enter Healer to choose a Healer" << endl;
	while (counter != 4) {
		cout << "\nChoose your unit " << counter << ": ";
		getline(cin, input);
		if (input._Equal("Assassin")) {
			cout << "\nPlease enter your Assassin name: ";
			getline(cin, nickName);
			unique_ptr<Unit> assassin(new Assassin(nickName, "Assassin", teamName, counter));
			team1.push_back(move(assassin));
		}
		else if (input._Equal("Warrior")) {
			cout << "\nPlease enter your Warrior name: ";
			getline(cin, nickName);
			unique_ptr<Unit> warrior(new Warrior(nickName, "Warrior", teamName, counter));
			team1.push_back(move(warrior));
		}
		else if (input._Equal("Healer")) {
			cout << "\nPlease enter your Healer name: ";
			getline(cin, nickName);
			unique_ptr<Unit> healer(new Healer(nickName, "Healer", teamName, counter));
			team1.push_back(move(healer));
		}
		else {
			cout << "\nYou have entered an invalid value, please enter again" << endl;
			continue;
		}
		counter++;
	}
	counter = 1;
	cout << "\nPlease enter the second team name: ";
	getline(cin, teamName);
	cout << "\nChoose units of " << teamName << "\n";
	while (counter != 4) {
		cout << "\nChoose your unit " << counter << ": ";
		getline(cin, input);
		if (input._Equal("Assassin")) {
			cout << "\nPlease enter your Assassin name: ";
			getline(cin, nickName);
			unique_ptr<Unit> assassin(new Assassin(nickName, "Assassin", teamName, counter));
			team2.push_back(move(assassin));
		}
		else if (input._Equal("Warrior")) {
			cout << "\nPlease enter your Warrior name: ";
			getline(cin, nickName);
			unique_ptr<Unit> warrior(new Warrior(nickName, "Warrior", teamName, counter));
			team2.push_back(move(warrior));
		}
		else if (input._Equal("Healer")) {
			cout << "\nPlease enter your Healer name: ";
			getline(cin, nickName);
			unique_ptr<Unit> healer(new Healer(nickName, "Healer", teamName, counter));
			team2.push_back(move(healer));
		}
		else {
			cout << "\nYou have entered an invalid value, please enter again" << endl;
			continue;
		}
		counter++;
	}
}

void selectArena(unique_ptr<Arena>& arena) {
	bool selectArena = false;
	cout << "\nPlease select the Arena type" << endl;
	string input;
	cout << "\nPlease type and enter Fire Meteorite Arena to select Fire Meteorite Arena" << endl;
	cout << "\nPlease type and enter Valhalla Arena to select Valhalla Arena" << endl;
	while (!selectArena) {
		cout << "\nChoose your Arena type: ";
		getline(cin, input);
		if (input._Equal("Fire Meteorite Arena")) {
			unique_ptr<Arena> fireMeteoriteArena(new FireMeteoriteArena());
			arena = move(fireMeteoriteArena);
		}
		else if (input._Equal("Valhalla Arena")) {
			unique_ptr<Arena> valhallaArena(new ValhallaArena());
			arena = move(valhallaArena);
		}
		else {
			cout << "\nYou have entered an invalid value, please enter again" << endl;
			continue;
		}
		selectArena = true;
	}
}

void flipCoin(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2, unique_ptr<Arena>& arena) {
	cout << "\nCoin flipping...\n" << endl;
	this_thread::sleep_for(1s);
	srand(time(NULL));
	int toss_A_Coin = rand() % 2;
	if (toss_A_Coin == 1) {
		cout << team1[0]->getTeamName() << " will start the battle" << endl;
		arena->battle(team1, team2);
	}
	else {
		cout << team2[0]->getTeamName() << " will start the battle" << endl;
		arena->battle(team2, team1);
	}
}

void info() {
	cout << "\t\t\t\t\t-----WELCOME TO THE ARENA CLASH!-----" << endl;
	cout << "\nThis game is designed for battle of 2 teams in arena mode" << endl;
	cout << "\nThere are 3 units and 2 arenas you can choose with different speciality" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n\t\t\t\t\t\tASSASSIN" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nHP: 250" << endl;
	cout << "\nAttack Point: 30 - 40" << endl;
	cout << "\nDefence Point: 10 - 15" << endl;
	cout << "\nSpecial Ability: Attack to all opponents" << endl;
	cout << "\nSpecial Ability Chance: %15" << endl;
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n\t\t\t\t\t\tWARRIOR" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nHP : 200" << endl;
	cout << "\nAttack Point: 35 - 45" << endl;
	cout << "\nDefence Point: 10 - 15" << endl;
	cout << "\nSpecial Ability: Critical attack" << endl;
	cout << "\nSpecial Ability Chance: %30" << endl;
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n\t\t\t\t\t\tHEALER" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nHP: 250" << endl;
	cout << "\nAttack Point: 15 - 20" << endl;
	cout << "\nDefence Point: 15 - 20" << endl;
	cout << "\nSpecial Ability: Healing teammates by their %10 HP(cannot be applied on dead teammates)" << endl;
	cout << "\nSpecial Ability Chance: %15" << endl;
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n\t\t\t\t\t\tFIRE METEORITE ARENA" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nFire Meteorite Arena: Fire meteorite attack(20 pure damage) each unit on the field after each round" << endl;
	cout << "\nFire Meteorite Chance: %10" << endl;
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n\t\t\t\t\t\tVALHALLA ARENA" << endl;
	this_thread::sleep_for(0.5s);
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nValhalla Arena: Resurrecting the dead units with %20 of their HP after each round" << endl;
	cout << "\nResurrection Chance: %5" << endl;
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	this_thread::sleep_for(0.5s);
}

int main() {
	//info();
	vector<unique_ptr<Unit>> team1;
	vector<unique_ptr<Unit>> team2;
	buildTeams(team1, team2);
	unique_ptr<Arena> arena;
	selectArena(arena);
	flipCoin(team1, team2, arena);
	return 0;
}