OBJECTS = test.o lib/models/nfv_resource.o lib/models/nfv_assignment.o lib/parse/nfv_parse.a \
	lib/execution/nfv_execute.o

test: test.c lib/models/nfv_resource.o lib/parse/nfv_parse.a lib/models/nfv_assignment.o \
	lib/execution/nfv_execute.o
	gcc -c -Wall --pedantic -o test.o test.c
	gcc -Wall --pedantic -o test $(OBJECTS)

lib/parse/nfv_parse.a: lib/parse/*.l lib/parse/*.y
	cd lib/parse ; make

lib/models/nfv_resource.o: lib/models/*.c lib/models/*.h
	cd lib/models ; make

lib/models/nfv_assignment.o: lib/models/*.c lib/models/*.h
	cd lib/models ; make

lib/execution/nfv_execute.o: lib/execution/*.c lib/execution/*.h
	cd lib/execution ; make

clean:
	cd lib/ ; make clean
