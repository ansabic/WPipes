cmake_minimum_required(VERSION 3.7)

project(WPipes)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(WPipes main.cpp common/CommonFunctions.cpp common/CommonFunctions.h model/Pipe.cpp model/Pipe.h model/PositionedPipe.cpp model/PositionedPipe.h model/Point.cpp model/Point.h common/Constants.h model/Game.cpp model/Game.h contoller/Controller.cpp contoller/Controller.h view/View.cpp view/View.h)
target_link_libraries(WPipes ${SDL2_LIBRARIES})




