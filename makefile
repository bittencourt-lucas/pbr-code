CFILES=$(shell find src -name '*.cpp')
OFILES=$(patsubst %.cpp,%.o,$(CFILES))
TARGET=pbr
FLAGS=-Wall -Wextra -Wpedantic
-CC_FLAGS=-std=c++11

$(TARGET): $(OFILES)
		g++ -o $(TARGET) $(OFILES) $(FLAGS)

%.o: %.cpp
		g++ $(CC_FLAGS) -o $@ -c $<

clean:
		rm -rf $(TARGET) $(OFILES)