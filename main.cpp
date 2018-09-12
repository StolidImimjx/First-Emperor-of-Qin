#include "regeditmanagetool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegeditManageTool RMT;
    RMT.show();

    return a.exec();
}
