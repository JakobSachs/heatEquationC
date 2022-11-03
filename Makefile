CC=gcc
LDFLAGS=
CFLAGS=   
OBJ = main.c

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f main *.o
