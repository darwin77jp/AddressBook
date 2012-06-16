CC=g++
LIB=
LIBDIR=-L/opt/local/lib
INCDIR=-I/opt/local/include
CFLAGS= -Wall -std=c++0x -fpermissive
TARGETS=client
SRCS=client.cpp
OBJS=$(SRCS:.cpp=.o)

all: $(TARGETS) $(OBJS)

$(TARGETS): $(OBJS) 
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(INCDIR) $(LIBDIR) $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) -c $< $(INCDIR) $(LIBDIR) $(LIB)

.PHONY: clean
clean:
	$(RM) *~ $(TARGETS) $(OBJS)
