#ifndef HEALER_H
#define HEALER_H

#include <iostream>
#include <thread>
#include <vector>
#include "Unit.h"

using namespace std;

class Healer : public Unit {
protected:
    static constexpr int HEALER_HP = 250;
    static constexpr int HEALER_MAX_ATTACK = 20;
    static constexpr int HEALER_MIN_ATTACK = 15;
    static constexpr int HEALER_MAX_DEFENSE = 20;
    static constexpr int HEALER_MIN_DEFENSE = 15;
    static constexpr int HEALER_SPECIAL_ABILITY_CHANCE = 15;
    static constexpr double HEAL_PERCENTAGE = 0.2;

public:
    Healer(const string& nickName, const string& className, const string& teamName, int creationOrder)
        : Unit(nickName, className, teamName, creationOrder) {
        HP = maxHP = HEALER_HP;
        maxAttackPoint = HEALER_MAX_ATTACK;
        minAttackPoint = HEALER_MIN_ATTACK;
        maxDefencePoint = HEALER_MAX_DEFENSE;
        minDefencePoint = HEALER_MIN_DEFENSE;
        specialAbilityChance = HEALER_SPECIAL_ABILITY_CHANCE;
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
        if (!isAlive(attacker) || !isTeamAlive(attackersTeam)) return;

        cout << "\n" << attacker->getNickName() << " attempts a healing spell..." << endl;
        this_thread::sleep_for(1s);

        if (isLucky(attacker)) {
            cout << "\n" << attacker->getNickName() << " successfully casts a healing spell!" << endl;
            healTeam(attackersTeam, attacker);
        }
        else {
            cout << "\n" << attacker->getNickName() << " failed to perform the healing spell." << endl;
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

    void healTeam(vector<unique_ptr<Unit>>& team, unique_ptr<Unit>& healer) {
        for (auto& unit : team) {
            if (isAlive(unit) && unit->getHP() < unit->getMaxHP()) {
                int healAmount = static_cast<int>(unit->getMaxHP() * HEAL_PERCENTAGE);
                unit->setHP(min(unit->getMaxHP(), unit->getHP() + healAmount));
                cout << "\n" << healer->getNickName() << " heals " << unit->getNickName()
                    << " for " << healAmount << " HP. " << unit->getNickName() << " now has "
                    << unit->getHP() << " HP." << endl;
            }
        }
    }
};

#endif