
#pragma once


#include <map>
#include <string>
#include <memory>
#include <stcexcept>
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
    const Resource& Get( Identifier id );

private:
    void InsertResource( Identifier id, std::unique_ptr<Resource> resource );

    std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
};

#include "resource_holder.inl"
} // namespace rh
