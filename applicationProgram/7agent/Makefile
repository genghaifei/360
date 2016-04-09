SERVER_BIN=./server/tcp_server
CLIENT_BIN=./client/tcp_client
SERVER_SRC=./server/tcp_server.cpp
CLIENT_SRC=./client/tcp_client.cpp
FLAG=-gdwarf-2
LIB=-lpthread
GCC=g++

.PHONY:all

all:${SERVER_BIN} ${CLIENT_BIN}

${SERVER_BIN}:${SERVER_SRC}
	${GCC} -o $@ $^ ${LIB} ${FLAG}
${CLIENT_BIN}:${CLIENT_SRC}
	${GCC} -o $@ $^ ${FLAG}

.PHONY:clean

clean:
	@rm -rf ${CLIENT_BIN} ${SERVER_BIN}
