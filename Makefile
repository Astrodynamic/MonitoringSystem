.PHONY: all build rebuild unistall clean cppcheck clang-format tests dist dvi

# Default target
all: build

# Build target with install as a dependency
build: install

# Clean and reinstall target
rebuild: clean install

# Install target
install:
	cmake -S . -B ./build
	cmake --build ./build -j $(nproc)

# Uninstall target
unistall:
	find ./ -name "build" -type d -exec rm -rf {} +

clean: unistall
	find . -name "*.user" -type f -delete
	rm -rf ./agents/*

# Agent targets (cpu, memory, network, system)
define AGENT_TARGET
$(1): $(1)_agent
endef

$(foreach agent, cpu memory network system, $(eval $(call AGENT_TARGET,$(agent))))

# Agent build target pattern
%_agent:
	cmake -DCMAKE_PREFIX_PATH:PATH=/home/astrodynamic/Qt/6.2.4/gcc_64 -S ./model/agents/$*/ -B ./model/agents/$*/build -DLBD_TARGET=/tmp/MonitoringSystem
	cmake --build ./model/agents/$*/build -j$(nproc)

# Test target
tests:
	cmake -S ./test/ -B ./test/build
	cmake --build ./test/build
	./test/build/TEST

# Cppcheck target
cppcheck:
	cd build; make cppcheck

# Clang-format target
clang-format:
	cd build; make clang-format

# Dist target
dist: clean
	tar -czvf MonitoringSystem.tar.gz ./*

# Dvi target
dvi:
	pandoc -s ./docs/doc.tex -o ./docs/doc.html