#include "Application.h"

#include <iostream>
#include <ctime>
#include <thread>

#include "Util/Common.h"
#include "Native/Native.h"

#include "ResourceManager/ResourceHolder.h"

Application::Application(const Config& config)
:   m_window    ({config.width, config.height}, "Empire")
,   m_pConfig   (&config)
{
    m_view.setCenter({(float)config.width / 2, (float)config.height / 2});
    m_view.setSize  ({(float)config.width,     (float)config.height});

    m_pixelBuffer.create(m_pConfig->width, m_pConfig->height);
    updateImage();

    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    m_pixelSurface.setSize({(float)config.width, (float)config.height});
    m_pixelSurface.setTexture(&m_pixelSurfaceTex);

    m_guiText.setFont(ResourceHolder::get().fonts.get("arial"));
    m_guiText.setCharacterSize(15);
    m_guiText.move(10, 3);
}

void Application::run()
{
    sf::Clock deltaClock;
    unsigned year = 0;
    while (m_window.isOpen())
    {
        m_guiText.setString("Generation: " + std::to_string(year++));
        m_fpsCounter.update();

        input   (deltaClock.restart().asSeconds());
        update  ();

        m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
        render  ();
        pollEvents();
    }
}


void Application::pollEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::P)
            {
                std::thread(&Application::makeImage, this).detach();
            }
            if (e.key.code == sf::Keyboard::Up)
            {
                m_view.zoom(0.99);
            }
            if (e.key.code == sf::Keyboard::Down)
            {
                m_view.zoom(1.01);
            }
        }
    }
}

//Takes the pixels that makes up the people, and save it to an image
void Application::makeImage()
{
    static int imageCount = 0;
    std::cout << "Saving image... Please hold...\n";
    std::string fileName = "Screenshots/Screenshot" + std::to_string(imageCount++) + ".png";

    if (m_pixelBuffer.saveToFile(fileName))
    {
        std::cout << TextColour::Green << "Saved, to file " << fileName << "! Be aware, future sessions WILL OVERRIDE these images\n\n" << TextColour::Default;
    }
    else
    {
        std::cout << TextColour::Red << "Failed to save!\n\n" << TextColour::Default;
    }
}

void Application::updateImage()
{
    cellForEach(*m_pConfig, [&](unsigned x, unsigned y)
    {
        //m_pixelBuffer.setPixel(x, y, m_world.getColorAt(x, y));
    });
}

void Application::input(float dt)
{
    float speed = 100;
    sf::Vector2f change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.y -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x += speed;
    }

    m_view.move(change * dt);
}

void Application::update()
{
}

void Application::render()
{
    m_window.clear(sf::Color::Blue);

    //Pixels
    m_window.setView(m_view);
    m_window.draw(m_pixelSurface);

    //GUI
    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_guiText);
    m_fpsCounter.draw(m_window);

    m_window.display();
}

