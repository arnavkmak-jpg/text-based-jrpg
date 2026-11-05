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
        Boss boss{};
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
            case Dragon_King:
                monsterHealthPoints = boss.bossHealthPoints;
                monsterDamage = boss.bossDamage;
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
                playerHealthPoints = 200;
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
        std::cout << "1. Warrior\n";
        std::cout << "2. Mage\n";
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

std::string getPlayerName()
{
    std::string playerName{};

    while (playerName.length() < 3 || playerName.length() > 10){
        std::cout << "Please input your name (3-10 characters): ";
        std::cin >> playerName;
        if (playerName.length() < 3 || playerName.length() > 10){
            std::cout << "name characters out of given range, please input again!\n";
            continue;
        }
        
    }
    

    return playerName;
}



bool startRound(Player& player, int roundNumber, int healingItems)
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
    else { // boss fight case
        MonsterType bossType{MonsterType::Dragon_King};
        monster.monsterType = bossType;
        monster.setMonsterStats(bossType);
        std::cout << "Congratulations! You made it to the final boss!\n";
    }
    

    using enum CharacterClasses;
    // int roundNumber{1}; // counts the current round number
    // int healingItems{0}; // count of healing items used by warrior class
    std::cout << "Round no. " << roundNumber << " starts\n";
    
    
    std::cout << "You have encountered a " << monster.monsterType << "\n";

    while (player.playerRemainingHealthPoints > 0 && monster.monsterRemainingHealthPoints > 0){
        // display player and enemy stats
        std::cout << player.charClass << "'s HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")                 " 
        << monster.monsterType << "'s HP(" << monster.monsterRemainingHealthPoints << "/" << monster.monsterHealthPoints << ")\n";
        int playerAction{0};
        
        while (playerAction < 1 || playerAction > 2){
            std::cout << "PLAYER TURN!\n";
            std::cout << "What will " << player.playerName << " do?(1/2)\n";
            std::cout << "1. Attack           2. Heal\n";
        
            std::cin >> playerAction;
            if (extractionFailed()){
                std::cout << "Bad input please input again!\n";
                playerAction = 0;
                continue;
            }
            ignoreLine();
        }
        

        switch (playerAction){
            case 1: // player attacks
                std::cout << player.playerName << " deals " << player.playerDamage << " damage\n" ;
                monster.monsterRemainingHealthPoints -= player.playerDamage; // player deals damage equivalent to damage

                std::cout << player.charClass << "'s HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")                 " 
               << monster.monsterType << "'s HP(" << monster.monsterRemainingHealthPoints << "/" << monster.monsterHealthPoints << ")\n";
                
                break;
            case 2: // player heals
                switch (player.charClass){
                    case Warrior:
                        if (healingItems <= 0){
                            std::cout << "No healing items in possession!\n";
                            continue;
                        }

                        if (player.playerRemainingHealthPoints == player.playerHealthPoints){
                            std::cout << "failed to use heal, hp is already full!\n";
                            continue;
                        }

                        std::cout << player.playerName << " uses a healing item\n";
                        std::cout << "restored 100 HP!\n";
                        if (player.playerHealthPoints - player.playerRemainingHealthPoints < 100){
                            player.playerRemainingHealthPoints = player.playerHealthPoints;
                        }
                        else {
                            player.playerRemainingHealthPoints += 100; // in case of warrior you get 1 heal per monster defeated each heal heals 100 hp
                        }
                        --healingItems;
                        std::cout << player.charClass << "'s HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")"; // display player hp
                        break;
                    case Mage:
                        std::cout << player.playerName << "casts a healing spell\n";
                        std::cout << "HP fully restored!";
                        player.playerRemainingHealthPoints = player.playerHealthPoints; // in case of mage he casts a heal spell which restores to full hp
                        std::cout << player.charClass << "'s HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")";
                        break;
                }
        }
        if (monster.monsterRemainingHealthPoints <= 0) {
            std::cout << player.playerName << " successfully slayed " << monster.monsterType << "!\n";
            if (player.charClass == Warrior){
                std::cout << "1 healing item gained!\n";
            }
            return true;
        }
        std::cout << "ENEMY TURN!\n";
        std::cout << "The " << monster.monsterType << " deals " << monster.monsterDamage << " damage\n";
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

bool playAgain()
{
    char playerInputPlayAgain{};
    
    while (playerInputPlayAgain != 'y' && playerInputPlayAgain != 'n'){
        std::cout << "Would you like to play again?(y/n): ";
        std::cin >> playerInputPlayAgain;
        if (extractionFailed()){
            std::cout << "bad input please try again!\n";
            continue;
        }
        ignoreLine();
    }

    if (playerInputPlayAgain == 'y') return true;
    return false;
}

void startGame()
{
    char startTheGame{'n'};
    Player player{};
    // input a name
    while (startTheGame != 'y'){
        std::string playerName{getPlayerName()};

        // choose a class
        CharacterClasses charClass{chooseCharacterClass()};

        // set the values of the player
        player.playerName = playerName;
        player.charClass = charClass;
        player.setPlayerStats(charClass);

        // display the player stats
        std::cout << "You have chosen the class: " << player.charClass << "\n";
        std::cout << "HP(" << player.playerRemainingHealthPoints << "/" << player.playerHealthPoints << ")\n";
        std::cout << "Attack: " << player.playerDamage << "\n";

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
        startRound(player, roundNumber, healingItems);
        ++roundNumber;
        if (player.charClass == CharacterClasses::Warrior){
            ++healingItems;
        }
    } while (startRound(player, roundNumber, healingItems) && roundNumber < 5);
    
     
    if (roundNumber > 5)
    {
        std::cout << "Congratulations! you successfully slayed the final boss and beat the final stage!\n";
    }

    
    
}


int main()
{
    do {
    startGame();
    } while (playAgain());
    return 0;
}
