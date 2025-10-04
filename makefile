# Nome dell'eseguibile
TARGET = main

# Sorgenti: SOLO .cpp, niente .h
SRCS = main.cpp \
       classes/Vector.cpp classes/Object.cpp classes/System.cpp \
       classes/Star.cpp classes/Planet.cpp classes/Moon.cpp \
       classes/Comet.cpp classes/TestMass.cpp \
       classes/NewtonianForce.cpp classes/parser/Parser.cpp

# Compilatore
CXX = g++

# Opzioni di compilazione
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -Iclasses -Iclasses/parser

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
