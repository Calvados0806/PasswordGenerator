#include "ThreadsManager.hpp"

ThreadsManager::~ThreadsManager()
{
    if (threads != nullptr) {
        for (size_t i = 0; i < Nthreads; ++i)
            delete threads[i];
        delete[] threads;
    }
}

std::string* ThreadsManager::_single_thread(PassGen& gen, size_t count)
{
    std::string* res = new std::string[count];

    generate_passwords(&gen, res, 0, count);

    return res;
}

std::string* ThreadsManager::_multi_threads(PassGen& gen, size_t count)
{
    std::string* res = new std::string[count];
    threads = new std::thread*[Nthreads];

    for (size_t i = 0; i < Nthreads; ++i) {
        size_t start = i*(count/Nthreads);
        size_t end   = (i+1)*(count/Nthreads);

        threads[i] = new std::thread(generate_passwords, &gen, res, start, end);
    }
    generate_passwords(&gen, res, Nthreads*(count/Nthreads), count);

    return res;
}

void ThreadsManager::generate_passwords(const PassGen *const gen, std::string *const res,
                                        size_t start, size_t end)
{
    for (int i = start; i < end; ++i) {
        *(res + i) = std::move(gen->generate());
    }
}

std::string* ThreadsManager::operator()(PassGen& gen, size_t count)
{
    return count / Nthreads > 5 ?
           _multi_threads(gen, count) : _single_thread(gen, count);
}

void ThreadsManager::join() const
{
    if (threads != nullptr) {
        for (size_t i = 0; i < Nthreads; ++i)
            threads[i]->join();
    }
}