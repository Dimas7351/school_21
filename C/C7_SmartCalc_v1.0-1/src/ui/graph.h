#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

extern "C" {
#include "../backend/headers/base.h"
#include "../backend/headers/calc.h"
#include "../backend/headers/parser.h"
#include "../backend/headers/stack.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void scailing();
  void rescale();
  rflag plot(char *expr);
  void graph_proccessing();

 private slots:
  void replot();

 private:
  Ui::Graph *ui;
  double xBegin = -1000000, xEnd = 1000000;
  double step;
  std::pair<std::vector<double>, std::vector<double>> points;
};

#endif  // GRAPH_H
