TARGET=fakesign

CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc

all: $(TARGET)

NV_OBJS=fakesign.o


$(TARGET): $(NV_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(TARGET) *.o


