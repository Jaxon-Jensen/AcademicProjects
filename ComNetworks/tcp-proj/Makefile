all: client server

client: client.c
	gcc -Wall -Wstrict-prototypes -Wmissing-prototypes -ansi -pedantic-errors -D_DEFAULT_SOURCE -o client client.c

server: server.c
	gcc -Wall -Wstrict-prototypes -Wmissing-prototypes -ansi -pedantic-errors -D_DEFAULT_SOURCE -o server server.c


debug: client_debug server_debug

client_debug: client.c
	gcc -g -Wall -Wstrict-prototypes -Wmissing-prototypes -ansi -pedantic-errors -D_DEFAULT_SOURCE -o client_debug client.c

server_debug: server.c
	gcc -g -Wall -Wstrict-prototypes -Wmissing-prototypes -ansi -pedantic-errors -D_DEFAULT_SOURCE -o server_debug server.c