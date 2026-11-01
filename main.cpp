// choose class of player
// randomise enemy spawns
// loop turns player attacks/heals then enemy attack backs
// end of each turn display hp of both parties 
#include <iostream>
#include "ignore.h"
#include <string_view>
#include "Random.h"

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
};

struct Monster
{
    MonsterType monsterType{};
    int monsterHealthPoints{};
    int monsterDamage{};

    MonsterType generateRandomMonster()
    {
        // generate a random number for a random monster
        return static_cast<MonsterType>(Random::get(0,7));
    }

    // access the enumerator from monster type enum and set it's stat accordingly
    void setMonsterStats(MonsterType& monsterType)
    {
        using enum MonsterType;
        switch (monsterType){
            case Goblin:
                monsterHealthPoints = 80;
                monsterDamage = 30;
                break;
            case Ogre:
                monsterHealthPoints = 120;
                monsterDamage = 40;
                break;
            case Wyverns:
                monsterHealthPoints = 150;
                monsterDamage = 20;
                break;
            case Slime:
                monsterHealthPoints = 30;
                monsterDamage = 10;
                break;
            case Witch:
                monsterHealthPoints = 70;
                monsterDamage = 60;
                break;
            case Giant_Spider:
                monsterHealthPoints = 150;
                monsterDamage = 30;
                break;
            case Skeleton:
                monsterHealthPoints = 60;
                monsterDamage = 50;
                break;
            case Ghoul:
                monsterHealthPoints = 100;
                monsterDamage = 20;
                break;
            
            
        }
    }


};



enum class CharacterClasses
{
    Warrior = 1,
    Mage = 2,
};

struct Player
{
    std::string_view playerName{};
    CharacterClasses charClass{};
    int playerHealthPoints{};
    int playerDamage{};

    // function to set stats of the player according to class chosen
    void setPlayerStats(CharacterClasses& charClass)
    {   
        using enum CharacterClasses;
        switch (charClass){
            case Warrior: 
                playerHealthPoints = 150;
                playerDamage = 60;
                break;
            case Mage:
                playerHealthPoints = 110;
                playerDamage = 80;
                break;
        }
    }
};

// helper function to check if stats are set properly
void printPlayerStats(Player& player)
{
    std::cout << player.playerDamage << " " << player.playerHealthPoints;
}

// function that takes input from player and returns an enumarator according to the choice
CharacterClasses chooseCharacterClass()
{
    int input{0};

    // loop runs till the input is out of range
    while (input < 1 || input > 2){
        std::cout << "Choose a class (1 or 2): ";
        std::cin >> input;

        // checks for invalid inputs
        if (extractionFailed()){
            std::cout << "Invalid input, choose again\n";
            continue;
        }
        ignoreLine();
        if (input < 1 || input > 2) {
            std::cout << "Invalid choice, choose again\n";
            continue;
        }
    
    }
    return static_cast<CharacterClasses>(input);
}



int main()
{
    CharacterClasses charClass{chooseCharacterClass()};
    Player player{.playerName = "FBI", .charClass = charClass};
    player.setPlayerStats(charClass);
    printPlayerStats(player);
    return 0;
}
