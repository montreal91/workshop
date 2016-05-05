
#pragma once


#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "src/ih/category.h"
#include "src/ih/command.h"


namespace ih {
struct EsCommand;
} // namespace ih


namespace nodes {
class ESceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<ESceneNode> Ptr_t;

    ESceneNode();

    void                    AttachChild( Ptr_t child );
    Ptr_t                   DetachChild( const ESceneNode& node );

    void                    Update( const sf::Time& dt );

    sf::Vector2f            GetWorldPosition() const; // ??? or b2Vec2?
    sf::Transform           GetWorldTransform() const;

    void                    OnCommand(
        const ih::EsCommand& command,
        const sf::Time& dt
    );
    virtual unsigned int    GetCategory() const;

private:
    virtual void    UpdateCurrent( const sf::Time& dt );
    void            UpdateChildren( const sf::Time& dt );

    virtual void    draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    virtual void    DrawCurrent(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;
    void            DrawChildren(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;

    std::vector<Ptr_t>  m_children;
    ESceneNode*         m_parent;
};

} // namespace nodes
