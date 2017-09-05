#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "Util/FPSCounter.h"
#include "Ant.h"

struct Config;

class Application
{
    enum Cell
    {
        On,
        Off
    };

    public:
        Application(const Config& config);

        void run();

    private:
        void makeImage();
        void updateImage();

        void pollEvents();
        void input  (float dt);
        void update ();
        void render ();

        Ant m_ant;

        std::vector<Cell> m_cells;

        sf::RenderWindow m_window;

        FPSCounter m_fpsCounter;

        sf::Image           m_pixelBuffer;
        sf::Texture         m_pixelSurfaceTex;
        sf::RectangleShape  m_pixelSurface;
        sf::Text            m_guiText;
        sf::View            m_view;

        const Config* m_pConfig = nullptr;
};

#endif // APPLICATION_H_INCLUDED
