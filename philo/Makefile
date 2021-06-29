include ../Makefile.template

CC		= clang
CFLAGS	= -Wall -Werror -Wextra -Iinclude -g
LD		= clang

SRCS	= $(addprefix src/, main.c data.c output.c philo.c thread.c	error.c	\
		  utils.c time.c)

HEADERS	= $(addprefix include/, philo.h)

OBJS	= $(LIB_OBJS) $(SRCS:%.c=%.o)

TARGET	= philo

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS) 
	@$(LD) $(OBJS)  -lpthread $(LD_FLAGS) -o $(TARGET) 
	@printf "\033[1;39mLD\t\033[1;32m$(TARGET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;39mCC\033[0m\t$<\n"
