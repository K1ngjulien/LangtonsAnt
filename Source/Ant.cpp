#include "Ant.h"

Ant::Ant(int xPosition, int yPosition)
:   m_position  (xPosition, yPosition)
{ }

void Ant::turn(Turn direction)
{
    int right = int(Direction::Right);
    int dir = (int)m_direction;
    switch (direction)
    {
        case Turn::Left:
            dir--;
            break;

        case Turn::Right:
            dir++;
            break;
    }

    if (dir < 0)
        dir = right;
    else if (dir > right)
        dir = 0;

    m_direction = Direction(dir);
}

void Ant::translate()
{
    switch (m_direction)
    {
        case Direction::Up:
            m_position.y--;
            break;

        case Direction::Down:
            m_position.y++;
            break;

        case Direction::Left:
            m_position.x--;
            break;

        case Direction::Right:
            m_position.x++;
            break;
    }
}
