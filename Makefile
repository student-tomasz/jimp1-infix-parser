CC = gcc
CFLAGS = -Wall
SOURCES = token_stack.c operator.c translator.c expression.c main.c
OBJECTS = $(SOURCES:%.c=%.o)
EXECUTABLE = parser
TESTSDIR = tests
SOURCES_TESTS = $(SOURCES:%.c=$(TESTSDIR)/%.c)
OBJECTS_TESTS = $(SOURCES_TESTS:%.c=%.o)
EXECUTABLE_TESTS = $(EXECUTABLE)_tests

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

$(EXECUTABLE_TESTS): $(OBJECTS) $(OBJECTS_TESTS)
	$(CC) $(filter-out main.o, $(OBJECTS)) $(OBJECTS_TESTS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(OBJECTS_TESTS) $(EXECUTABLE_TESTS)

all: $(SOURCES) $(EXECUTABLE)

all_tests: $(SOURCES) $(SOURCES_TESTS) $(EXECUTABLE_TESTS)

run: all
	./$(EXECUTABLE)

test: all_tests
	./$(EXECUTABLE_TESTS);
