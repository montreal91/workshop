
#pragma once


#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


// rh stands for resource holder
namespace rh {

template <typename Resource, typename Identifier>
class EtResourceHolder {
public:
    void Load( Identifier id, const std::string& filename );

    template<typename Parameter>
    void Load( Identifier id, const std::string& filename, const Parameter& second_param );

    Resource& Get( Identifier id );
    const Resource& Get( Identifier id ) const;

private:
    void InsertResource( Identifier id, std::unique_ptr<Resource> resource );

    std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
};

// #include "resource_holder.inl"
template <typename Resource, typename Identifier>
void
EtResourceHolder<Resource, Identifier>::Load(
    Identifier id,
    const std::string& filename
) {
    std::unique_ptr<Resource> resource( new Resource() );
    if ( !resource->loadFromFile( filename ) ) {
        throw std::runtime_error(
            "EtResourceHolder::Load - Failed to load " + filename
        );
    } else {
        this->InsertResource( id, std::move( resource ) );
    }
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void
EtResourceHolder<Resource, Identifier>::Load(
    Identifier id,
    const std::string& filename,
    const Parameter& second_param
) {
    std::unique_ptr<Resource> resource( new Resource() );
    if ( !resource->loadFromFile( filename, second_param ) ) {
        throw std::runtime_error(
            "EtResourceHolder::Load - Failed to load " + filename
        );
    } else {
        this->InsertResource( id, std::move( resource ) );
    }
}

template <typename Resource, typename Identifier>
Resource&
EtResourceHolder<Resource, Identifier>::Get( Identifier id ) {
    auto found = this->m_resource_map.find( id );
    assert( found != this->m_resource_map.end() );

    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource&
EtResourceHolder<Resource, Identifier>::Get( Identifier id ) const {
    auto found = this->m_resource_map.find( id );
    assert( found != this->m_resource_map.end() );

    return *found->second;
}

template <typename Resource, typename Identifier>
void
EtResourceHolder<Resource, Identifier>::InsertResource(
    Identifier id,
    std::unique_ptr<Resource> resource
) {
    auto inserted = this->m_resource_map.insert(
        std::make_pair( id, std::move( resource ) )
    );
    assert( inserted.second );
}
} // namespace rh
