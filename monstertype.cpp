#include "monstertype.h"
#include <iostream>
#include <string_view>

std::string_view getMonsterType(MonsterType& monsterType)
{
    using enum MonsterType;
    switch (monsterType){
        case Goblin:       return "Goblin";
        case Ogre:         return "Ogre";
        case Wyverns:      return "Wyverns";
        case Slime:        return "Slime";
        case Giant_Spider: return "Giant Spider";
        case Skeleton:     return "Skeletons";
        case Ghoul:        return "Ghoul";
    }
}

std::ostream& operator<<(std::ostream& out, MonsterType monsterType)
{
    out << getMonsterType(monsterType);
    return out;
}


