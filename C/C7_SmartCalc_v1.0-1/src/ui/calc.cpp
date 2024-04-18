#include "calc.h"

#include "./ui_calc.h"
#include "QtWidgets/qmessagebox.h"
#include "graph.h"

Calc::Calc(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calc) {
  ui->setupUi(this);

  connect(ui->acosButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->asinButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->sinButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->cosButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->plusButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->minusButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->multButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->divButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->dotButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->openBrackButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->closeBrackButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->tanButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->atanButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->sqrtButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->oneButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->twoButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->threeButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->fourButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->fiveButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->sixButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->sevenButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->eightButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->nineButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->zeroButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearExpr()));
  connect(ui->logButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->lnButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->powButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeChar()));
  connect(ui->xButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->modButton, SIGNAL(clicked()), this, SLOT(inputExpr()));
  connect(ui->resultButton, SIGNAL(clicked()), this, SLOT(result()));
  connect(ui->graphButton, SIGNAL(clicked()), this, SLOT(graph()));
}

Calc::~Calc() { delete ui; }

void Calc::clearExpr() { ui->exprLine->setText("0"); }

void Calc::inputExpr() {
  QPushButton *button = (QPushButton *)sender();
  QString expr = ui->exprLine->text();

  if (expr == "0") {
    if (button->text() == ".")
      expr += ".";
    else
      expr = button->text().toLower();
  } else
    expr += button->text().toLower();

  if (button->text().length() > 1) expr += "(";

  ui->exprLine->setText(expr);
}

void Calc::result() {
  double res = 0.0;
  if (ui->exprLine->text().contains("x")) {
    if (calculate(ui->exprLine->text().toLocal8Bit().data(),
                  ui->xValue->text().toDouble(), &res) == SUCCESS) {
      ui->exprLine->setText(QString::number(res, 'g', 8));
    } else {
      ui->exprLine->setText("Error");
    }
  } else {
    if (calculate(ui->exprLine->text().toLocal8Bit().data(), 0, &res) ==
        SUCCESS) {
      ui->exprLine->setText(QString::number(res, 'g', 8));
    } else {
      ui->exprLine->setText("Error");
    }
  }
}

void Calc::removeChar() {
  QString expr = ui->exprLine->text();
  expr.remove(expr.length() - 1, expr.length());
  ui->exprLine->setText(expr);
}

void Calc::graph() {
  Graph *graph = new Graph();
  graph->setWindowTitle("Graph");
  graph->scailing();
  if (graph->plot(ui->exprLine->text().toLocal8Bit().data()) == SUCCESS) {
    graph->graph_proccessing();
    graph->show();
  } else {
    ui->exprLine->setText("Error");
    delete graph;
  }
}
