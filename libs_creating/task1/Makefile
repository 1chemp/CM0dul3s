### static linking ###

finish_static: static
	gcc calc_v3.c -L. -lxxx -o result -lm
static: st_sqr st_sqrt
	ar rc libxxx.a sqr.o sqrt.o
	ranlib libxxx.a
st_sqr:
	gcc -c sqr.c -o sqr.o
st_sqrt:
	gcc -c sqrt.c -o sqrt.o

### dynamic linking ###

finish_dynamic: dynamic
	gcc -c calc_v3.c
	gcc calc_v3.o -L. -lyyy -o result -lm

dynamic: dyn_sqr dyn_sqrt
	gcc -shared -o libyyy.so sqr.o sqrt.o
dyn_sqr:
	gcc -fPIC -c sqr.c -o sqr.o
dyn_sqrt:
	gcc -fPIC -c sqrt.c -o sqrt.o

### linking with prog main.c  ###
main: finish_dynamic
	gcc -c main.c
	gcc main.o -L. -lyyy -o main -lm

### cleaning ###
clean:
	rm result sqr.o sqrt.o libxxx.a libyyy.so calc_v3.o | echo "Files deleted but find errors"
	
