CC = g++
CFLAGS = -std=c++11 -lz
OBJS = src/parse.o src/request.o src/response.o src/socket.o src/tools.o src/compress.o src/server.o

myhttpd: src/myhttpd.cpp $(OBJS)
	$(CC) $(CFLAGS) src/myhttpd.cpp $(OBJS) -o myhttpd

src/parse.o: src/parse.cpp
src/request.o:
src/response.o:
src/socket.o:
src/tools.o:
src/compress.o:
src/server.o:

clean:
	rm src/*.o

install:
	sudo ln -s src/myhttpd /usr/bin/myhttpd