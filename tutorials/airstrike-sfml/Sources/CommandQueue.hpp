
#ifndef __COMMAND_QUEUE_HPP__
#define __COMMAND_QUEUE_HPP__

#include "Command.hpp"

#include <queue>


class CommandQueue {
public:
    void    push( const Command& command );
    Command pop();
    bool    isEmpty() const;

private:
    std::queue<Command> mQueue;
    
};

#endif // __COMMAND_QUEUE_HPP__
