#ifndef VALHALLAARENA_H
#define VALHALLAARENA_H

#include "Arena.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

class ValhallaArena : public Arena {
protected:
    static constexpr int resurrectionChance = 5;
    static constexpr const char* arenaName = "Valhalla Arena";

    void resurrectUnits(std::vector<std::unique_ptr<Unit>>& team) const {
        for (auto& unit : team) {
            if (!isAlive(unit)) {
                int resurrectionHP = unit->getMaxHP() / 10;
                unit->setHP(resurrectionHP);
                std::cout << "\n" << arenaName << " resurrected " 
                          << unit->getNickName() << " with " << resurrectionHP << " HP.\n";
            }
        }
    }

public:
    void arenaEffect(std::vector<std::unique_ptr<Unit>>& team1, 
                     std::vector<std::unique_ptr<Unit>>& team2) override 
    {
        if (!isTeamAlive(team1) || !isTeamAlive(team2)) return;

        std::cout << "\n" << arenaName << " attempts to cast Resurrection Spell...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (isLucky(resurrectionChance)) {
            std::cout << arenaName << " successfully casts the Resurrection Spell!\n";
            resurrectUnits(team1);
            resurrectUnits(team2);
        } else {
            std::cout << arenaName << " failed to cast the Resurrection Spell.\n";
        }
    }
};

#endif // VALHALLAARENA_H