include ../Makefile.template

SRCS	= $(addprefix src/, main.c setup.c spawn_philosopher.c philo_change_state.c \
			philo_watcher.c output_status.c philo_routine.c semaphore.c			\
			semaphore2.c error.c)
OBJS	= $(LIB_OBJS) $(SRCS:%.c=%.o)

LIB_PHILO_PATH	:= ../lib

TARGET	= philo_three

all: $(TARGET)

$(TARGET): $(OBJS) include/philo_three.h include/philo_error.h
	make -C $(LIB_PHILO_PATH)
	@$(LD) $(OBJS) -L$(LIB_PHILO_PATH) -lphilo -lpthread $(LD_FLAGS) -o $(TARGET) 
	@printf "LD\t$(TARGET)\n"
