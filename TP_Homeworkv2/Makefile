all:
	gcc cyclicRead.c -lrt -o read.o
	gcc cyclicWrite.c -lrt -o write.o

	gnome-terminal -x sh -c "sudo ./write.o|less"
	sudo ./read.o

clear:
	sudo rm -f *o a.out
