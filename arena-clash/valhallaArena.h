#ifndef VALHALLAARENA_H
#define VALHALLAARENA_H

#include "Arena.h"
#include <vector>

class ValhallaArena : public Arena {

protected:

	const int resurrectionChance = 5;
	const string arenaName = "Valhalla Arena";

public:

	void arenaEffect(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
		if (isTeamAlive(team1) && isTeamAlive(team2)) {
			cout << "\n" << arenaName << " trying to perform resurrection spell" << endl;
			this_thread::sleep_for(1s);
			if (isLucky(resurrectionChance)) {
				cout << "\n" << arenaName << " is succeed to perform resurrection spell" << endl;
				for (unique_ptr<Unit>& unit : team1) {
					if (!isAlive(unit)) {
						int resurrectionHP = (unit->getMaxHP() / 10);
						unit->setHP(resurrectionHP);
						cout << "\n" << arenaName << " resurrect " << unit->getNickName() << " with " << resurrectionHP << " HP" << endl;
					}
					else {
						cout << "\n" << unit->getNickName() << " is already alive" << endl;
					}
				}
				for (unique_ptr<Unit>& unit : team2) {
					if (!isAlive(unit)) {
						int resurrectionHP = (unit->getMaxHP() / 10);
						unit->setHP(resurrectionHP);
						cout << "\n" << arenaName << " resurrect " << unit->getNickName() << " with " << resurrectionHP << " HP" << endl;
					}
					else {
						cout << "\n" << unit->getNickName() << " is already alive" << endl;
					}
				}
			}
			else {
				cout << "\n" << arenaName << " failed to perform resurrection spell" << endl;
			}
		}
	}
};
#endif