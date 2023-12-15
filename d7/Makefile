build:
	mkdir -p dist/
	gcc -o ./dist/main ./src/main.c

run: build
	cat ./inputs/input-1.txt | ./dist/main

test: build
	cat ./inputs/input-2.txt | ./dist/main

clean:
	rm -rf dist/
