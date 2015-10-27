
#include "ParallelTask.hpp"


ParallelTask::ParallelTask() :
mThread( &ParallelTask::runTask, this ),
mFinished( false ) {
}

void
ParallelTask::execute() {
    mFinished = false;
    mElapsedTime.restart();
    mThread.launch();
}

bool
ParallelTask::isFinished() {
    sf::Lock lock( mMutex );
    return mFinished;
}

float
ParallelTask::getCompletion() {
    sf::Lock lock( mMutex );

    // 100% at 10 seconds of elapsed time
    return mElapsedTime.getElapsedTime().asSeconds() / 10.0f;
}

void
ParallelTask::runTask() {
    bool ended = false;

    while ( !ended ) {
        sf::Lock lock( mMutex );
        if ( mElapsedTime.getElapsedTime().asSeconds() >= 10.0f ) {
            ended = true;
        }
    }

    {
        sf::Lock lock( mMutex );
        mFinished = true;
    }
}