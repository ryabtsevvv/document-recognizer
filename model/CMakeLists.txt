# coding: utf-8
# Сборка библиотеки, содержащей бизнес-логику приложения.

SET( libmodel_HDRS 
  document_recognizer_model.hpp
)

SET( libmodel_SRCS
  document_recognizer_model.cpp
)

ADD_LIBRARY( libmodel SHARED ${libmodel_SRCS} ${libmodel_HDRS} )
TARGET_LINK_LIBRARIES( libmodel
  Qt5::Core
  ${OpenCV_LIBS}
  libpassport
  libimage_processing
)
