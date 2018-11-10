#ifndef THREADSMANAGER_HPP
#define THREADSMANAGER_HPP

#include <thread>
#include <string>
#include "PassGen.hpp"

class ThreadsManager
{
private:
    std::string* _single_thread(PassGen&, size_t);
    std::string* _multi_threads(PassGen&, size_t);
    static void generate_passwords(const PassGen* const gen, std::string* const res,
                                   size_t start, size_t end);
public:
    ThreadsManager() : threads(nullptr)
    {}
    ThreadsManager(const ThreadsManager&) = delete;
    ~ThreadsManager();

    ThreadsManager& operator=(const ThreadsManager&) = delete;

    std::string* operator()(PassGen&, size_t);
    void join() const;
private:
    std::thread** threads;
    size_t        Nthreads = 7;
};


#endif //THREADSMANAGER_HPP
