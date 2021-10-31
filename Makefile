prodcon: prodcon.o producer.o consumer.o tands.o buffer.o global.h
	gcc -g prodcon.o producer.o consumer.o tands.o buffer.o -o prodcon -lpthread 

prodcon.o: 
	gcc -g -c prodcon.c -o prodcon.o -lpthread

consumer.o: consumer.h buffer.h
	gcc -g -c consumer.c -o consumer.o -lpthread

producer.o: producer.h buffer.h
	gcc -g -c producer.c -o producer.o -lpthread

tands.o: tands.h
	gcc -g -c tands.c -o tands.o -lpthread

buffer.o: buffer.h
	gcc -g -c buffer.c -o buffer.o -lpthread

clean:
	rm prodcon.o  buffer.o tands.o consumer.o producer.o