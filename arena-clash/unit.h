#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <vector>
#include <memory>
#include <random>

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

    // Shared static random number generator
    static mt19937 rng;

public:
    Unit(string nickName, string className, string teamName, int creationOrder)
        : nickName(move(nickName)), teamName(move(teamName)),
        className(move(className)), creationOrder(creationOrder) {}

    virtual ~Unit() = default;

    virtual void attack(vector<unique_ptr<Unit>>& attackersTeam,
        vector<unique_ptr<Unit>>& defendersTeam,
        unique_ptr<Unit>& attacker,
        unique_ptr<Unit>& defender) = 0;

    virtual void specialSkill(vector<unique_ptr<Unit>>& attackersTeam,
        vector<unique_ptr<Unit>>& defendersTeam,
        unique_ptr<Unit>& attacker,
        unique_ptr<Unit>& defender) = 0;

    string getNickName() const { return nickName; }
    string getTeamName() const { return teamName; }
    string getClassName() const { return className; }
    int getCreationOrder() const { return creationOrder; }
    int getHP() const { return HP; }
    int getMaxHP() const { return maxHP; }
    int getSpecialAbilityChance() const { return specialAbilityChance; }

    void setHP(int newHP) { HP = newHP; }

    int getAttackPoint() const {
        uniform_int_distribution<int> dist(minAttackPoint, maxAttackPoint);
        return dist(rng);
    }

    int getDefencePoint() const {
        uniform_int_distribution<int> dist(minDefencePoint, maxDefencePoint);
        return dist(rng);
    }

    static bool isAlive(const unique_ptr<Unit>& unit) {
        return unit && unit->getHP() > 0;
    }

    static bool isTeamAlive(const vector<unique_ptr<Unit>>& team) {
        for (const auto& unit : team) {
            if (isAlive(unit)) return true;
        }
        return false;
    }

    // ✅ Accepts unique_ptr directly now
    static bool isLucky(const unique_ptr<Unit>& unit) {
        uniform_int_distribution<int> dist(1, 100);
        return dist(rng) <= unit->getSpecialAbilityChance();
    }
};

// Initialize static RNG
mt19937 Unit::rng(random_device{}());

#endif // UNIT_H