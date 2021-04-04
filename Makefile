CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_printf.c


all : 
	./test.sh

normal :
	${CC} ${CFLAGS} ${SRCS} -o printf

test :
	${CC} ${CFLAGS} -D TEST ${SRCS} -o ft_printf

clean :
	rm printf ft_printf

re :
	clean all
