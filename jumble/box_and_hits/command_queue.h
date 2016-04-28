
#pragma once

#include <queue>

#include "command.h"

class ESceneNode;


namespace ih {
class ECommandQueue {
public:
    void        Push( const EsCommand& command );
    EsCommand   Pop();
    bool        IsEmpty() const;

private:
    std::queue<EsCommand> m_queue;
};

} // namespace ih
