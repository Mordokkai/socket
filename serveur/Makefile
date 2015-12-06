
CC=g++

OBJ=main.o #database.o response.o query.o client.o server.o server_connection.o

a.out : $(OBJ)
	$(CC) -o $@ $+


#server : server_connection.hpp
#database.o : response.hpp query.hpp

%.o:%.cpp %.hpp
	$(CC) -c -o $@ $<

clean :
	rm $(OBJ) a.out
