all: build

build: install

rebuild: clean install

install:
	cmake -S . -B ./build
	cmake --build ./build

unistall:
	find ./ -name "build" -type d -exec rm -rf {} +

clean: unistall
	find . -name "*.user" -type f -delete
	rm -rf ./lib/*

tests:
	cmake -S ./test/ -B ./test/build
	cmake --build ./test/build
	./test/build/TEST

cppcheck: install
	cmake --build . --target cppcheck

clang-format: install
	cmake --build . --target clang-format

dist: clean
	tar -czvf MonitoringSystem.tar.gz ./*

dvi:
	pandoc -s ./docs/doc.tex -o ./docs/doc.html

.PHONY: all build rebuild unistall clean cppcheck clang-format tests dist dvi
