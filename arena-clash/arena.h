#ifndef ARENA_H
#define ARENA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Arena {

public:

	Arena() {}

	virtual void arenaEffect(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) = 0;

	void battle(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
		vector<unique_ptr<Unit>>::iterator team1Iterator = team1.begin();
		vector<unique_ptr<Unit>>::iterator team2Iterator = team2.begin();
		int round = 1;
		string input;
		bool isAttackPerformed;
		bool isAttackerAlive;
		bool isBattleOver = false;
		cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
		while (!isBattleOver) {
			cout << "\n\t\t\t\t\t\t### ROUND " << round << " ###" << endl;
			teamsInfo(team1, team2);
			cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
			if (isTeamAlive(team1) && isTeamAlive(team2)) {
				isAttackerAlive = false;
				while (!isAttackerAlive) {
					if (isAlive(*team1Iterator)) {
						isAttackerAlive = true;
						cout << "\nYou are leading " << (*team1Iterator)->getNickName() << ", which enemy do you want to attack, please enter a number: ";
						isAttackPerformed = false;
						while (!isAttackPerformed) {
							cin >> input;
							if (isInputValid(team2, input)) {
								if (isAlive(team2[stoi(input) - 1])) {
									isAttackPerformed = true;
									(*team1Iterator)->attack(team1, team2, (*team1Iterator), team2[stoi(input) - 1]);
									team1Iterator++;
									if (team1Iterator == team1.end()) {
										team1Iterator = team1.begin();
									}
								}
								else {
									cout << "\n" << team2[stoi(input) - 1]->getNickName() << " is already dead, please enter again: ";
								}
							}
							else {
								cout << "\nYou have entered an invalid value, please enter again: ";
							}
						}
					}
					else {
						team1Iterator++;
						if (team1Iterator == team1.end()) {
							team1Iterator = team1.begin();
						}
					}
				}
			}
			if (isTeamAlive(team1) && isTeamAlive(team2)) {
				isAttackerAlive = false;
				while (!isAttackerAlive) {
					if (isAlive(*team2Iterator)) {
						isAttackerAlive = true;
						cout << "\nYou are leading " << (*team2Iterator)->getNickName() << ", which enemy do you want to attack, please enter a number: ";
						isAttackPerformed = false;
						while (!isAttackPerformed) {
							cin >> input;
							if (isInputValid(team1, input)) {
								if (isAlive(team1[stoi(input) - 1])) {
									isAttackPerformed = true;
									(*team2Iterator)->attack(team2, team1, (*team2Iterator), team1[stoi(input) - 1]);
									team2Iterator++;
									if (team2Iterator == team2.end()) {
										team2Iterator = team2.begin();
									}
									round++;
								}
								else {
									cout << "\n" << team1[stoi(input) - 1]->getNickName() << " is already dead, please enter again: ";
								}
							}
							else {
								cout << "\nYou have entered an invalid value, please enter again: ";
							}
						}
					}
					else {
						team2Iterator++;
						if (team2Iterator == team2.end()) {
							team2Iterator = team2.begin();
						}
					}
				}
			}
			arenaEffect(team1, team2);
			cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
			if (!isTeamAlive(team1) || !isTeamAlive(team2)) {
				isBattleOver = true;
			}
		}
		winner(team1, team2);
	}

	void winner(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
		cout << "\n\t\t\t\t\t****************************************" << endl;
		if (!isTeamAlive(team1) && !isTeamAlive(team2)) {
			cout << "\n\t\tAll units of " << team1.front()->getTeamName() << " and " << team2.front()->getTeamName() << " are dead, there is no winner" << endl;
		}
		else if (isTeamAlive(team1)) {
			cout << "\n\t\t\t\t\t\t" << team1.front()->getTeamName() << " wins the battle" << endl;
			cout << "\n\t\t\t\t\t\t\tSURVIVORS" << endl;
			cout << "\t\t\t\t\t\t\t_________" << endl;
			for (unique_ptr<Unit>& unit : team1) {
				if (unit->getHP() > 0) {
					cout << "\n\t\t\t\t\t\t" << unit->getNickName() << " (" << unit->getClassName() << " - " << unit->getHP() << " HP)" << endl;
				}
			}
		}
		else if (isTeamAlive(team2)) {
			cout << "\n\t\t\t\t\t\t" << team2.front()->getTeamName() << " wins the battle" << endl;
			cout << "\n\t\t\t\t\t\t\t" << "SURVIVORS" << endl;
			cout << "\t\t\t\t\t\t\t_________" << endl;
			for (unique_ptr<Unit>& unit : team2) {
				if (unit->getHP() > 0) {
					cout << "\n\t\t\t\t\t\t" << unit->getNickName() << " (" << unit->getClassName() << " - " << unit->getHP() << " HP)" << endl;
				}
			}
		}
		cout << "\n\t\t\t\t\t****************************************" << endl;
		cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	}

	void teamsInfo(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
		for (unique_ptr<Unit>& unit : team1) {
			if (unit->getCreationOrder() == team1.front()->getCreationOrder()) {
				cout << "\n" << unit->getTeamName() << ": " << unit->getNickName() << "(" << unit->getClassName() << " - " << unit->getHP() << " HP) | ";
			}
			else if (unit->getCreationOrder() == team1.back()->getCreationOrder()) {
				cout << unit->getNickName() << "(" << unit->getClassName() << " - " << unit->getHP() << " HP)" << endl;
			}
			else {
				cout << unit->getNickName() << "(" << unit->getClassName() << " - " << unit->getHP() << " HP) | ";
			}
		}
		for (unique_ptr<Unit>& unit : team2) {
			if (unit->getCreationOrder() == team2.front()->getCreationOrder()) {
				cout << "\n" << unit->getTeamName() << ": " << unit->getNickName() << "(" << unit->getClassName() << " - " << unit->getHP() << " HP) | ";
			}
			else if (unit->getCreationOrder() == team2.back()->getCreationOrder()) {
				cout << unit->getNickName() << "(" << unit->getClassName() << " - " << unit->getHP() << " HP)" << endl;
			}
			else {
				cout << unit->getNickName() << "(" << unit->getClassName() << " - " << unit->getHP() << " HP) | ";
			}
		}
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

	bool isInputValid(vector<unique_ptr<Unit>>& team, string input) {
		for (unique_ptr<Unit>& unit : team) {
			if (input._Equal(to_string(unit->getCreationOrder()))) {
				return true;
			}
		}
		return false;
	}

	bool isLucky(int SpecialAbilityChance) {
		srand(time(NULL));
		int chance = 1 + (rand() % 99);
		if (chance <= SpecialAbilityChance) {
			return true;
		}
		return false;
	}
};
#endif