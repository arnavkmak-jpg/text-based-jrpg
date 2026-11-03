#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H
#include <string_view>
#include <iostream>

enum class MonsterType
{
    Goblin,
    Ogre,
    Wyverns,
    Slime,
    Witch,
    Giant_Spider,
    Skeleton,
    Ghoul,
    // bosses
    Dragon_King,
};

std::string_view getMonsterType(MonsterType& monsterType);
std::ostream& operator<<(std::ostream& out, MonsterType monsterType);

#endif
