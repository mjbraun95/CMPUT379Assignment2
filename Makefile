prodcon: prodcon.o producer.o consumer.o tands.o myqueue.o globalvariables.h
	gcc -g prodcon.o producer.o consumer.o tands.o myqueue.o -o prodcon -lpthread 

prodcon.o: 
	gcc -g -c prodcon.c -o prodcon.o -lpthread

consumer.o: consumer.h myqueue.h
	gcc -g -c consumer.c -o consumer.o -lpthread

producer.o: producer.h myqueue.h
	gcc -g -c producer.c -o producer.o -lpthread

tands.o: tands.h
	gcc -g -c tands.c -o tands.o -lpthread

myqueue.o: myqueue.h
	gcc -g -c myqueue.c -o myqueue.o -lpthread

clean:
	rm prodcon.o  myqueue.o tands.o consumer.o producer.o