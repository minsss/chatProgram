//
//  run_c_client.c
//  communication
//
//  Created by Minsu Lee on 2016. 5. 24..
//  Copyright © 2016년 mins. All rights reserved.
//

#include "run_c_client.h"
#include "run_n_client.h"
#include "run_c_crypt.h"

char quit_c[] = ":quit";
char *g_name;
char *private_key;
char *public_key;

pthread_t thread_1, thread_2;
int g_socket;

void *send_c_message(void *);
void *recv_c_message(void *);

int run_c_client()
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

    if((g_name = malloc(MAX_INPUT_SIZE)) == NULL) {
	perror("Memory problem\n");
	return -1;
    }

    printf("Type your name [MAX 20] : ");
    if(fgets(g_name, MAX_INPUT_SIZE, stdin) == NULL) {
	perror("Too long name was typed\n");
	return -1;
    }
    g_name[strlen(g_name) - 1] = '\0';   //remove 'enter'

/*---------------------------------------------------------------------keySet*/
    RSA *keypair = keyGen();

    if((private_key = setPrivatekey(keypair)) == NULL) {
	fprintf(stderr, "private key generation failure\n");
	return -1;
    }

    if((public_key = setPublickey(keypair)) == NULL) {
	fprintf(stderr, "public key generation failure\n");
	return -1;
    }
/*---------------------------------------------------------------------------*/
    
    if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) < -1) {
        printf("Can't connect\n");
        close(c_socket);
        return -1;
    }

    signal(SIGINT, sig_handler);
    
    pthread_create(&thread_1, NULL, send_c_message, (void *) c_socket);
    pthread_create(&thread_2, NULL, recv_c_message, (void *) c_socket);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    
    close(c_socket);
}

void* send_c_message(void *arg)
{
    char chatData[1024];
    char buf[1024];
    int n;
    int c_socket = (int) arg;

    time_t timer;
    struct tm *t;
    timer = time(NULL);
    t = localtime(&timer);

    write(c_socket, public_key, strlen(public_key));   //public key initialization to server

    while(1) {
	memset(buf, 0, sizeof(buf));

	if((n = read(0, buf, sizeof(buf))) > 0) {
	    
	    sprintf(chatData, "[%s %d/%d %d:%d] %s", g_name, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, buf);
	    write(c_socket, chatData, strlen(chatData));

	    if(!strncmp(buf, quit_c, strlen(quit_c))) {
		pthread_kill(thread_2, SIGINT);
		break;
	    }
	}
    }
}

void* recv_c_message(void *arg)
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
