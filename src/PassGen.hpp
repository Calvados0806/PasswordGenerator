#ifndef PASSGEN_HPP
#define PASSGEN_HPP


#include <cstddef>
#include <cstdint>
#include <string>
#include <random>

enum class Complexity : uint8_t { EASY, MEDIUM, HARD };

class PassGen
{
private:
    std::uniform_int_distribution<> _get_randomizer(Complexity) const;
public:
    PassGen() : alphabets(), complexity(Complexity::EASY), length(0)
    {}
    PassGen(size_t, Complexity);
    PassGen(const PassGen&);
    ~PassGen();

    PassGen& operator=(const PassGen&);

    size_t get_length() const;
    void   set_length(size_t);
    Complexity get_complexity() const;
    void    set_complexity(Complexity);
    std::string generate() const;

private:
    char*       alphabets[4];
    Complexity  complexity;
    size_t      length;
    size_t      sizes[4]{ 26, 26, 10, 16 };
};


#endif // PASSGEN_HPP
