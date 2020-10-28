#include <iostream>
#include <string>

#include <lab/crypto/symmetric/aes.hpp>

#include <lab/crypto/symmetric/aes.h>

using lab::crypto::symmetric::aes::aes_t;

int main()
{
/*
    char buf[20] = "Hello";
    std::string encrypt;
    std::string plain;

    aes_t<128> aes;
    aes.encrypt( (u_char*)buf, strlen(buf), encrypt );

    std::cout << buf << std::endl;
    std::cout << encrypt << std::endl;

    aes.decrypt( (u_char*)encrypt.c_str(), encrypt.size(), plain );

    std::cout << encrypt << std::endl;
    std::cout << plain << std::endl;
*/
    const char buf[8] = "0123456";
    char encr[20];
    char cipher[20];

    des_encrypt( buf, encr );
    des_decrypt( encr, cipher );

    const unsigned char buf1[16] = "Hello";
    unsigned char c[16] = "\0";
    unsigned char p[16] = "\0";
    aes_encrypt( buf1, sizeof(buf1), c );
    aes_decrypt( c, p );

    return 0;
}