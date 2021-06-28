include ../Makefile.template

CC		= clang
CFLAGS	= -Wall -Werror -Wextra -Iinclude -g
LD		= clang

SRCS	= $(addprefix src/, main.c setup.c philo_watcher.c output.c	\
		  philo_routine.c thread.c error.c utils.c get_timestamp.c)

HEADERS	= $(addprefix include/, philo.h)

OBJS	= $(LIB_OBJS) $(SRCS:%.c=%.o)

TARGET	= philo

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS) 
	@$(LD) $(OBJS)  -lpthread $(LD_FLAGS) -o $(TARGET) 
	@printf "LD\t$(TARGET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "CC\t$<\n"
