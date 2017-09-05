#include "Application.h"
#include "Util/Config.h"

int main()
{
    Config config;
    config.width    = 1280;
    config.height   = 720;

    Application app(config);
    app.run();
}
