#include "monstertype.h"
#include <iostream>
#include <string_view>

std::string_view getMonsterType(MonsterType& monsterType)
{
    using enum MonsterType;
    switch (monsterType){
        case Goblin:       return "Goblin";
        case Ogre:         return "Ogre";
        case Wyverns:      return "Wyvern";
        case Slime:        return "Slime";
        case Giant_Spider: return "Giant Spider";
        case Witch:        return "Witch";
        case Skeleton:     return "Skeleton";
        case Ghoul:        return "Ghoul";
        case Dragon_King:  return "Dragon King";
        default: return "???";
    }
}

std::ostream& operator<<(std::ostream& out, MonsterType monsterType)
{
    out << getMonsterType(monsterType);
    return out;
}


