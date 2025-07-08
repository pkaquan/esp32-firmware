#ifndef AESEncrytion_H
#define AESEncrytion_H

#include <Arduino.h>
#include <mbedtls/aes.h>

class AESEncrytion {
private:
    mbedtls_aes_context aes;
    static const size_t size = 16;
    unsigned char iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    String key = "abcdefghijklmnop";
public:
    AESEncrytion();

    String encrypt(String plainText);
    String decrypt(String hexCipherText);
};

#endif