TARGET = tester
ROMAN_LIB = roman

CC = gcc
CFLAGS := -fPIC -Wall -g
LDFLAGS = -shared
RM = rm -f

SRCS = roman.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: lib$(ROMAN_LIB).so $(TARGET)

$(TARGET): lib$(ROMAN_LIB).so
	$(CC) main.c -o $@ $(ROMAN_LIB).o -lcheck -lsubunit -lpthread -lrt -lm

lib$(ROMAN_LIB).so: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(SRCS:.c):%.c
	$(CC) $(CFLAGS) -MM $< >$

include $(SRCS:.c)

.PHONY: clean
clean:
	-${RM} $(TARGET) lib${ROMAN_LIB}.so ${OBJS} $(SRCS:.c)


