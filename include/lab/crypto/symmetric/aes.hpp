#pragma once

#include <string>

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

using byte = u_char;

namespace lab::crypto::symmetric::aes
{

template< uint32_t K >
class aes_t
{
public:
    aes_t()
    {}

    ~aes_t()
    {}

    void encrypt( const byte* plain, const uint32_t input_sz, std::string& encrypted );

    void decrypt( const byte* encrypted, const uint32_t encrypted_sz, std::string& plain);

protected:

    template< typename T >
    void processing( T& transform,  const byte* input, 
                                    const std::size_t input_sz,
                                    std::string& output )
    {
        try
        {
            CryptoPP::StringSource ss( input, input_sz,
                                       true,
                                       new CryptoPP::StreamTransformationFilter
                                       (
                                            transform,
                                            new CryptoPP::StringSink(output)
                                       ) );
        }
        catch(const CryptoPP::Exception& e)
        { std::cerr << e.what() << std::endl; }
        
    }

private:
    static constexpr char* key = "key";
    static constexpr char* iv = "iv";
};



template< uint32_t K >
void aes_t<K>::encrypt( const byte* plain, const uint32_t input_sz, std::string& encrypted )
{
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encr;
    encr.SetKeyWithIV( (byte*)key, K/8, (byte*)iv );
    processing<CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption>(encr, plain, input_sz, encrypted );
}

template< uint32_t K >
void aes_t<K>::decrypt( const byte* encrypted, const uint32_t encrypted_sz, std::string& plain )
{
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decr;
    decr.SetKeyWithIV( (byte*)key, K/8, (byte*)iv );
    processing<CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption>(decr, encrypted, encrypted_sz, plain );
}


}