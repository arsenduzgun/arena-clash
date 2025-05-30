#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <thread>
#include <vector>
#include "Unit.h"

using namespace std;

class Warrior : public Unit {

protected:
    static constexpr int warriorHP = 200;
    static constexpr int warriorMaxAttackPoint = 45;
    static constexpr int warriorMinAttackPoint = 35;
    static constexpr int warriorMaxDefencePoint = 15;
    static constexpr int warriorMinDefencePoint = 10;
    static constexpr int warriorSpecialAbilityChance = 30;

    void applyDamage(unique_ptr<Unit>& attacker, unique_ptr<Unit>& defender, int damage, bool isCritical) const {
        defender->setHP(defender->getHP() - damage);
        cout << "\n" << attacker->getNickName()
             << " deals " << damage << " damage"
             << (isCritical ? " (critical)" : "") << " to "
             << defender->getNickName() << "." << endl;

        if (!isAlive(defender)) {
            defender->setHP(0);
            cout << defender->getNickName() << " is dead." << endl;
        } else {
            cout << defender->getNickName() << " has " << defender->getHP() << " HP remaining." << endl;
        }
    }

public:
    Warrior(string nickName, string className, string teamName, int creationOrder)
        : Unit(nickName, className, teamName, creationOrder) 
    {
        HP = warriorHP;
        maxHP = warriorHP;
        maxAttackPoint = warriorMaxAttackPoint;
        minAttackPoint = warriorMinAttackPoint;
        maxDefencePoint = warriorMaxDefencePoint;
        minDefencePoint = warriorMinDefencePoint;
        specialAbilityChance = warriorSpecialAbilityChance;
    }

    void attack(vector<unique_ptr<Unit>>& attackersTeam,
                vector<unique_ptr<Unit>>& defendersTeam,
                unique_ptr<Unit>& attacker,
                unique_ptr<Unit>& defender) override 
    {
        int baseAttack = attacker->getAttackPoint();
        int defence = defender->getDefencePoint();
        int damage;
        bool critical = isLucky(attacker);

        if (critical) {
            damage = static_cast<int>(baseAttack * (100.0 / (100 + defence)) * 2);
        } else {
            damage = static_cast<int>(baseAttack * (100.0 / (100 + defence)));
        }

        applyDamage(attacker, defender, damage, critical);
    }

    void specialSkill(vector<unique_ptr<Unit>>& attackersTeam,
                      vector<unique_ptr<Unit>>& defendersTeam,
                      unique_ptr<Unit>& attacker,
                      unique_ptr<Unit>& defender) override 
    {
        // No special skill implemented yet for Warrior
    }
};

#endif // WARRIOR_H