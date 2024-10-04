#ifndef ASSASSIN_H
#define ASSASSIN_H

#include <iostream>
#include "Unit.h"
#include <thread>
#include <vector>

using namespace std;

class Assassin : public Unit {

protected:

	const int assassinHP = 250;
	const int assassinMaxAttackPoint = 40;
	const int assassinMinAttackPoint = 30;
	const int assassinMaxDefencePoint = 15;
	const int assassinMinDefencePoint = 10;
	const int assassinSpecialAbilityChance = 15;

public:

	Assassin(string nickName, string className, string teamName, int creationOrder) : Unit(nickName, className, teamName, creationOrder) {
		HP = assassinHP;
		maxHP = assassinHP;
		maxAttackPoint = assassinMaxAttackPoint;
		minAttackPoint = assassinMinAttackPoint;
		maxDefencePoint = assassinMaxDefencePoint;
		minDefencePoint = assassinMinDefencePoint;
		specialAbilityChance = assassinSpecialAbilityChance;
	}

	void attack(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam, unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) {
		int damage = attacker->getAttackPoint() * (100.0 / (100 + defender->getDefencePoint()));
		defender->setHP(defender->getHP() - damage);
		cout << "\n" << attacker->getNickName() << " deals " << damage << " damage to " << defender->getNickName() << endl;
		if (!isAlive(defender)) {
			cout << "\n" << defender->getNickName() << " is dead" << endl;
			defender->setHP(0);
		}
		else if (isAlive(defender)) {
			cout << "\n" << defender->getNickName() << " has remaining " << defender->getHP() << " HP" << endl;
		}
		specialSkill(attackersTeam, defendersTeam, attacker, defender);
	}

	void specialSkill(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam, unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) {
		if (isAlive(attacker) && isTeamAlive(defendersTeam)) {
			cout << "\n" << attacker->getNickName() << " tries to perform throwing knife attack" << endl;
			this_thread::sleep_for(1s);
			if (isLucky(attacker)) {
				cout << "\n" << attacker->getNickName() << " is succeed to perform throwing knife attack" << endl;
				int damage;
				for (unique_ptr<Unit>& unit : defendersTeam) {
					if (isAlive(unit)) {
						damage = attacker->getAttackPoint() * (100.0 / (100 + unit->getDefencePoint()));
						unit->setHP(unit->getHP() - damage);
						cout << "\n" << attacker->getNickName() << " deals " << damage << " damage to " << unit->getNickName() << endl;
						if (!isAlive(unit)) {
							cout << "\n" << unit->getNickName() << " is dead" << endl;
							unit->setHP(0);
						}
						else if (isAlive(unit)) {
							cout << "\n" << unit->getNickName() << " has remaining " << unit->getHP() << " HP" << endl;
						}
					}
				}
			}
			else {
				cout << "\n" << attacker->getNickName() << " is failed to perform throwing knife attack" << endl;
			}
		}
	}
};
#endif