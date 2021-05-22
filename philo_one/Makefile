include ../Makefile.template

SRCS	= $(addprefix src/, main.c setup.c)
OBJS	= $(LIB_OBJS) $(SRCS:%.c=%.o)

LIB_PHILO_PATH	:= ../lib

TARGET	= philo_one

all: $(TARGET)

$(TARGET): $(OBJS) include/philo_one.h
	make -C $(LIB_PHILO_PATH)
	$(LD) $(OBJS) -L$(LIB_PHILO_PATH) -lphilo $(LD_FLAGS) -o $(TARGET) 
