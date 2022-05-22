all: bank

bank: main.o functions.o utility.o
	gcc -g $^ -Wall -pedantic -fsanitize=undefined -o $@

.c.o: 
	gcc -g -Wall -fsanitize=undefined -pedantic -c $<

main.o: main.c functions.h utility.h types.h

functions.o: functions.h functions.c constants.h

utility.o: utility.h utility.c

clean:
	-rm main.o functions.o utility.o bank
