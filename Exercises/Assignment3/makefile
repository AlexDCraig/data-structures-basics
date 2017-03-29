default: prog

# Produce the two object files used to test the CircularList.
cirListDeque.o: cirListDeque.c cirListDeque.h
	gcc -Wall -g -std=c99 -c cirListDeque.c	

testCirListDeque.o: cirListDeque.h testCirListDeque.c
	gcc -Wall -g -std=c99 -c testCirListDeque.c

# Make the CircularList test.
prog: cirListDeque.o testCirListDeque.o 
	gcc -Wall -g -std=c99 -o prog cirListDeque.o testCirListDeque.o

#Produce the two object files used to test the LinkedListDeque.
linkedList.o: linkedList.c linkedList.h
	gcc -Wall -g -std=c99 -c linkedList.c

testLinkedList.o: linkedList.h testLinkedList.c
	gcc -Wall -g -std=c99 -c testLinkedList.c

# Make the LinkedList test.
testLink: linkedList.o testLinkedList.o
	gcc -Wall -g -std=c99 -o testLink linkedList.o testLinkedList.o

# Produce the two object files used to measure the Dynamic Array.
dynamicArray.o: dynamicArray.c dynamicArray.h
	gcc -Wall -g -std=c99 -c dynamicArray.c

dynamicArrayMain.o: dynamicArray.h dynamicArrayMain.c
	gcc -Wall -g -std=c99 -c dynamicArrayMain.c

# Make the DynamicArray measurer.
measureDynArr: dynamicArray.o dynamicArrayMain.o
	gcc -Wall -g -std=c99 -o measureDynArr dynamicArray.o dynamicArrayMain.o

# Produce the object file used to measure the Dynamic Array.
linkedListMain.o: linkedList.h linkedListMain.c
	gcc -Wall -g -std=c99 -c linkedListMain.c

# Make the LinkedList measurer.
measureLinkedList: linkedList.o linkedListMain.o
	gcc -Wall -g -std=c99 -o measureLinkedList linkedList.o linkedListMain.o

# erase the objects		
clean:
	rm cirListDeque.o
	rm testCirListDeque.o
	rm linkedList.o
	rm testLinkedList.o
	rm dynamicArray.o
	rm dynamicArrayMain.o
	rm measureDynArr 
	rm linkedListMain.o
	rm measureLinkedList
	rm prog
	rm testLink
