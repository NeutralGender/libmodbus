#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include <libmodbus/src/modbus.h>

#include <lab/configure/modb/modbus.conf.hpp>
#include <lab/concurency/thread_channel.hpp>

namespace lab::modbus::slave
{

using lab::config::modbus::modbus_tcp_conf;
using lab::config::modbus::modbus_mapping_conf;
using test::concurency::destruct_method;
using test::concurency::thread_channel;

class slave_t
{

using raii_mod = std::unique_ptr< modbus_t >;

using raii_thread = thread_channel;
using uniq_thread = std::unique_ptr< raii_thread >;

public:
    slave_t()
    {}

    ~slave_t()
    { std::cout << "~slave" << std::endl; }

    void cleanup()
    {
        for(auto& e : conn )
        {
            modbus_close( e );
            modbus_free( e );
        }
    }

    void config_tcp( const modbus_tcp_conf& proto )
    {
        try
        {
            conn.resize( proto.modb.conf.size() );
            for( auto& e : conn )
            {
                e = modbus_new_tcp( proto.modb.conf[ &e - &conn[0] ].host.c_str(),
                                    proto.modb.conf[ &e - &conn[0] ].port );
                
                listenfd = modbus_tcp_listen( e, proto.modb.conf[ &e - &conn[0] ].backlog );
            }
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    }

    void config_mapping( const modbus_mapping_conf& proto )
    {
        try
        {
            md_mapping = modbus_mapping_new( proto.modb.conf[0].nb_bits,
                                             proto.modb.conf[0].nb_input_bits,
                                             proto.modb.conf[0].nb_registers,
                                             proto.modb.conf[0].nb_input_registers );
            if( md_mapping == NULL )
                throw std::invalid_argument( "Mapping Arguments Error" );
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void start_listen()
    {
        thread_.resize( conn.size() );
        for( auto& e : thread_ )
        {
            std::thread( &slave_t::handle,this,conn[ &e - &thread_[0] ] ).join();

            /*
            e = std::make_unique< raii_thread >( std::thread( &slave_t::handle,
                                                                        this,
                                                                        conn[ &e - &thread_[0] ] ),
                                                 destruct_method::join);
            */

        }
    }

protected:

    void handle( modbus_t* socket )
    {
        std::cout << "Start thread" << std::endl;
        modbus_tcp_accept( socket, &listenfd );
        while( true )
        {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            
            int nrecv = -1;
            if( ( nrecv = modbus_receive( socket, query ) ) < 0 )
            {
                std::cout << "Receive Error: " << errno << std::endl;
                break;
            }
            
            int nsnd = -1;
            if( ( nsnd = modbus_reply( socket, query, nrecv, md_mapping ) ) < 0 )
                std::cerr << "modbus_reply Error: " << errno << std::endl;
        }
    }

private:
    int listenfd = {-1};
    std::vector< modbus_t* > conn;
    modbus_mapping_t* md_mapping;
    std::vector< uniq_thread > thread_;
};

} // namespace lab::modbus::slave