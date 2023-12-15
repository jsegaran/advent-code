build:
	mkdir -p dist/
	gcc -o ./dist/d1 ./src/main.c

run: build
	cat ./inputs/input-1.txt | ./dist/d1

clean:
	rm -rf dist/
