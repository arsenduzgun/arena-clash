#ifndef ASSASSIN_H
#define ASSASSIN_H

#include <iostream>
#include <thread>
#include <vector>
#include "Unit.h"

using namespace std;

class Assassin : public Unit {
protected:
    static constexpr int ASSASSIN_HP = 250;
    static constexpr int ASSASSIN_MAX_ATTACK = 40;
    static constexpr int ASSASSIN_MIN_ATTACK = 30;
    static constexpr int ASSASSIN_MAX_DEFENSE = 15;
    static constexpr int ASSASSIN_MIN_DEFENSE = 10;
    static constexpr int ASSASSIN_SPECIAL_ABILITY_CHANCE = 15;

public:
    Assassin(const string& nickName, const string& className, const string& teamName, int creationOrder)
        : Unit(nickName, className, teamName, creationOrder) {
        HP = maxHP = ASSASSIN_HP;
        maxAttackPoint = ASSASSIN_MAX_ATTACK;
        minAttackPoint = ASSASSIN_MIN_ATTACK;
        maxDefencePoint = ASSASSIN_MAX_DEFENSE;
        minDefencePoint = ASSASSIN_MIN_DEFENSE;
        specialAbilityChance = ASSASSIN_SPECIAL_ABILITY_CHANCE;
    }

    void attack(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam,
        unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) override {
        int damage = calculateDamage(attacker, defender);
        applyDamage(defender, damage);
        cout << "\n" << attacker->getNickName() << " deals " << damage << " damage to " << defender->getNickName() << endl;
        specialSkill(attackersTeam, defendersTeam, attacker, defender);
    }

    void specialSkill(vector<unique_ptr<Unit>>& attackersTeam, vector<unique_ptr<Unit>>& defendersTeam,
        unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) override {
        if (!isAlive(attacker) || !isTeamAlive(defendersTeam)) return;

        cout << "\n" << attacker->getNickName() << " attempts a throwing knife attack..." << endl;
        this_thread::sleep_for(1s);

        if (isLucky(attacker)) {
            cout << "\n" << attacker->getNickName() << " successfully performs a throwing knife attack!" << endl;
            for (auto& unit : defendersTeam) {
                if (isAlive(unit)) {
                    int damage = calculateDamage(attacker, unit);
                    applyDamage(unit, damage);
                    cout << "\n" << attacker->getNickName() << " deals " << damage << " damage to " << unit->getNickName() << endl;
                }
            }
        }
        else {
            cout << "\n" << attacker->getNickName() << " failed to perform the throwing knife attack." << endl;
        }
    }

private:
    int calculateDamage(unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender) {
        return attacker->getAttackPoint() * (100.0 / (100 + defender->getDefencePoint()));
    }

    void applyDamage(unique_ptr<Unit>& defender, int damage) {
        defender->setHP(max(0, defender->getHP() - damage));
        if (!isAlive(defender)) {
            cout << "\n" << defender->getNickName() << " has fallen!" << endl;
        }
        else {
            cout << "\n" << defender->getNickName() << " has " << defender->getHP() << " HP remaining." << endl;
        }
    }
};

#endif