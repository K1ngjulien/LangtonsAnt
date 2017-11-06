#include "Application.h"
#include "Util/Config.h"

bool checkInput(std::string input)
{
    return std::stoi(input) <= 0;   //True if input is invalid
}

int main()
{
    Config config;
    config.width    = 1280;
    config.height   = 720;

    std::string inputBuffer;

    do    //Input and checking validity
    {
        std::cout << "\nHow many ants? [Enter a positive numbers] ";
        std::cin >> inputBuffer;

        if(checkInput(inputBuffer))
            std::cout << "Input must be greater than 0!\n";
    }
    while (checkInput(inputBuffer)); //Not as inefficient as filling the callstack with recursive calls

    std::cout << "Press Q to add more ants!\n";

    Application app(std::stoi(inputBuffer), config);
    app.run();
}


