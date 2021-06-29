CC		= clang
CFLAGS	= -Wall -Werror -Wextra -Iinclude -g
LD		= clang

RM		= rm -rf

SRCS	= $(addprefix src/, main.c output.c philo.c error.c	run_philo.c utils.c	\
		  time.c process.c)

HEADERS	= $(addprefix include/, philo_bonus.h)

OBJS	= $(SRCS:%.c=%.o)

TARGET	= philo_bonus

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS) 
	@$(LD) $(OBJS)  -lpthread $(LD_FLAGS) -o $(TARGET) 
	@printf "\033[1;39mLD\t\033[1;32m$(TARGET)\n"

clean:
	@$(RM) $(OBJS)
	
fclean: clean
	@$(RM) $(TARGET)

re: fclean all

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;39mCC\033[0m\t$<\n"
