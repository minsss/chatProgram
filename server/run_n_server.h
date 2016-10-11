//
//  run_n_server.h
//  communucation
//
//  Created by Minsu Lee on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//

#ifndef run_n_server_h
#define run_n_server_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#include <pthread.h>

#define PORT 9001
#define MAX_CLIENT 10

int run_n_server();
int pushClient(int);
int popClient(int);

#endif /* run_n_server_h */
