all: nfv_parse.a nfv_resource.o nfv_assignment.o nfv_execute.o nfv_symtab.o

nfv_parse.a:
	cd parse/ ; make

nfv_resource.o:
	cd models/ ; make

nfv_symtab.o:
	cd models/ ; make

nfv_assignment.o:
	cd models/ ; make

nfv_execute.o:
	cd execution/ ; make

clean:
	cd parse/; make clean
	cd models/; make clean
	cd execution/; make clean
