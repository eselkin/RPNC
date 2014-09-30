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
    GUI.setStyleSheet("background-color: lightblue;");
    GUI.setGeometry(250,50,600,400);
    return ThisApp.exec(); // enters a loop // done running
}
