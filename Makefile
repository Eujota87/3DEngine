build:
	gcc -std=c99 ./*.c -lm -lSDL2 -o engine3d
run: 
	./engine3d
clean:
	rm engine3d
