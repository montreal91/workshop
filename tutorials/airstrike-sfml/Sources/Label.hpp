

#ifndef __LABEL_HPP__
#define __LABEL_HPP__


#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/Text.hpp>


namespace GUI {

class Label : public Component {
public:
    typedef std::shared_ptr<Label> Ptr;

    Label( const std::string& text, const FontHolder& fonts );

    virtual bool    isSelectable() const;
    void            setText( const std::string& text );

    virtual void    handleEvent( const sf::Event& event );

private:
    void        draw( sf::RenderTarget& target, sf::RenderStates states ) const;

    sf::Text    mText;
};

} // namespace GUI

#endif // __LABEL_HPP__
