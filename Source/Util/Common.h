#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Random.h"
#include "Config.h"

unsigned getIndex(unsigned width, unsigned x, unsigned y);

enum class ItrDirection
{
    Increase,
    Decrease
};

template<typename F>
void iterateInDirection(ItrDirection direction,
                        unsigned lower_bound,
                        unsigned upper_bound,
                        F action)
{
    switch(direction)
    {
        case ItrDirection::Increase:
            for (unsigned i = lower_bound; i < upper_bound; i++)
            {
                action(i);
            }
            break;

        case ItrDirection::Decrease:
            for (unsigned i = upper_bound - 1; i > lower_bound; i--)
            {
                action(i);
            }
            break;
    }
}

//This loops the cells in a random order, eg might go from bottom left to top right,
//or top left to bottom right.
//This is there is less bias towards a certain direction
template<typename F>
void randomCellForEach(const Config& config, F f)
{
    auto xDir = (ItrDirection)Random::get().intInRange(0, 1);
    auto yDir = (ItrDirection)Random::get().intInRange(0, 1);

    iterateInDirection(yDir, 0, config.height, [&](auto y)
    {
        iterateInDirection(xDir, 0, config.width, [&](auto x)
        {
            f(x, y);
        });
    });
}


template<typename F>
void cellForEach(const Config& config, F f)
{
    iterateInDirection(ItrDirection::Increase, 0, config.height, [&](auto y)
    {
        iterateInDirection(ItrDirection::Increase, 0, config.width, [&](auto x)
        {
            f(x, y);
        });
    });
}

#endif // COMMON_H_INCLUDED
