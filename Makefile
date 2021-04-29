SRC = src
OUTPUT = ouri
PARAMS = -g -O2

all:
	g++ $(PARAMS) $(wildcard $(SRC)/*.cpp) -o $(OUTPUT)

clean:
	rm ouri.exe