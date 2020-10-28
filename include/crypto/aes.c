#include "aes.h"

// 64 bit key_des
static const char key_des[8] = "qwertyy";
// < ------------------------------ DES --------------------------------> //
                                                                          //
void des_encrpt( const char* plain, char* cipher )                        //
{                                                                         //
    DES_cblock des_key, input, output;                                    //
    DES_key_schedule sched;                                               //
                                                                          //
    DES_string_to_key( key_des, &des_key );                               //
                                                                          //
    memcpy( &input, plain, 8 );                                           //
                                                                          //
    DES_set_key_checked( &des_key, &sched );                              //
                                                                          //
    DES_ecb_encrypt(&input, &output, &sched, DES_ENCRYPT);                //
                                                                          //
    memcpy( cipher, &output, sizeof(output) );                            //
    //std::cout << "Cipher: " << cipher << std::endl;                     //
}                                                                         //
                                                                          //
void des_decrpt( const char* cipher, char* plain )                        //
{                                                                         //
    DES_cblock des_key, input, output;                                    //
    DES_key_schedule sched;                                               //
                                                                          //
    DES_string_to_key( key_des, &des_key );                               //
                                                                          //
    memcpy( &input, cipher, 8 );                                          //
                                                                          //
    DES_set_key_checked( &des_key, &sched );                              //
                                                                          //
    DES_ecb_encrypt( &input, &output, &sched, DES_DECRYPT);               //
                                                                          //
    memcpy( plain, &output, sizeof(output) );                             //
    //std::cout << "Cipher: " << plain << std::endl;                      //
                                                                          //
}                                                                         //
                                                                          //
// < ------------------------------ DES --------------------------------> //



// < ------------------------------ AES --------------------------------> //
                                                                          //
// 128 bit key_aes                                                        //
static const byte key_aes[16] = "key_aes";                                //
                                                                          //
void aes_encrpt( const byte* plain, uint32_t plain_sz, byte* cipher )     //
{                                                                         //
    AES_KEY aes_key;                                                      //
    AES_set_encrypt_key( key_aes, 128, &aes_key );                        //
                                                                          //
    AES_encrypt( plain, cipher, &aes_key );                               //
                                                                          //
    //std::cout << "Plain: " << plain << std::endl;                       //
    //std::cout << "Cipher: " << cipher << std::endl;                     //
    //std::cout << "sizeof(cipher):: " << sizeof(cipher) << std::endl;    //
}                                                                         //
                                                                          //
void aes_decrpt( const byte* cipher, byte* plain )                        //
{                                                                         //
    AES_KEY aes_key;                                                      //
    AES_set_decrypt_key( key_aes, 128, &aes_key );                        //
                                                                          //
    AES_decrypt( cipher, plain, &aes_key );                               //
                                                                          //
    //std::cout << "Cipher: " << cipher << std::endl;                     //
    //std::cout << "Plain: " << plain << std::endl;                       //
    //std::cout << "sizeof(cipher):: " << sizeof(plain) << std::endl;     //
                                                                          //
}                                                                         //
                                                                          //
// < ------------------------------ AES --------------------------------> //