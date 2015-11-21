
#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__


#include "Component.hpp"

#include <vector>
#include <memory>


namespace GUI {

class Container : public Component {

public:
    typedef std::shared_ptr<Container> Ptr;

    Container();

    void            pack( Component::Ptr Component );

    virtual bool    isSelectable() const;
    virtual void    handleEvent( const sf::Event& event );

private:
    virtual void    draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    bool            hasSelection() const;
    void            select( std::size_t index );
    void            selectNext();
    void            selectPrevious();

    std::vector<Component::Ptr> mChildren;
    int                         mSelectedChild;

};
} // namespace GUI

#endif // __CONTAINER_HPP__
