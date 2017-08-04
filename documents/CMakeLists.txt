# coding: utf-8

SET( libpassport_HDRS
    field_image.hpp
    page_image.hpp
    passport.hpp
    passport_image.hpp
  )

SET( libpassport_SRCS
    field_image.cpp
    page_image.cpp
    passport.cpp
    passport_image.cpp
  )

ADD_LIBRARY( libpassport SHARED ${libpassport_HDRS} ${libpassport_SRCS} )
TARGET_LINK_LIBRARIES( libpassport
    libimage_processing
  )
