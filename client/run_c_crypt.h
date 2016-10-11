//
//  run_c_crypt.h
//  communication
//
//  Created by Minsu Lee on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//

#ifndef run_c_crypt_h
#define run_c_crypt_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include <signal.h>

#define KEY_LENGTH  2048
#define PUB_EXP     3
#define PRINT_KEYS
#define WRITE_TO_FILE

RSA* keyGen();
char * setPrivatekey(RSA *keypair);
char * setPublickey(RSA *keypair);

#endif
