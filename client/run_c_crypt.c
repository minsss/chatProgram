#include "run_c_crypt.h"

RSA* keyGen()
{
    printf("Key generated...\n");
    fflush(stdout);
    RSA *keypair = RSA_generate_key(KEY_LENGTH, PUB_EXP, NULL, NULL);

    return keypair;
}

char * setPrivatekey(RSA *keypair)
{
    size_t pri_len;            // Length of private key
    char *private_key;           // Private key

    BIO *pri = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
    pri_len = BIO_pending(pri);

    private_key = malloc(pri_len + 1);
    BIO_read(pri, private_key, pri_len);
    private_key[pri_len] = '\0';

    printf("%s\n", private_key);

    return private_key;
}

char * setPublickey(RSA *keypair)
{
    size_t pub_len;            // Length of public key
    char *public_key;           // Public key

    BIO *pub = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(pub, keypair);
    pub_len = BIO_pending(pub);

    public_key = malloc(pub_len + 1);
    BIO_read(pub, public_key, pub_len);
    public_key[pub_len] = '\0';

    printf("%s\n", public_key);

    return public_key;
}

int encrypt()
{
    char msg[KEY_LENGTH/8];  // Message to encrypt
    char *cypertext = NULL;    // Encrypted message
    char *plaintext = NULL;    // Decrypted message
    char *err;               // Buffer for any error messages


}


