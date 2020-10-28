#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <libmodbus/src/modbus-tcp.h>
#include <libmodbus/src/modbus.h>

#include <lab/configure/modb/modbus.conf.hpp>
#include <lab/concurency/thread_channel.hpp>

namespace lab::modbus::master
{

using lab::config::modbus::modbus_tcp_conf;
using test::concurency::destruct_method;
using test::concurency::thread_channel;

class master_t
{

using raii_thread = thread_channel;
using uniq_thread = std::unique_ptr< raii_thread >;

public:
    master_t()
    {}

    ~master_t()
    {
        for(auto& e : conn )
        {
            modbus_close( e );
            modbus_free( e );
        }
    }

    void config( const modbus_tcp_conf& proto )
    {
        try
        {
            conn.resize( proto.modb.conf.size() );
            for( auto& e : conn )
            {
                e = modbus_new_tcp( proto.modb.conf[ &e - &conn[0] ].host.c_str(),
                                    proto.modb.conf[ &e - &conn[0] ].port );

                if( modbus_connect( e ) == -1 )
                    throw std::exception();
            }
        }
        catch(const std::exception& e)
        { std::cout << e.what() << '\n'; }

    }

    void start_listen()
    {
        thread_.resize( conn.size() );
        for( std::size_t ix = 0; ix < thread_.size(); ++ix )
        {
        
        
            std::thread( &master_t::handle, 
                                    this, 
                                    std::ref(conn[ ix ]) ).join();
        
        
        /*
            thread_[ix] = std::make_unique< raii_thread >( std::thread( &master_t::handle,
                                                                        this,
                                                                        conn[ ix ] ),
                                                 destruct_method::join);
        */

        }

    }

protected:

    static uint16_t f()
    { return std::rand() % 10; }

    void handle( modbus_t* socket )
    {
        uint16_t tab_reg[6];

        for( std::size_t i = 0; i < sizeof(tab_reg)/sizeof(uint16_t); ++i )
            tab_reg[i] = i;

        int rc = -1;
        
        rc = modbus_write_registers( socket, 0, sizeof(tab_reg)/sizeof(uint16_t), tab_reg );
        if( rc == -1 )
        {
             std::cout << "Error modbus_write_registers: " << errno << std::endl;
             exit(1);
        }

        rc = modbus_read_registers( socket, 0, sizeof(tab_reg)/sizeof(uint16_t), tab_reg );
        if( rc == -1 )
        {
             std::cout << "Error modbus_read_registers: " << errno << std::endl;
             exit(1);
        }

        for ( std::size_t i=0; i < rc; i++)
            printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
    }

private:
    std::vector< modbus_t* > conn;
    std::vector< uniq_thread > thread_;
};

} // namespace lab::modbus::master