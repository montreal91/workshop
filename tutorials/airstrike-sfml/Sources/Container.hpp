
#pragma once


#include <vector>
#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "Component.hpp"


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
