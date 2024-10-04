#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Unit {

protected:

	const string nickName;
	const string teamName;
	const string className;
	const int creationOrder;
	int maxHP;
	int HP;
	int maxAttackPoint;
	int minAttackPoint;
	int maxDefencePoint;
	int minDefencePoint;
	int specialAbilityChance;
	bool isFrozen = false;
	bool isCursed = false;

public:

	Unit(string nickName, string className, string teamName, int creationOrder) : nickName(nickName), className(className), teamName(teamName), creationOrder(creationOrder) {}

	virtual void attack(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam, unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) = 0;

	virtual void specialSkill(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam, unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) = 0;

	string getNickName() const {
		return nickName;
	}

	int getHP() const {
		return HP;
	}

	void setHP(int HP) {
		this->HP = HP;
	}

	int getMaxHP() const {
		return maxHP;
	}

	int getCreationOrder() const {
		return creationOrder;
	}

	string getTeamName() const {
		return teamName;
	}

	string getClassName() const {
		return className;
	}

	int getAttackPoint() const {
		srand(time(NULL));
		return minAttackPoint + (rand() % (maxAttackPoint - minAttackPoint));
	}

	int getDefencePoint() const {
		srand(time(NULL));
		return minDefencePoint + (rand() % (maxDefencePoint - minDefencePoint));
	}

	int getSpecialAbilityChance() const {
		return specialAbilityChance;
	}

	bool isTeamAlive(vector<unique_ptr<Unit>>& team) {
		for (unique_ptr<Unit>& unit : team) {
			if (unit->getHP() > 0) {
				return true;
			}
		}
		return false;
	}

	bool isAlive(unique_ptr<Unit>& unit) {
		if (unit->getHP() > 0) {
			return true;
		}
		return false;
	}

	bool isLucky(unique_ptr<Unit>& unit) {
		srand(time(NULL));
		int chance = 1 + (rand() % 99);
		if (chance <= unit->getSpecialAbilityChance()) {
			return true;
		}
		return false;
	}
};
#endif