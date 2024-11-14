# Arena Clash

## 1. Introduction
This project is a command-line-based game where two teams of three units engage in combat. The teams select units from three available classes—Warrior, Assassin, and Healer—each with unique strengths, weaknesses, and special abilities. Players face off in one of two distinct arenas, each introducing different environmental effects that influence the flow of battle. The objective is to eliminate the opposing team by carefully managing unit abilities and adapting to the challenges posed by the arenas.

## 2. Game Structure
The game is designed as a turn-based battle where each team, composed of three units, alternates attacks and defenses until one team is completely eliminated. Players can choose to perform regular attacks, use special abilities, or rely on the unique effects of the arena in which the battle takes place.

The key elements of the game are the unit classes and the arena environments, both of which significantly impact gameplay. Each unit type has different attributes such as health points (HP), attack points, defense points, and special abilities. Arena effects add an extra layer of unpredictability, requiring players to strategize not just based on their opponents but also on the battlefield itself.

## 3. Units
The game features three unique unit types, each tailored to a specific combat role:

- **Warrior**:
  - A strong, offensive unit with a high chance of delivering critical attacks. Despite having lower HP, the warrior compensates with substantial attack power.
  - **Attributes**:
    - HP: 200
    - Attack Point: 35 - 45
    - Defense Point: 10 - 15
    - Special Ability: Critical Attack (deals double damage)
    - Special Ability Chance: 30%

- **Assassin**:
  - The assassin is a stealthy unit capable of launching attacks against all enemy units at once. While possessing slightly higher HP than the warrior, the assassin's low defense requires a hit-and-run style of play. The special ability allows the assassin to deal damage to multiple enemies, making it a versatile asset for weakening the opposition.
  - **Attributes**:
    - HP: 250
    - Attack Point: 30 - 40
    - Defense Point: 10 - 15
    - Special Ability: Attack all opponents simultaneously
    - Special Ability Chance: 15%

- **Healer**:
  - The healer is a support unit designed to restore HP to injured teammates. Although healers have moderate attack and defense capabilities, their primary role is to extend the survivability of the team by healing other units. However, they cannot heal dead teammates, making the timing of healing crucial for maintaining team strength.
  - **Attributes**:
    - HP: 250
    - Attack Point: 15 - 20
    - Defense Point: 15 - 20
    - Special Ability: Heal teammates by restoring 10% of their HP (cannot be applied to dead teammates)
    - Special Ability Chance: 15%

## 4. Arenas
The game takes place in one of two distinct arenas, each with its own special effects that shape the course of the battle:

- **Fire Meteorite Arena**:
  - The Fire Meteorite Arena introduces environmental hazards that deal 20 pure damage to each unit on the field after every round. This damage cannot be blocked or reduced by defense, forcing players to factor in attrition alongside regular combat. The chance of a fire meteorite attack occurring is 10% after each round, adding an element of randomness that can quickly turn the tide of battle.
  - **Effect**:
    - 20 pure damage to each unit after every round.
    - Fire Meteorite Chance: 10%

- **Valhalla Arena**:
  - The Valhalla Arena brings a unique resurrection mechanic to the game. After each round, there is a 5% chance that dead units will be resurrected with 20% of their maximum HP. This resurrection mechanic can prolong battles and provide teams with unexpected opportunities to recover from heavy losses.
  - **Effect**:
    - Resurrects dead units with 20% of their HP after each round.
    - Resurrection Chance: 5%

## 5. Game Mechanics
The game operates on a straightforward turn-based combat system where units alternate attacking and defending. Units' damage output is calculated based on their attack and defense points, and the effectiveness of defense plays a crucial role in keeping units alive. Special abilities add a tactical layer to the game, as each unit has a chance to trigger a powerful ability that can swing the battle in favor of one team.

The arenas further enhance gameplay by introducing environmental effects that affect all units, demanding players to adapt their strategies accordingly.

## 6. Future Work
1. **More units**: Introduce additional unit types with unique abilities and attributes, such as ranged attackers or defensive tanks, to increase the variety of team compositions and strategies.
2. **More arenas**: Expand the available arenas with different environmental effects, such as ice fields that slow movement or poison fields that deal gradual damage, providing fresh challenges and strategic considerations for each battle.
3. **Graphical User Interface**: Develop a GUI to make the game more accessible and visually engaging. This would allow for easier navigation, improved interaction, and an overall enhanced user experience compared to the command-line interface.

## 7. Conclusion
The Arena Clash project offers a fun and strategic gameplay experience where players can experiment with different team compositions and strategies. The combination of diverse unit types and dynamic arena effects creates a fresh challenge in every game. With a solid framework in place, the game has the potential for future enhancements that could further improve both its replayability and depth.