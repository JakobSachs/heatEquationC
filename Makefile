CC=gcc
LDFLAGS=  -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl
CFLAGS=  -m64 -I${MKLROOT}/include 
OBJ = main.c

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f main *.o
