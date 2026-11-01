#include <limits>
#include <iostream>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

bool extractionFailed()
{
    if (!std::cin)
    {
        std::cin.clear();
        ignoreLine();
        return true;
    }
    return false;
}
