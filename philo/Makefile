include ../Makefile.template

CC		= clang
CFLAGS	= -Wall -Werror -Wextra -Iinclude
LD		= clang

SRCS	= $(addprefix src/, main.c setup.c spawn_philosopher.c				\
			philo_change_state.c philo_watcher.c mutex.c output_status.c	\
			philo_routine.c thread.c error.c)

HEADERS	= $(addprefix include/, philo.h)

OBJS	= $(LIB_OBJS) $(SRCS:%.c=%.o)

TARGET	= philo

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS) 
	@$(LD) $(OBJS)  -lpthread $(LD_FLAGS) -o $(TARGET) 
	@printf "LD\t$(TARGET)\n"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
