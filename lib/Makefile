include ../Makefile.template

SRCS		:= $(addprefix src/, ft_strlen.c dputs.c parse_uint.c error.c parse_params.c)

OBJS	:= $(SRCS:%.c=%.o)

TARGET	:= libphilo.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)
