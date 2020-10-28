#pragma once

#include <fstream>
#include <json/json.hpp>

namespace lab::reader::json_reader
{

using json = nlohmann::json;

class json_reader_t
{
public:
    json_reader_t()
    {}

    ~json_reader_t()
    { in.close(); }

    bool open(const std::string& path);

    const json& read();

    const json& get_data();

protected:

private:
    std::ifstream in;
    std::string data;
    json j;
};

bool json_reader_t::open(const std::string& path)
{
    in.open(path, std::ios_base::in);
    return ( not in.is_open() ) ? false : true;
}

const json& json_reader_t::read()
{
    std::copy( std::istream_iterator<char>{in}, std::istream_iterator<char>{}, std::back_inserter(data) );
    j = json::parse( data );

    return j;
}

} // namespace lab::reader::json_reader
