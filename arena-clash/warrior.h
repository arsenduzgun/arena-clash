#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include "Unit.h"
#include <thread>
#include <vector>

using namespace std;

class Warrior : public Unit {

protected:
	const int warriorHP = 200;
	const int warriorMaxAttackPoint = 45;
	const int warriorMinAttackPoint = 35;
	const int warriorMaxDefencePoint = 15;
	const int warriorMinDefencePoint = 10;
	const int warriorSpecialAbilityChance = 30;

public:

	Warrior(string nickName, string className, string teamName, int creationOrder) : Unit(nickName, className, teamName, creationOrder) {
		HP = warriorHP;
		maxHP = warriorHP;
		maxAttackPoint = warriorMaxAttackPoint;
		minAttackPoint = warriorMinAttackPoint;
		maxDefencePoint = warriorMaxDefencePoint;
		minDefencePoint = warriorMinDefencePoint;
		specialAbilityChance = warriorSpecialAbilityChance;
	}

	void attack(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam, unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) {
		int damage;
		if (isLucky(attacker)) {
			damage = attacker->getAttackPoint() * (100.0 / (100 + defender->getDefencePoint())) * 2;
			defender->setHP(defender->getHP() - damage);
			cout << "\n" << attacker->getNickName() << " deals " << damage << " damage(critical) to " << defender->getNickName() << endl;
			if (!isAlive(defender)) {
				cout << "\n" << defender->getNickName() << " is dead" << endl;
				defender->setHP(0); // If defenders HP drops below 0, this function sets defenders HP to 0 
			}
			else if (isAlive(defender)) {
				cout << "\n" << defender->getNickName() << " has remaining " << defender->getHP() << " HP" << endl;
			}
		}
		else {
			damage = attacker->getAttackPoint() * (100.0 / (100 + defender->getDefencePoint()));
			defender->setHP(defender->getHP() - damage);
			cout << "\n" << attacker->getNickName() << " deals " << damage << " damage to " << defender->getNickName() << endl;
			if (!isAlive(defender)) {
				cout << "\n" << defender->getNickName() << " is dead" << endl;
				defender->setHP(0);
			}
			else if (isAlive(defender)) {
				cout << "\n" << defender->getNickName() << " has remaining " << defender->getHP() << " HP" << endl;
			}
		}
	}

	void specialSkill(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam, unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) {}
};

#endif