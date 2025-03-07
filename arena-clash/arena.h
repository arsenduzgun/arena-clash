#ifndef ARENA_H
#define ARENA_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

using namespace std;

class Arena {
public:
    Arena() {}

    virtual void arenaEffect(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) = 0;

    void battle(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
        auto team1Iterator = team1.begin();
        auto team2Iterator = team2.begin();
        int round = 1;
        bool isBattleOver = false;

        cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
        while (!isBattleOver) {
            cout << "\n\t\t\t\t\t\t### ROUND " << round << " ###" << endl;
            displayTeamsInfo(team1, team2);
            cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;

            if (isTeamAlive(team1) && isTeamAlive(team2)) {
                processTurn(team1Iterator, team1, team2, "You are leading ");
            }
            if (isTeamAlive(team1) && isTeamAlive(team2)) {
                processTurn(team2Iterator, team2, team1, "You are leading ");
                round++;
            }

            arenaEffect(team1, team2);
            cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;

            isBattleOver = !isTeamAlive(team1) || !isTeamAlive(team2);
        }
        determineWinner(team1, team2);
    }

protected:  // Changed from private to protected for access in derived classes
    bool isTeamAlive(const vector<unique_ptr<Unit>>& team) const {
        return any_of(team.begin(), team.end(), [](const unique_ptr<Unit>& unit) { return unit->getHP() > 0; });
    }

    bool isAlive(const unique_ptr<Unit>& unit) const {  // Added missing function
        return unit->getHP() > 0;
    }

    bool isLucky(int SpecialAbilityChance) {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> distr(1, 100);
        return distr(gen) <= SpecialAbilityChance;
    }

private:
    void processTurn(vector<unique_ptr<Unit>>::iterator& attacker, vector<unique_ptr<Unit>>& attackingTeam,
        vector<unique_ptr<Unit>>& defendingTeam, const string& prompt) {
        string input;
        while (true) {
            if ((*attacker)->getHP() > 0) {
                cout << "\n" << prompt << (*attacker)->getNickName()
                    << ", which enemy do you want to attack? Enter a number: ";

                while (true) {
                    cin >> input;
                    int targetIndex;
                    try {
                        targetIndex = stoi(input) - 1;
                        if (targetIndex >= 0 && targetIndex < defendingTeam.size() && defendingTeam[targetIndex]->getHP() > 0) {
                            break;
                        }
                        else {
                            cout << "\nInvalid choice or target is already dead. Please enter again: ";
                        }
                    }
                    catch (...) {
                        cout << "\nInvalid input. Please enter a valid number: ";
                    }
                }

                (*attacker)->attack(attackingTeam, defendingTeam, *attacker, defendingTeam[stoi(input) - 1]);
                attacker++;
                if (attacker == attackingTeam.end()) {
                    attacker = attackingTeam.begin();
                }
                return;
            }
            attacker++;
            if (attacker == attackingTeam.end()) {
                attacker = attackingTeam.begin();
            }
        }
    }

    void determineWinner(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) {
        cout << "\n\t\t\t\t\t****************************************" << endl;
        if (!isTeamAlive(team1) && !isTeamAlive(team2)) {
            cout << "\n\t\tBoth teams are eliminated. No winner." << endl;
        }
        else {
            auto& winningTeam = isTeamAlive(team1) ? team1 : team2;
            cout << "\n\t\t\t\t\t\t" << winningTeam.front()->getTeamName() << " wins the battle!" << endl;
            cout << "\n\t\t\t\t\t\t\tSURVIVORS" << endl;
            cout << "\t\t\t\t\t\t\t_________" << endl;
            for (auto& unit : winningTeam) {
                if (unit->getHP() > 0) {
                    cout << "\n\t\t\t\t\t\t" << unit->getNickName() << " (" << unit->getClassName()
                        << " - " << unit->getHP() << " HP)" << endl;
                }
            }
        }
        cout << "\n\t\t\t\t\t****************************************" << endl;
        cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void displayTeamsInfo(const vector<unique_ptr<Unit>>& team1, const vector<unique_ptr<Unit>>& team2) {
        auto printTeam = [](const vector<unique_ptr<Unit>>& team) {
            cout << "\n" << team.front()->getTeamName() << ": ";
            for (size_t i = 0; i < team.size(); ++i) {
                cout << team[i]->getNickName() << " (" << team[i]->getClassName() << " - " << team[i]->getHP() << " HP)";
                if (i != team.size() - 1) cout << " | ";
            }
            cout << endl;
            };
        printTeam(team1);
        printTeam(team2);
    }
};

#endif
