#include "lededitwidget.h"
#include "spinboxstyle.h"
#include <QLineEdit>
#include <QPainter>
#include <QScrollBar>
#include <QSpinBox>
#include <QStyleOptionSpinBox>
#include <qpainter.h>
#include <qpixmap.h>

LedEditWidget::LedEditWidget(QWidget *parent) : QAbstractScrollArea{parent} {
  _rowHeaderHeight << 30;
  _columnHeaderWidth << 40 << 30 << 30;
  _cellSize = QSize(15, 15);
  _column = 4;
  _verticalOffset = 0;
  _horizontalOffset = 0;
  //   spinBox = new QSpinBox(viewport());
  //   spinBox->setAccelerated(true);
  //   spinBox->setGeometry(
  //       0, 0,
  //       std::accumulate(_columnHeaderWidth.begin(), _columnHeaderWidth.end(),
  //                       0),
  //       std::accumulate(_rowHeaderHeight.begin(), _rowHeaderHeight.end(), 0));
  //   spinBox->setFocusPolicy(Qt::NoFocus);
  //   // spinBox->setStyle(new SpinBoxStyle());

  //   spinBox->setStyleSheet("color: white; background-color: black; border: 0px; "
  //                          "selection-background-color: transparent;");

  this->resize(1080, 768);
  verticalScrollBar()->setRange(0, 10000 * _cellSize.height());
  horizontalScrollBar()->setRange(0, 100);
  connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &LedEditWidget::setVerticalOffset);
  connect(horizontalScrollBar(),
          &QScrollBar::valueChanged,
          this,
          &LedEditWidget::setHorizontalOffset);
  //   _pixmap = QPixmap(500, 200);
  //   connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &LedEditWidget::setVerticalOffset);
  //   QPainter painter(&_pixmap);
  //   painter.setPen(Qt::black);
  //   painter.setBrush(Qt::red);
  //   // vẽ hình chữ nhật
  // //   painter.drawRect(10, 10, 80, 60);

  //   // vẽ chữ
  //   painter.drawText(20, 90, "Hello QPixmap");
}

QPair<int, int> LedEditWidget::visibleColumns() const
{
    return _visibleColumns;
}

int LedEditWidget::horizontalOffset() const
{
    return _horizontalOffset;
}

int LedEditWidget::verticalOffset() const
{
    return _verticalOffset;
}

QSize LedEditWidget::cellSize() const
{
    return _cellSize;
}

QRect LedEditWidget::gridRect() const
{
    return _gridRect;
}

int LedEditWidget::column() const
{
    return _column;
}

void LedEditWidget::setColumn(int value)
{
    _column = value;
}

void LedEditWidget::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  QPainter p(viewport());
  QRect r = viewport()->rect();
  r = r.marginsRemoved(QMargins(0, 0, 10, 10));
  p.setBrush(Qt::red);
  p.setPen(Qt::NoPen);
  p.drawRect(r);
  // p.drawPixmap(0, 0, _pixmap.width(), _pixmap.height(), _pixmap);
}

void LedEditWidget::resizeEvent(QResizeEvent *event)
{
    _gridRect = viewport()->rect().marginsRemoved(QMargins(0, 0, 10, 10));
    qDebug() << "_gridRect" << _gridRect;
    updateVisibleColumns();
    updateVisibleRows();
}

void LedEditWidget::valueChanged(int value) {
    spinBox->setValue(value);
}

void LedEditWidget::updateVisibleColumns()
{
    int oldMinColumn = visibleColumns().first;
    int newMinColumn = horizontalOffset() >= 0 ? horizontalOffset() / cellSize().width()
                                              : (horizontalOffset() + 1) / cellSize().width() - 1;
    int newMaxColumn = horizontalOffset() + gridRect().width() > 0
                           ? (horizontalOffset() + gridRect().width() - 1) / cellSize().width()
                           : (horizontalOffset() + gridRect().width()) / cellSize().width() - 1;

    newMinColumn = std::max(0, newMinColumn);
    newMaxColumn = std::min(std::max(_column - 1, 0), std::max(newMinColumn, newMaxColumn));
    setVisibleColumn(newMinColumn, newMaxColumn);
}

void LedEditWidget::updateVisibleRows()
{
    int oldMinRow = _visibleRows.first;
    int newMinRow = _verticalOffset >= 0 ? _verticalOffset / _cellSize.height()
                                         : (_verticalOffset + 1) / _cellSize.height() - 1;
    int oldMaxRow = _visibleRows.second;
    int newMaxRow = _verticalOffset + _gridRect.height() > 0
                        ? (_verticalOffset + _gridRect.height() - 1) / _cellSize.height()
                        : (_verticalOffset + _gridRect.height() / _cellSize.height() - 1);
    newMinRow = std::max(0, newMinRow);
    newMaxRow = std::min(10000, std::max(newMinRow, newMaxRow));
    setVisibleRow(newMinRow, newMaxRow);
}

void LedEditWidget::setHorizontalOffset(int value)
{
    _horizontalOffset = value;
    updateVisibleColumns();
}

void LedEditWidget::setVerticalOffset(int value)
{
    _verticalOffset = value;
    updateVisibleRows();
}

void LedEditWidget::setVisibleColumn(int minColumn, int maxColumn)
{
    _visibleColumns = qMakePair(minColumn, maxColumn);
    qDebug() << "_visibleColumns" << _visibleColumns;
}

void LedEditWidget::setVisibleRow(int minRow, int maxRow)
{
    _visibleRows = qMakePair(minRow, maxRow);
    qDebug() << "_visibleRows" << _visibleRows;
}
