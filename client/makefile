OBJECTS = main.o run_n_client.o

CC = gcc
CFLAGS = -c

TARGET = chat

$(TARGET) : $(OBJECTS)
	gcc -o $(TARGET) -pthread $(OBJECTS)

main.o : main.c
	gcc -c main.c

run_n_client.o : run_n_client.c
	gcc -c run_n_client.c

clean :
	rm $(TARGET) $(OBJECTS)
