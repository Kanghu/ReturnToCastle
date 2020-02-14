#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(452, 482);
    w.setWindowTitle("Return to Castle");
    w.setWindowIcon(QIcon("castle.ico"));
    w.show();

    return a.exec();
}
