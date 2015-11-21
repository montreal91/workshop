
#ifndef __PARALLEL_TASK_HPP__
#define __PARALLEL_TASK_HPP__

#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>


class ParallelTask {
public:
    ParallelTask();

    void    execute();
    bool    isFinished();
    float   getCompletion();

private:
    void runTask();

    sf::Thread mThread;
    bool mFinished;
    sf::Clock mElapsedTime;
    sf::Mutex mMutex;

};

#endif // __PARALLEL_TASK_HPP__
