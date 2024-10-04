#ifndef HEALER_H
#define HEALER_H

#include <iostream>
#include "Unit.h"
#include <thread>
#include <vector>

using namespace std;

class Healer : public Unit {

protected:
	const int healerHP = 250;
	const int healerMaxAttackPoint = 20;
	const int healerMinAttackPoint = 15;
	const int healerMaxDefencePoint = 20;
	const int healerMinDefencePoint = 15;
	const int healerSpecialAbilityChance = 15;

public:

	Healer(string nickName, string className, string teamName, int creationOrder) : Unit(nickName, className, teamName, creationOrder) {
		HP = healerHP;
		maxHP = healerHP;
		maxAttackPoint = healerMaxAttackPoint;
		minAttackPoint = healerMinAttackPoint;
		maxDefencePoint = healerMaxDefencePoint;
		minDefencePoint = healerMinDefencePoint;
		specialAbilityChance = healerSpecialAbilityChance;
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
			cout << "\n" << attacker->getNickName() << " tries to perform life god spell" << endl;
			this_thread::sleep_for(1s);
			if (isLucky(attacker)) {
				cout << "\n" << attacker->getNickName() << " is succeed to perform life god spell" << endl;
				int hp;
				for (unique_ptr<Unit>& unit : attackersTeam) {
					if (unit->getHP() >= ((unit->getMaxHP() * 4) / 5.0)) {
						if (unit->getHP() == unit->getMaxHP()) {
							cout << "\n" << unit->getNickName() << " has already full health" << endl;
						}
						else if (unit->getHP() != unit->getMaxHP()) {
							hp = unit->getMaxHP() - unit->getHP();
							unit->setHP(unit->getMaxHP());
							if (unit->getCreationOrder() == attacker->getCreationOrder()) {
								cout << "\n" << attacker->getNickName() << " heals himself/herself of " << hp << " HP and " << unit->getNickName() << " has " << unit->getHP() << " HP now" << endl;
							}
							else if (unit->getCreationOrder() != attacker->getCreationOrder()) {
								cout << "\n" << attacker->getNickName() << " heals " << unit->getNickName() << " of " << hp << " HP and " << unit->getNickName() << " has " << unit->getHP() << " HP now" << endl;
							}
						}
					}
					else if (unit->getHP() < ((unit->getMaxHP() * 4) / 5.0)) {
						if (isAlive(unit)) {
							hp = (unit->getMaxHP() / 5.0);
							unit->setHP(unit->getHP() + hp);
							if (unit->getCreationOrder() == attacker->getCreationOrder()) {
								cout << "\n" << attacker->getNickName() << " heals himself/herself of " << hp << " HP and " << unit->getNickName() << " has " << unit->getHP() << " HP now" << endl;
							}
							else if (unit->getCreationOrder() != attacker->getCreationOrder()) {
								cout << "\n" << attacker->getNickName() << " heals " << unit->getNickName() << " of " << hp << " HP and " << unit->getNickName() << " has " << unit->getHP() << " HP now" << endl;
							}
						}
						else if (!isAlive(unit)) {
							cout << "\n" << unit->getNickName() << " cannot be healed, because " << unit->getNickName() << " is dead" << endl;
						}
					}
				}
			}
			else {
				cout << "\n" << attacker->getNickName() << " is failed to perform life god spell" << endl;
			}
		}
	}
};
#endif