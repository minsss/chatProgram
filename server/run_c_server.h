//
//  run_c_server.h
//  communucation
//
//  Created by Minsu Lee on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//

#ifndef run_c_server_h
#define run_c_server_h

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

#include "run_n_server.h"

#define PORT 9001
#define MAX_CLIENT 10

int run_c_server();

#endif /* run_c_server_h */
