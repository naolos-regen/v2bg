CC	= gcc
CFLAGS	= -Wall -Wextra -g -I./includes
LDFLAGS = -lX11 -lmpv

SRCS	= src/main.c src/mpvgoat.c src/x11.c src/gl.c src/atoms.c
OBJS	= obj/main.o obj/mpvgoat.o obj/x11.o obj/gl.o obj/atoms.o

TARGET	= v2bg

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY:	all clean rebuild
