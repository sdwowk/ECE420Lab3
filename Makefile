CFLAGS = -lm -pthread -lpthread -gstabs+

lab3: lab3.c 
	gcc -ggdb -Wall -o lab3 lab3.c $(CFLAGS)

datagen: datagen.c
	gcc datagen.c Lab3IO.c -o datagen

serialtester: serialtester.c
	gcc serialtester.c Lab3IO.c -o serialtester -lm

	


