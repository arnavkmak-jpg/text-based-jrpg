#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H
#include <string_view>
#include <iostream>

enum class CharacterClasses
{
    Warrior = 1,
    Mage = 2,
};

std::string_view getCharacterClass(CharacterClasses& charClass);
std::ostream& operator<<(std::ostream& out, CharacterClasses charClass);

#endif
