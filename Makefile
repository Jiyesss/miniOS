# Compiler and Compiler Flags
CC=gcc
CFLAGS=-Wall -g -Iinclude 
# Linker flags
LDFLAGS=-lreadline -lpthread

# The build target executable:
TARGET=minios

# Source, Object files
# kernel/20211318/fork.c  kernel/20211318/montecarlo.c kernel/20211318/round_robin.c
SRCS = kernel/kernel.c kernel/system.c kernel/20211318/fork.c  kernel/20211318/ipc_pipe.c kernel/20211318/montecarlo_multi.c kernel/20211318/rr_process.c

OBJS=$(SRCS:.c=.o) 

# Include directory
INCLUDE_DIR=include

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# To obtain object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up:
clean:
	rm -f $(OBJS) $(TARGET)
