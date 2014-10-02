#include <QApplication>
#include "calcui.h"
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));
    QApplication ThisApp(argc, argv);
    calcUI GUI;
    GUI.show();
    GUI.setStyleSheet("background-color: #CCCCFF;");
    GUI.setGeometry(250,50,500,300);
    return ThisApp.exec(); // enters a loop // done running
}
