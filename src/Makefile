# CC specifies which compiler we're using
CC = g++ -std=c++11

# COMPILER_FLAGS specifies the additional compilation options we're using
# -Wall will turn on all standard warnings
COMPILER_FLAGS = -Wall

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -Wunknown-pragmas

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = a

#This is the target that compiles our executable
ass: assignment.o Mesh.o supportClass.o
		$(CC) assignment.o Mesh.o supportClass.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

assignment.o: assignment.cpp Mesh.h supportClass.h
		$(CC) assignment.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c

Mesh.o: Mesh.cpp supportClass.h
		$(CC) Mesh.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c

supportClass.o: supportClass.h
		$(CC) supportClass.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c

clean:
		rm *.o a