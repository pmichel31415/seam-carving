CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_MODULE_PATH $ENV{OPENCV_DIR})

FIND_PACKAGE(OpenCV REQUIRED)

PROJECT(seam-carving)

ADD_EXECUTABLE(seam-carving test.cpp main.cpp seam_carv.cpp seam_carv_dynamic.cpp seam_carv_random.cpp gui.cpp seam_carv.h seam_carv_dynamic.h gui.h seam_carv_random.h)

TARGET_LINK_LIBRARIES(seam-carving ${OpenCV_LIBS})