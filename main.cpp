#include <QApplication>
#include "lededitwidget.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // MainWindow w;
    // w.show();
    LedEditWidget *w = new LedEditWidget();

    w->show();
    return a.exec();
}
