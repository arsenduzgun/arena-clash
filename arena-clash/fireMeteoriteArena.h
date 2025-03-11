#ifndef FIREMETEORITEARENA_H
#define FIREMETEORITEARENA_H

#include "Arena.h"
#include <vector>
#include <thread>

class FireMeteoriteArena : public Arena {
protected:
    static constexpr int FIRE_METEORITE_CHANCE = 10;
    static constexpr int FIRE_METEORITE_DAMAGE = 20;
    static constexpr const char* ARENA_NAME = "Fire Meteorite Arena";

public:
    void arenaEffect(vector<unique_ptr<Unit>>& team1, vector<unique_ptr<Unit>>& team2) override {
        if (!isTeamAlive(team1) || !isTeamAlive(team2)) return;

        cout << "\n" << ARENA_NAME << " is attempting a fire meteorite attack..." << endl;
        this_thread::sleep_for(1s);

        if (isLucky(FIRE_METEORITE_CHANCE)) {
            cout << "\n" << ARENA_NAME << " successfully launches a fire meteorite attack!" << endl;
            applyMeteoriteDamage(team1);
            applyMeteoriteDamage(team2);
        }
        else {
            cout << "\n" << ARENA_NAME << " failed to perform a fire meteorite attack." << endl;
        }
    }

private:
    void applyMeteoriteDamage(vector<unique_ptr<Unit>>& team) {
        for (auto& unit : team) {
            if (isAlive(unit)) {
                unit->setHP(max(0, unit->getHP() - FIRE_METEORITE_DAMAGE));
                cout << "\nFire meteorite deals " << FIRE_METEORITE_DAMAGE << " damage to " << unit->getNickName() << "!" << endl;

                if (!isAlive(unit)) {
                    cout << "\n" << unit->getNickName() << " has fallen!" << endl;
                }
                else {
                    cout << "\n" << unit->getNickName() << " has " << unit->getHP() << " HP remaining." << endl;
                }
            }
        }
    }
};

#endif