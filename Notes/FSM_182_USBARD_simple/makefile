CC=gcc
LIB=-L./

all:resultado

resultado:creation_7.o creation_7_func.o
	${CC} creation_7.o creation_7_func.o -Wall -lm -o FSM.exe ${LIB}

resultado.o:creation_7.c
	${CC} -c creation_7.c -Wall -lm -o creation_7.o ${LIB}

resultado_func.o:creation_7_func.c
	${CC} -c creation_7_func.c -Wall -lm -o creation_7_func.o ${LIB}

clean.o:
	rm *.o *.exe

