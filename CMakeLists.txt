# Основной файл системы сборки приложения для распознавания документов.

PROJECT( DOCUMENT_RECOGNIZER CXX )

CMAKE_MINIMUM_REQUIRED( VERSION 3.0.2 FATAL_ERROR )

# Подключение модулей библиотеки Qt5.
FIND_PACKAGE( Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED
  ) 		# \TODO Перенести в папку gui
SET( CMAKE_AUTOMOC ON )
SET( CMAKE_AUTOUIC ON )

# Подключение библиотеки OpenCV.
FIND_PACKAGE( OpenCV REQUIRED )		# \TODO Перенести в папку image

# Определение директорий, содержащих заголовочные файлы.
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${Qt5_DIR}/include )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

# Добавление подкаталогов проекта.
ADD_SUBDIRECTORY( documents )       # Модуль, содержащий классы, описывающие документы и их элементы.
ADD_SUBDIRECTORY( images )          # Модуль обработки изображений.
ADD_SUBDIRECTORY( gui )             # Модуль графического интерфейса пользователя.
ADD_SUBDIRECTORY( model )           # Модуль бизнес-логики.


# Определение правил сборки основного приложения.
ADD_EXECUTABLE( document_recognizer
	main.cpp
)

TARGET_LINK_LIBRARIES( document_recognizer
  libgui
  libmodel
)


