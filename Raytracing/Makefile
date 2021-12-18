src_files = $(wildcard ./src/*.cc)
headers = $(wildcard ./src/*.h)
build_path = ./build/main

COMPILER = g++
CXXFLAGS = -pedantic -O3
all: build

build: $(src_files) $(headers)
	$(COMPILER) $(CXXFLAGS) -o $(build_path) $(src_files)
run: all 
	./build/main > image.ppm
out: build
	./build/main