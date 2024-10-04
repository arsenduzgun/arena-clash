#ifndef FIREMETEORITEARENA_H
#define FIREMETEORITEARENA_H

#include "Arena.h"
#include <vector>

class FireMeteoriteArena : public Arena {

protected:

	const int fireMeteoriteChance = 10;
	const int fireMeteoriteDamage = 20;
	const string arenaName = "Fire Meteorite Arena";

public:

	void arenaEffect(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
		if (isTeamAlive(team1) && isTeamAlive(team2)) {
			cout << "\n" << arenaName << " trying to perform fire meteorite attack" << endl;
			this_thread::sleep_for(1s);
			if (isLucky(fireMeteoriteChance)) {
				cout << "\n" << arenaName << " is succeed to perform fire meteorite attack" << endl;
				for (unique_ptr<Unit>& unit : team1) {
					if (isAlive(unit)) {
						unit->setHP(unit->getHP() - fireMeteoriteDamage);
						cout << "\n" << "Fire meteorite deals " << fireMeteoriteDamage << " damage to " << unit->getNickName() << endl;
						if (!isAlive(unit)) {
							cout << "\n" << unit->getNickName() << " is dead" << endl;
							unit->setHP(0);
						}
						else {
							cout << "\n" << unit->getNickName() << " has remaining " << unit->getHP() << " HP" << endl;
						}
					}
				}
				for (unique_ptr<Unit>& unit : team2) {
					if (isAlive(unit)) {
						unit->setHP(unit->getHP() - fireMeteoriteDamage);
						cout << "\n" << "Fire meteorite deals " << fireMeteoriteDamage << " damage to " << unit->getNickName() << endl;
						if (!isAlive(unit)) {
							cout << "\n" << unit->getNickName() << " is dead" << endl;
							unit->setHP(0);
						}
						else {
							cout << "\n" << unit->getNickName() << " has remaining " << unit->getHP() << " HP" << endl;
						}
					}
				}
			}
			else {
				cout << "\n" << arenaName << " failed to perform fire meteorite attack" << endl;
			}
		}
	}
};
#endif