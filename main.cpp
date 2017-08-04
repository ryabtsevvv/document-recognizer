// coding: utf-8
//! \file main.cpp
//! \brief Файл, содержащий точку входа приложения DOCUMENT_RECOGNIZER
//! \author Рябцев В.В.

#include <QApplication>

#include <gui/main_window.hpp>
#include <model/document_recognizer_model.hpp>

int main(int argc, char * argv[]) {
	
  QApplication application(argc, argv);

  DocumentRecognizerModel drModel;
  DocumentRecognizerMainWindow mainWindow(drModel);
	mainWindow.show();
	
  return application.exec();
}
