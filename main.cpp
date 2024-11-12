#include <iostream>
#include "textstatistik.h"

unsigned int minLength = 2;
unsigned int maxLength = 20;


struct Menu {
    char        item;
    std::string menuText;
    std::string Path;
};

const Menu mMenu[] {
        {'0', "buergschaft",    "buergschaft.txt"},
        {'1', "glocke",         "glocke.txt"}
};

int main() {

    char command;
    std::cout << "*** TEXTSTATISTIK ***" << std::endl;
    // alle menüpunkte anzeigen
    for(std::size_t i = 0; i < sizeof(mMenu)/ sizeof(Menu); ++i)
    {
        std::cout << "[" << mMenu[i].item << "] " << mMenu[i].menuText
                  << std::endl;
    }
    std::cin  >> command;
    for(std::size_t i = 0; i < sizeof(mMenu)/ sizeof(Menu); ++i)
    {
        if(command == mMenu[i].item)
        {
            std::string path = mMenu[i].Path;
            printStatistic(path, minLength, maxLength);
        }
    }

    return 0;
}
