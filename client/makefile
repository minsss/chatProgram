OBJECTS = main.o run_n_client.o run_c_client.o run_c_crypt.o

CC = gcc
CFLAGS = -c

TARGET = chat

$(TARGET) : $(OBJECTS)
	gcc -o $(TARGET) -pthread -ggdb -Wall -Wextra $(OBJECTS) -lcrypto

main.o : main.c
	gcc -c main.c

run_n_client.o : run_n_client.c
	gcc -c run_n_client.c

run_c_client.o : run_c_client.c
	gcc -c run_c_client.c

run_c_crypt.o : run_c_crypt.c
	gcc -c run_c_crypt.c

clean :
	rm $(TARGET) $(OBJECTS)
