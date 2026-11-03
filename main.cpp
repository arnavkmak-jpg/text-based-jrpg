// choose class of player
// randomise enemy spawns
// loop turns player attacks/heals then enemy attack backs
// end of each turn display hp of both parties 
#include <iostream>
#include "ignore.h"
#include <string_view>
#include "Random.h"
#include "monstertype.h"
#include "characterclass.h"


struct Boss
{
    int bossHealthPoints{500};
    int bossDamage{50};
};

struct Monster
{
    MonsterType monsterType{};
    int monsterRemainingHealthPoints{};
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
        monsterRemainingHealthPoints = monsterHealthPoints;
    }


};

struct Player
{
    std::string_view playerName{};
    CharacterClasses charClass{};
    int playerRemainingHealthPoints{};
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
        playerRemainingHealthPoints = playerHealthPoints;
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

std::string_view getPlayerName()
{
    std::cout << "Please input your name (5-10 characteres): ";
    // TO DO: limit input to 5 - 10 characters
    std::string playerName{};
    std::cin >> playerName;

    return playerName;
}



bool startRound(Player& player, Boss& boss, int roundNumber, int healingItems)
{
    Monster monster{};
    // check if it's a boss round or normal round
    if (roundNumber % 5 != 0)
    {
        
        // generate random monster
        MonsterType randomMonster{monster.generateRandomMonster()};
        monster.monsterType = randomMonster;
        monster.setMonsterStats(randomMonster);
    }
    else {
        monster.monsterType = MonsterType::Dragon_King;
        monster.monsterDamage = boss.bossDamage;
        monster.monsterHealthPoints = boss.bossHealthPoints;
        monster.monsterRemainingHealthPoints = boss.bossHealthPoints;
    }
    

    using enum CharacterClasses;
    // int roundNumber{1}; // counts the current round number
    // int healingItems{0}; // count of healing items used by warrior class
    std::cout << "Round no. " << roundNumber << " starts";
    
    
    std::cout << "You have encountered a " << monster.monsterType;

    while (player.playerRemainingHealthPoints > 0 && monster.monsterRemainingHealthPoints > 0){
        // display player and enemy stats
        std::cout << player.charClass << "'s HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")                 " 
        << monster.monsterType << "'s HP(" << monster.monsterRemainingHealthPoints << "/" << monster.monsterHealthPoints << "\n";
        std::cout << "PLAYER TURN!\n";
        std::cout << "What will " << player.playerName << " do?\n";
        std::cout << "1. Attack           2. Heal\n";
        int playerAction{};
        std::cin >> playerAction;

        // TODO: handle bad input

        switch (playerAction){
            case 1: // player attacks
                std::cout << player.playerName << " deals " << player.playerDamage << " damage\n" ;
                monster.monsterRemainingHealthPoints -= player.playerDamage; // player deals damage equivalent to damage
                break;
            case 2: // player heals
                switch (player.charClass){
                    case Warrior:
                        if (healingItems <= 0){
                            std::cout << "No healing items in possession!\n";
                            continue;
                        }

                        std::cout << player.playerName << "uses a healing item\n";
                        std::cout << "restored 100 HP!";
                        player.playerRemainingHealthPoints += 100; // in case of warrior you get 1 heal per monster defeated each heal heals 100 hp
                        std::cout << player.charClass << "'s HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")"; // display player hp

                    case Mage:
                        std::cout << player.playerName << "casts a healing spell\n";
                        std::cout << "HP fully restored!";
                        player.playerRemainingHealthPoints = player.playerHealthPoints; // in case of mage he casts a heal spell which restores to full hp
                        std::cout << player.charClass << "'s HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")";
                }
        }
        if (monster.monsterRemainingHealthPoints <= 0) {
            std::cout << player.playerName << " successfully slayed " << monster.monsterType << "!";
            if (player.charClass == Warrior){ // warrior gets a healing item for each monster slayed
                ++healingItems;
            }
            // return true player won
            ++roundNumber;
            return true;
        }
        std::cout << "ENEMY TURN!\n";
        std::cout << "The " << monster.monsterType << " deals " << monster.monsterDamage << " damage ";
        player.playerRemainingHealthPoints -= monster.monsterDamage;
        // if (player.playerRemainingHealthPoints == 0){
        //     std::cout << "GAME OVER!\n";
        //     // return false player lost
        //     return false;
        // }
    }
    std::cout << "GAME OVER!\n";
    return false;

}

void startGame()
{
    char startTheGame{'n'};
    Boss boss{};
    Player player{};
    // input a name
    while (startTheGame != 'y'){
        std::string_view playerName{getPlayerName()};

        // choose a class
        CharacterClasses charClass{chooseCharacterClass()};

        // set the values of the player
        player.playerName = playerName;
        player.charClass = charClass;
        player.setPlayerStats(charClass);

        // display the player stats
        std::cout << "You have chosen the class: " << player.charClass << "\n";
        std::cout << "HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")";
        std::cout << "Attack: " << player.playerDamage;

        std::cout << "Would you like to start the game? (y/n): ";
        std::cin >> startTheGame;
        // TODO: handle bad inputs
    }
    std::cout << "The game begins!\n";
    
    int roundNumber{1};
    int healingItems{0};

    // we move proceed to next round as startRound is true (player beat the monster) 
    // or round number is less 5
    do {
        startRound(player, boss, roundNumber, healingItems);
    } while (startRound || roundNumber < 5);
    
     

    
}


int main()
{
    CharacterClasses charClass{chooseCharacterClass()};
    Player player{.playerName = "FBI", .charClass = charClass};
    player.setPlayerStats(charClass);
    printPlayerStats(player);
    return 0;
}
