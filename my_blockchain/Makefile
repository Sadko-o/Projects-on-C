NAME = my_blockchain
CC = gcc
CFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra
HEADER = my_blockchain.h
all: ${NAME}

${NAME}: main.o my_blockchain.o  my_readline.o my_helper.o add.o rm.o other.o
	@${CC} ${CFLAGS} main.o my_blockchain.o  my_readline.o my_helper.o add.o rm.o other.o -o ${NAME}

main.o: main.c $(HEADER)
	@${CC} ${CFLAGS} -c main.c

my_blockchain.o: my_blockchain.c $(HEADER)
	@${CC} ${CFLAGS} -c my_blockchain.c

my_readline.o: my_readline.c $(HEADER)
	@${CC} ${CFLAGS} -c my_readline.c

my_helper.o: my_helper.c $(HEADER)
	@${CC} ${CFLAGS} -c my_helper.c

add.o: add.c $(HEADER)
	@${CC} ${CFLAGS} -c add.c

rm.o: rm.c $(HEADER)
	@${CC} ${CFLAGS} -c rm.c

other.o: other.c $(HEADER)
	@${CC} ${CFLAGS} -c other.c

clean:
	@rm  ${NAME} *.o

	