#pragma once

#include <json/json.hpp>

#include <vector>
#include <string>

namespace lab::config::modbus
{

using json = nlohmann::json;

struct tcp_t
{
    std::string host;
    uint16_t port;
    uint32_t backlog;
};

struct mapping_t
{
    uint32_t nb_bits;
    uint32_t nb_input_bits;
    uint32_t nb_registers;
    uint32_t nb_input_registers;
};

struct tcp_conf
{
    std::vector< tcp_t > conf;
};

struct mapping_conf
{
    std::vector< mapping_t > conf;
};

void from_json( const json& j, tcp_t& tcp )
{
    tcp.host = j["tcp"]["host"];
    tcp.port = j["tcp"]["port"];
    tcp.backlog = j["tcp"]["backlog"];
}

void from_json( const json& j, mapping_t& map )
{
    map.nb_bits = j["mapping"]["nb_bits"];
    map.nb_input_bits = j["mapping"]["nb_input_bits"];
    map.nb_registers = j["mapping"]["nb_registers"];
    map.nb_input_registers = j["mapping"]["nb_input_registers"];
}

void from_json( const json& j, tcp_conf& tcp_modb )
{
    for( auto& e : j )
        tcp_modb.conf.emplace_back( e );
}

void from_json( const json& j, mapping_conf& map_modb )
{
    for( auto& e : j )
        map_modb.conf.emplace_back( e );
}

class modbus_tcp_conf
{
public:
    modbus_tcp_conf( const json& j ):
                     modb( j )
    {}

    ~modbus_tcp_conf()
    {}

    const tcp_conf modb;
};

class modbus_mapping_conf
{
public:
    modbus_mapping_conf( const json& j ):
                     modb( j )
    {}

    ~modbus_mapping_conf()
    {}

    const mapping_conf modb;
};

} // namespace lab::config::modbus
