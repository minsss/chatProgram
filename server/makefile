OBJECTS = main.o run_n_server.o run_c_server.o

CC = gcc
CFLAGS = -c

TARGET = server

$(TARGET) : $(OBJECTS)
	gcc -o $(TARGET) -pthread $(OBJECTS)

main.o : main.c
	gcc -c main.c

run_n_server.o : run_n_server.c
	gcc -c run_n_server.c

run_c_server.o : run_c_server.c
	gcc -c run_c_server.c

clean :
	rm $(OBJECTS) $(TARGET)
