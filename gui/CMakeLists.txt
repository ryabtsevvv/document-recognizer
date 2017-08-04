# coding: utf-8
# Сборка библиотеки графического интерфейса пользователя.

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(libgui_HDRS
  control_widget.hpp
  image_widget.hpp
  main_window.hpp
)

SET(libgui_SRCS
  control_widget.cpp
  image_widget.cpp
	main_window.cpp
)

SET(libgui_UIS
  main_window.ui
)


ADD_LIBRARY(libgui SHARED
	${libgui_HDRS}
	${libgui_SRCS}
)

TARGET_LINK_LIBRARIES(libgui
	Qt5::Widgets
  ${OpenCV_LIBS}
  libimage_processing
  libpassport
  libmodel
)
