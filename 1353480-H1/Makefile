CFLAGS = -lm -pthread -fopenmp -lpthread -gstabs+

lab3_openMP: lab3_openMP.c 
	gcc -ggdb -Wall -o main lab3_openMP.c Lab3IO.c $(CFLAGS)

lab3_serial: lab3_serial.c 
	gcc -ggdb -Wall -o lab3_serial lab3_serial.c Lab3IO.c $(CFLAGS)

datagen: datagen.c
	gcc datagen.c Lab3IO.c -o datagen

serialtester: serialtester.c
	gcc serialtester.c Lab3IO.c -o serialtester -lm

	


