#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include <SFML/System/Vector2.hpp>

//anti-clockwise order
enum class Direction
{
    Up,
    Left,
    Down,
    Right,
};

enum class Turn
{
    Left, Right
};

class Ant
{
    public:
        Ant(int xPosition, int yPosition);

        void turn(Turn direction);

        void translate();

        const sf::Vector2i& getPosition() const { return m_position; }

    private:
        Direction       m_direction = Direction::Up;
        sf::Vector2i    m_position;
};

#endif // ANT_H_INCLUDED
