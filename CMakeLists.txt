cmake_minimum_required(VERSION 3.20)
project(WPipes)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(WPipes main.cpp common/CommonFunctions.cpp common/CommonFunctions.h model/Pipe.cpp model/Pipe.h model/PositionedPipe.cpp model/PositionedPipe.h model/Point.cpp model/Point.h common/Constants.h model/Game.cpp model/Game.h contoller/Controller.cpp contoller/Controller.h view/View.cpp view/View.h)
target_link_libraries(WPipes ${OpenGlLinkers}) # linking opengl libraries to the project




