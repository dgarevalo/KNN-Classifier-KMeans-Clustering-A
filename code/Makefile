# Nombre del archivo ejecutable
TARGET = program

# Compilador y flags
CC = g++
CFLAGS = -std=c++11

# Archivos fuente y objeto
SRC_FILES = main.cpp kmeans.cpp kmedoids.cpp dataset.cpp AvaluacioClustering.cpp randIndex.cpp generator.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Reglas
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)