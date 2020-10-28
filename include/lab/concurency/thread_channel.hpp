#pragma once

#include <iostream>
#include <thread>

namespace test::concurency
{

/**
 * @brief Enum for further execution
 */
enum class destruct_method{ join, detach };

/**
 * @class RAII thread channel class
 * 
 */
class thread_channel
{
public:

    thread_channel(std::thread th, destruct_method jd ):
                   method_(jd),
                   thread_(std::move(th))
    {}

    ~thread_channel()
    { std::cout << "~thread_channel" << std::endl; std::cin.get(); cleanup(); }

    /**
     * @brief Return thread instance
     * 
     * @return std::thread& 
     */
    std::thread& get()
    { return (thread_); }

protected:

    void cleanup()
    {
        if( thread_.joinable() )
        {
            if( method_ == destruct_method::join )
                thread_.join();
            else
                thread_.detach();
        }
    }

private:
    destruct_method method_;
    std::thread thread_;

};

} // namespace test::concurency