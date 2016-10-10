//
//  run_n_server.h
//  communucation
//
//  Created by csrc on 2016. 5. 24..
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

#include "run_n_login.h"

int run_n_server();

#endif /* run_n_server_h */
