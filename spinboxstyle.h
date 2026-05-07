#ifndef SPINBOXSTYLE_H
#define SPINBOXSTYLE_H
#include <QProxyStyle>
class SpinBoxStyle : public QProxyStyle
{
public:
    SpinBoxStyle();

    // QStyle interface
public:
    void drawComplexControl(ComplexControl cc,
                            const QStyleOptionComplex *opt,
                            QPainter *p,
                            const QWidget *widget) const override;
};

#endif // SPINBOXSTYLE_H
