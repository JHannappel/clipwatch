project(clipwatch)
cmake_minimum_required(VERSION 2.6)

#find_package(Qt5 COMPONENTS QtCore QtGui REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS}  ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -O2 -g -Wall -pthread -fstack-protector-all -Wstack-protector -Woverloaded-virtual -Wextra -Wshadow -Wsuggest-attribute=noreturn")
set(CMAKE_AUTOMOC ON)
set(Clipwatch_SRCS main.cpp clipWatch.cpp)
add_executable(clipwatch ${Clipwatch_SRCS})
#target_link_libraries(clipwatch ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTWIDGETS_LIBRARY})
target_link_libraries(clipwatch Qt5::Core Qt5::Gui Qt5::Widgets)

install(TARGETS clipwatch RUNTIME DESTINATION bin)
