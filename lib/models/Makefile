AR = ar
CC = gcc
LD = gcc

CC_FLAGS = -Wall -Werror --pedantic -c -O3
LD_FLAGS = -Wall -Werror --pedantic -l -O3

OBJECTS = nfv_resource.o nfv_assignment.o

nfv_models.a:  $(OBJECTS)
	$(AR) r nfv_models.a $(OBJECTS)

%.o: %.c
	$(CC) $(CC_FLAGS) -o $@ $<

clean:
	rm -rf *.o
	rm -rf *.a
