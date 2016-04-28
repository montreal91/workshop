
#include "command_queue.h"

namespace ih {

void
ECommandQueue::Push( const EsCommand& command ) {
    this->m_queue.push( command );
}

EsCommand
ECommandQueue::Pop() {
    EsCommand command = this->m_queue.front();
    this->m_queue.pop();
    return command;
}

bool
ECommandQueue::IsEmpty() const {
    return this->m_queue.empty();
}

} // namespace ih
