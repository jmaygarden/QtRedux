#include "todoswidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TodosWidget w;
    w.show();

    return a.exec();
}
