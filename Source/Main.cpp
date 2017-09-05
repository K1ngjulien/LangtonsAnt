#include "Application.h"
#include "Util/Config.h"

int main()
{
    Config config;
    config.width    = 1280;
    config.height   = 720;

    std::string inputBuffer;
    std::cout << "How many ants? ";
    std::cin >> inputBuffer;

    for (auto c : inputBuffer)
    {
        if (!std::isdigit(c))
        {
            std::cout << "Invalid input, must be a number greater than 0\n";
            main(); //hacky af but it works
        }
    }
    int n = std::stoi(inputBuffer);

    Application app(n, config);
    app.run();
}
