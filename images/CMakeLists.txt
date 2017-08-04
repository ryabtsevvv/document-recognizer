# coding: utf-8
# Сборка библиотеки обработки изображений.

SET(libimage_processing_HDRS
  #cv_image.hpp
  image_processor.hpp
  recognizable_object.hpp
)

SET(libimage_processing_SRCS
  #cv_image.cpp
  image_processor.cpp
  recognizable_object.cpp
)

ADD_LIBRARY(libimage_processing SHARED
	${libimage_processing_HDRS}
	${libimage_processing_SRCS}
)

TARGET_LINK_LIBRARIES( libimage_processing
    ${OpenCV_LIBS}
    Qt5::Gui
  )
