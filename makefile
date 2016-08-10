FILES = arquivo.o ArquivoIndexado.o ArvoreB.o registro.o Cliente.o

all: $(FILES)
	gcc $^ -o cliente -Wall -ggdb

%.o: %.c
	gcc -c $^ -o $@ -Wall -ggdb

clean:
	rm cliente *.o
