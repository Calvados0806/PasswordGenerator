#include <cstdio>
#include <cstring>

#include "PassGen.hpp"

PassGen::PassGen(size_t len, Complexity comp) :
    alphabets(), complexity(comp), length(len)
{
    for (size_t i = 0; i < 4; ++i) {
        alphabets[i] = new char[sizes[i]];
    }
    std::sprintf(alphabets[0], "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::sprintf(alphabets[1], "abcdefghijklmnopqrstuvwxyz");
    std::sprintf(alphabets[2], "0123456789");
    std::sprintf(alphabets[3], "~!@#$%%^&*_-+=?<>");
}

PassGen::PassGen(const PassGen& pg) : length(pg.length), complexity(pg.complexity)
{
    for (size_t i = 0; i < 4; ++i) {
        alphabets[i] = new char[sizes[i]];
        std::memcpy(alphabets[i], pg.alphabets[i], sizes[i]);
    }
}

PassGen& PassGen::operator=(const PassGen& pg)
{
    if (this != &pg) {
        length = pg.length;
        complexity = pg.complexity;
    }
    return *this;
}

PassGen::~PassGen()
{
    for (size_t i = 0; i < 4; ++i)
        delete alphabets[i];
}

size_t PassGen::get_length() const
{
    return length;
}

void PassGen::set_length(size_t len)
{
    length = len;
}

Complexity PassGen::get_complexity() const
{
    return complexity;
}

void PassGen::set_complexity(Complexity comp)
{
    complexity = comp;
}

std::uniform_int_distribution<> PassGen::_get_randomizer(Complexity comp) const
{
    switch (comp) {
        case Complexity::EASY:
            return std::uniform_int_distribution<>(0, 1);
        case Complexity::MEDIUM:
            return std::uniform_int_distribution<>(0, 2);
        case Complexity::HARD:
            return std::uniform_int_distribution<>(0, 3);
    }
}

std::string PassGen::generate() const
{
    std::random_device dv;
    std::mt19937 gen(dv());
    auto dist = _get_randomizer(complexity);

    char buff[length+1];
    buff[length] = 0;

    for (size_t i = 0; i < length; ++i) {
        int alp_ind = dist(gen);
        std::uniform_int_distribution<> alp_dist(0, sizes[alp_ind] - 1);
        buff[i] = alphabets[alp_ind][alp_dist(gen)];
    }

    return std::string(buff);
}