CFLAGS = `pkg-config --cflags opencv4`
LIBS= `pkg-config --libs opencv4`

eyetrack: eyetrack.cpp
		g++ $(CFLAGS) -o eyetrack eyetrack.cpp $(LIBS)

main: main.cpp App.cpp Model.cpp
		g++ $(CFLAGS) -o eyetrack main.cpp App.cpp Model.cpp $(LIBS)

