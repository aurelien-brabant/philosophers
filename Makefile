CC			= clang
CFLAGS		= -g -Wall -Wextra -Werror -Iinclude
LD			= clang
LD_FLAGS	= -g

RM			= rm -rf

LIB			= $(addprefix lib/, ft_strlen.c dputs.c parse_int.c error.c)

SRCS		= $(LIB) src/main.c

OBJS		= $(SRCS:%.c=%.o)

all: $(OBJS)
	$(LD) $(LD_FLAGS) $(OBJS) -o test

clean:
	$(RM) $(OBJS)

fclean: clean

re: fclean all

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
