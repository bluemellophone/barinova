# This is a CMake build file, for more information consult:
# http://en.wikipedia.org/wiki/CMake
# and
# http://www.cmake.org/Wiki/CMake
# http://www.cmake.org/cmake/help/syntax.html
# http://www.cmake.org/Wiki/CMake_Useful_Variables
# http://www.cmake.org/cmake/help/cmake-2-8-docs.html

# to compile the local code you can use: cmake ./ && make -j2

# ----------------------------------------------------------------------
# Base CMake setup

cmake_minimum_required (VERSION 2.6)

# ----------------------------------------------------------------------
# Setup the project

include(FindPkgConfig)
project (ObjectDetection)

# ----------------------------------------------------------------------
# Setup require libraries
pkg_check_modules(opencv REQUIRED opencv>=2.1)

# ----------------------------------------------------------------------
# Setup link and include directories

link_directories(
	${opencv_LIBRARY_DIRS}
	"/opt/local/lib/"
)
include_directories(
	"../Utils/" 
	${opencv_INCLUDE_DIRS} 
	"/opt/local/include/"
)

# ----------------------------------------------------------------------
# Collect source files

file(GLOB SrcCpp 
	"../*.cpp"
	"../DenseGreedyDetection/*.cpp"
	"../Forests/*.cpp"
	"../ImageWrapper/*.cpp"
	"../Utils/*.cpp"
)

# ----------------------------------------------------------------------
# Create the executable
if(WIN32)
	set(OPT_CXX_FLAGS "-O3 -fopenmp -funroll-lolsops -march=native -mtune=native --fast-math -mfpmath=sse -msse3 ")
else()
	set(OPT_CXX_FLAGS "-O3 -funroll-loops -march=native -mtune=native -ffast-math -msse3 ")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DNDEBUG ${OPT_CXX_FLAGS}")

add_executable(object_detection ${SrcCpp})

target_link_libraries(object_detection
   boost_filesystem-mt
   boost_system-mt
   boost_thread-mt
   gomp # sudo ln -s /opt/local/lib/libgcc/libgomp.1.dylib /opt/local/lib/libgomp.dylib
   opencv_core # Added because pkg-config cannot find symbols
   opencv_highgui # Added because pkg-config cannot find symbols
   opencv_video # Added because pkg-config cannot find symbols
   opencv_imgproc # Added because pkg-config cannot find symbols
   ${opencv_LIBRARIES}
)   
 
# ----------------------------------------------------------------------
