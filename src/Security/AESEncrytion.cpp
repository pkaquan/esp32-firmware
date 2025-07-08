#include "AESEncrytion.h"

AESEncrytion::AESEncrytion() {
    mbedtls_aes_init(&aes);
}




String AESEncrytion::encrypt( String plainText) {
    unsigned char output[size];
    unsigned char iv_copy[size];
    memcpy(iv_copy, iv, size);

    // Pad the input to block size
    String paddedText = plainText;
    int padding = size - (plainText.length() % size);
    for (int i = 0; i < padding; i++) {
        paddedText += (char)padding;
    }
    mbedtls_aes_setkey_enc(&aes, (const unsigned char*)key.c_str(), key.length() * 8);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, paddedText.length(), iv_copy, (const unsigned char*)paddedText.c_str(), output);
    String hexString = "";
    for (size_t i = 0; i < size; i++) {
        if (output[i] < 0x10) {
            hexString += "0";
        }
        hexString += String(output[i], HEX);
    }
    hexString.toUpperCase();
    return hexString;
}

String AESEncrytion::decrypt(String hexCipherText) {
    unsigned char cipherBytes[size];
    unsigned char decrypted[size];
    unsigned char iv_copy[size];
    memcpy(iv_copy, iv, size);
    for (size_t i = 0; i < hexCipherText.length() / 2; i++) {
        String byteString = hexCipherText.substring(i * 2, i * 2 + 2);
        cipherBytes[i] = (unsigned char)strtol(byteString.c_str(), NULL, 16);
    }
    mbedtls_aes_setkey_dec(&aes, (const unsigned char*)key.c_str(), key.length() * 8);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, size, iv_copy, cipherBytes, decrypted);
    return String((char*)decrypted);
}