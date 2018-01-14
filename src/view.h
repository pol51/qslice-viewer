#pragma once

#include <QtWidgets/QMainWindow>

class Data;

class View : public QMainWindow
{
  Q_OBJECT

  public:
    View(const Data &data);
};
