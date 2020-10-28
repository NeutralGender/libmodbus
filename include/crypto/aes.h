#pragma once

#ifndef AES_CRYPTO_H
#define AES_CRYPTO_H

#include <string.h>

#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/err.h>
#include <openssl/evp.h>

typedef unsigned char byte;

void des_encrpt( const char* plain, char* cipher );

void des_decrpt( const char* cipher, char* plain );

void aes_encrpt( const byte* plain, uint32_t plain_sz, byte* cipher );

void aes_decrpt( const byte* cipher, byte* plain );

#endif /* AES_CRYPTO_H */