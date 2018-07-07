TARGET  = trie
CC      = gcc
CFLAGS  =  -Wall -I. -Wno-initializer-overrides -Wno-unused-function
OBJ     = file.o trie.o
HEADERS = file.h trie.h stream.h

INSTALL_DEST = /usr/local/bin

.PHONY: default all clean test install uninstall

default: run

install: $(TARGET)
	chmod 755 ./$(TARGET)
	cp ./$(TARGET) $(INSTALL_DEST)/$(TARGET)

uninstall:
	rm $(INSTALL_DEST)/$(TARGET)

run: $(TARGET)
	./$(TARGET)

test-$(TARGET): test.o
	$(CC) $(OBJ) test.o $(CFLAGS) -o $@

test: test-$(TARGET)
	./test-$(TARGET)

$(TARGET): $(OBJ) main.o
	$(CC) $(OBJ) main.o $(CFLAGS) -o $@

debug: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -g -o $(TARGET)-debug

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o
	$(RM) $(TARGET)-debug
	$(RM) -r $(TARGET)-debug.dSYM
	$(RM) $(TARGET)
