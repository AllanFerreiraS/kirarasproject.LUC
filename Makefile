CXX = g++
CXXFLAGS = -std=c++17

SRC = main.cpp \
./src/Luc.cpp \
./src/Luc.debug.cpp \
./src/Luc.datatype.cpp \
./src/Luc.unit.cpp \
./src/Luc.parse.cpp \
./src/Luc.dimension.cpp \
./src/Luc.temperature.cpp \
./src/Luc.kirarasproject.logo.cpp 

OUT = luc

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)