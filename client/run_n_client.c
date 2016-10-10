//
//  run_n_client.c
//  communication
//
//  Created by csrc on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//

#include "run_n_client.h"

#define PORT 9001
#define IPADDR "127.0.0.1"

char quit[] = ":quit";

pthread_t thread_1, thread_2;
int g_socket;

void *send_message(void *);
void *recv_message(void *);

void sig_handler(int);   //ctrl+c handler

int run_n_client()
{
    int c_socket;
    struct sockaddr_in c_addr;
    int len;
    int n;
    
    c_socket = socket(PF_INET, SOCK_STREAM, 0);
    g_socket = c_socket;
    //printf("%d\n", c_socket);
    
    bzero((char *) &c_addr, sizeof(c_addr));
    c_addr.sin_addr.s_addr = inet_addr(IPADDR);
    c_addr.sin_family = AF_INET;
    c_addr.sin_port = htons(PORT);
    
    if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) < -1) {
        printf("Can't connect\n");
        close(c_socket);
        return -1;
    }

    signal(SIGINT, sig_handler);
    
    pthread_create(&thread_1, NULL, send_message, (void *) c_socket);
    pthread_create(&thread_2, NULL, recv_message, (void *) c_socket);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    
    close(c_socket);
}

void* send_message(void *arg)
{
    char chatData[1024];
    char buf[1024];
    int n;
    int c_socket = (int) arg;

    while(1) {
	memset(buf, 0, sizeof(buf));

	if((n = read(0, buf, sizeof(buf))) > 0) {
	    sprintf(chatData, "%s", buf);
	    write(c_socket, chatData, strlen(chatData));

	    if(!strncmp(buf, quit, strlen(quit))) {
		pthread_kill(thread_2, SIGINT);
		break;
	    }
	}
    }
}

void* recv_message(void *arg)
{
    char chatData[1024];
    int n;
    int c_socket = (int) arg;

    while(1) {
	memset(chatData, 0, sizeof(chatData));
	if((n = read(c_socket, chatData, sizeof(chatData))) > 0 ) {
	    write(1, chatData, n);
	}
    }
}

void sig_handler(int sig)
{
    write(g_socket, quit, strlen(quit));
    pthread_kill(thread_2, SIGINT);
}