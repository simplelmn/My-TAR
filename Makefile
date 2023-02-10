CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = src/*.c  my_tar.c
TARGET = my_tar

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)