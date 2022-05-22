all: bank

bank: main.o functions.o utility.o menu.o
	gcc -g $^ -Wall -pedantic -fsanitize=undefined -o $@

.c.o: 
	gcc -g -Wall -fsanitize=undefined -pedantic -c $<

main.o: main.c functions.h utility.h types.h menu.h

functions.o: functions.h functions.c constants.h

utility.o: utility.h utility.c

menu.o: menu.h menu.c types.h functions.h utility.h

clean:
	-rm main.o functions.o utility.o bank
