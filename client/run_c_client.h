//
//  run_c_client.h
//  communication
//
//  Created by Minsu Lee on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//

#ifndef run_c_client_h
#define run_c_client_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

#include <signal.h>

#define PORT 9001
#define IPADDR "127.0.0.1"
#define MAX_INPUT_SIZE 20

#define KEY_LENGTH 2048
#define PUB_EXP    3

int run_c_client();

#endif /* run_c_client_h */
