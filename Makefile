.PHONY: all build rebuild unistall clean cppcheck clang-format tests dist dvi

all: build

build: install

rebuild: clean install

install:
	cmake -S . -B ./build
	cmake --build ./build -j $(nproc)

unistall:
	find ./ -name "build" -type d -exec rm -rf {} +

clean: unistall
	find . -name "*.user" -type f -delete
	rm -rf ./agents/*

define AGENT_TARGET
$(1): $(1)_agent
endef

$(foreach agent, cpu memory network system, $(eval $(call AGENT_TARGET,$(agent))))

%_agent:
	cmake -S ./model/agents/$*/ -B ./model/agents/$*/build -DLBD_TARGET=${CURDIR}/build
	cmake --build ./model/agents/$*/build -j$(nproc)

cppcheck:
	cd build; make cppcheck

clang-format:
	cd build; make clang-format

dist: clean
	tar -czvf MonitoringSystem.tar.gz ./*

dvi:
	pandoc -s ./docs/doc.tex -o ./docs/doc.html