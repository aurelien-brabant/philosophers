include ../Makefile.template

SRCS	= $(addprefix src/, main.c setup.c philosopher.c philo_change_state.c \
			philo_watcher.c fork.c get_mutexes.c get_philosophers.c output_status.c)
OBJS	= $(LIB_OBJS) $(SRCS:%.c=%.o)

LIB_PHILO_PATH	:= ../lib

TARGET	= philo_one

all: $(TARGET)

$(TARGET): $(OBJS) include/philo_one.h
	make -C $(LIB_PHILO_PATH)
	$(LD) $(OBJS) -L$(LIB_PHILO_PATH) -lphilo -lpthread $(LD_FLAGS) -o $(TARGET) 
