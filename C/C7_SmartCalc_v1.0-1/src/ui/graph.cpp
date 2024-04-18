#include "graph.h"

#include "qcustomplot.h"
#include "ui_graph.h"

Graph::Graph(QWidget* parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);

  connect(ui->plotButton, SIGNAL(clicked()), this, SLOT(replot()));
}

Graph::~Graph() { delete ui; }

rflag Graph::plot(char* expr) {
  rflag flag = SUCCESS;

  for (double x = xBegin; x <= xEnd; x += step) {
    double res = 0.0;
    flag = calculate(expr, x, &res);

    if (flag == SUCCESS) {
      this->points.first.push_back(x);
      this->points.second.push_back(res);
    }
  }

  return flag;
}

void Graph::rescale() {
  this->xBegin = ui->xFrom->text().toDouble();
  this->xEnd = ui->xTo->text().toDouble();
}

void Graph::scailing() {
  if (xEnd - xBegin <= 10)
    this->step = 0.00001;
  else if (xEnd - xBegin <= 100)
    this->step = 0.0001;
  else if (xEnd - xBegin <= 1000)
    this->step = 0.001;
  else if (xEnd - xBegin <= 10000)
    this->step = 0.01;
  else if (xEnd - xBegin <= 100000)
    this->step = 0.1;
  else if (xEnd - xBegin > 100000)
    this->step = 0.5;
}

void Graph::replot() {
  this->rescale();
  this->scailing();
  ui->graph->yAxis->setRange(this->xBegin, this->xEnd);
  ui->graph->xAxis->setRange(this->xBegin, this->xEnd);
  ui->graph->replot();
}

void Graph::graph_proccessing() {
  ui->graph->yAxis->setRange(this->xBegin, this->xEnd);
  ui->graph->xAxis->setRange(this->xBegin, this->xEnd);
  ui->graph->addGraph();
  ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->graph->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

  QVector<double> x_points =
      QVector<double>(this->points.first.begin(), this->points.first.end());
  QVector<double> y_points =
      QVector<double>(this->points.second.begin(), this->points.second.end());

  ui->graph->graph(0)->addData(x_points, y_points);
  ui->graph->replot();
  ui->graph->setInteraction(QCP::iRangeZoom, true);
  ui->graph->setInteraction(QCP::iRangeDrag, true);
}
