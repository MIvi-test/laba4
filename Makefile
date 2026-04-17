CC = gcc
TESTFLAGS = -Wall -g -Wextra -pedantic
CFLAGS = -O3 -Wall -g
SOFLAGS = -shared -fPIC -Wall -O2

UNIT_TARGET = unit_test
TARGET = main
SO_LIB = ld_preload.so

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes


all: run_hook


$(UNIT_TARGET).out: $(UNIT_TARGET).c
	$(CC) $(UNIT_TARGET).c $(TESTFLAGS) -o $(UNIT_TARGET).out


test: $(UNIT_TARGET).out
	./$(UNIT_TARGET).out


$(SO_LIB): hooks.c
	$(CC) hooks.c $(SOFLAGS) -o $(SO_LIB)

$(TARGET).out: $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET).out


run_hook: $(UNIT_TARGET).out
	@echo "--- Running Tests ---"
	./$(UNIT_TARGET).out
	@echo "--- Tests Passed. Building Hooks and Main ---"
	$(MAKE) $(SO_LIB)
	$(MAKE) $(TARGET).out
	@echo "--- Running Main with LD_PRELOAD ---"
	LD_PRELOAD=./$(SO_LIB) ./$(TARGET).out

clean:
	rm -f *.out *.so
