#ifndef LEDEDITWIDGET_H
#define LEDEDITWIDGET_H
#include <QAbstractScrollArea>
#include <QWidget>

class QSpinBox;
class LedEditWidget : public QAbstractScrollArea
{
    Q_OBJECT

public:
    explicit LedEditWidget(QWidget *parent = nullptr);
    QPair<int, int> visibleColumns() const;
    int horizontalOffset() const;
    int verticalOffset() const;
    QSize cellSize() const;
    QRect gridRect() const;
    int column() const;
    void setColumn(int value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void valueChanged(int value);
    void updateVisibleColumns();
    void updateVisibleRows();
    void setHorizontalOffset(int value);
    void setVerticalOffset(int value);
    void setVisibleColumn(int minColumn, int maxColumn);
    void setVisibleRow(int minRow, int maxRow);

private:
    QSpinBox *spinBox;
    QList<int> _rowHeaderHeight;
    QList<int> _columnHeaderWidth;
    QSize _cellSize;
    QPixmap _pixmap;
    QPair<int, int> _visibleColumns;
    QPair<int, int> _visibleRows;
    int _horizontalOffset;
    int _verticalOffset;
    QRect _gridRect;
    int _column;
};

#endif // LEDEDITWIDGET_H
