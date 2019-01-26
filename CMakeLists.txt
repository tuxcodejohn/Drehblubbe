cmake_minimum_required(VERSION 3.9)

project("QtDrehblubbe" CXX)

if(ANDROID)
	list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/qt-android-cmake/")
	include(AddQtAndroidApk)
endif()

set(GNUCXX_MINIMUM_VERSION "5.0")
set(CLANG_MINIMUM_VERSION "3.5")

# QT ENABLING STUFF:
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_EXPORT_COMPILE "ON" CACHE BOOL "Requried by clang.")

SET(WARNING_FLAGS "-Wall -Wextra -Wmissing-field-initializers -Wunused-parameter -Wno-unused-function")
SET(COMPILE_FLAGS "-std=c++11 -O0 -ggdb -pipe -static-libstdc++")
SET(LINK_FLAGS    "-static-libstdc++")



add_subdirectory("./libfmt/")


set(GUI_SRC_FILES
	./mainwindow.cc
	./Motor.cc
	./main.cc
)


if(ANDROID)
	add_library(Drehblubbe SHARED
		${GUI_SRC_FILES}
		)
else()
	add_executable(Drehblubbe
		${GUI_SRC_FILES}
		)
endif()

target_include_directories(Drehblubbe
	#PRIVATE ../src
	#PRIVATE ../src/util/
	PUBLIC ./
)

target_link_libraries(Drehblubbe
	pthread
	Qt5::Widgets
	Qt5::SerialPort
	fmt
)
#--------------------------------------------
if(ANDROID)
    include(qt-android-cmake/AddQtAndroidApk.cmake)
    add_qt_android_apk(Drehblubbe_apk Drehblubbe
	    VERSION_CODE 1
	    PACKAGE_NAME "org.tuxcode.${source_target}")
endif()
