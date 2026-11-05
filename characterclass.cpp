#include "characterclass.h"
#include <string_view>
#include <iostream>

std::string_view getCharacterClass(CharacterClasses& charClass)
{
    using enum CharacterClasses;
    switch (charClass){
        case Warrior: return "Warrior";
        case Mage: return "Mage";
        default: return "???";
    }
}

std::ostream& operator<<(std::ostream& out, CharacterClasses charClass)
{
    out << getCharacterClass(charClass);
    return out;
}
