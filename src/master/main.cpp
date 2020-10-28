#include <iostream>
#include <filesystem>

#include <lab/reader/reader.hpp>
#include <lab/reader/templates/json_reader.hpp>

#include <lab/configure/modb/modbus.conf.hpp>

#include <lab/modb/master.hpp>
#include <lab/modb/slave.hpp>

namespace fs = std::filesystem;

using lab::reader::reader_t;
using lab::reader::json_reader::json_reader_t;

using lab::config::modbus::modbus_tcp_conf;
using lab::config::modbus::modbus_mapping_conf;

using lab::modbus::master::master_t;

int main()
{
    const fs::path workdir = fs::current_path();
    const fs::path modbus_conf_path = workdir / "etc" / "json" / "modbus" / "modbus.conf.json";

    json_reader_t modbus_conf_json;
    reader_t<json_reader_t> reader_modbus_conf( modbus_conf_json );
    if( not reader_modbus_conf.open(modbus_conf_path) )
    {
        std::cout << "Json Modbus Config Reader Error" << std::endl;
        return -1;
    }

    modbus_tcp_conf modbus_conf_tcp( reader_modbus_conf.read() );
    modbus_mapping_conf modbus_conf_map( reader_modbus_conf.read() );

    try
    {
        master_t master;
        master.config( modbus_conf_tcp );
        master.start_listen();
    }
    catch( ... )
    {
        std::cerr << "Unknow std::exception" << '\n';
    }

    return 0;
}