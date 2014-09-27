#ifndef CALCUI_H
#define CALCUI_H
#include <iostream>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QInputDialog>
#include <QLineEdit>
#include "infixtopostfix.h"

using namespace std;

class calcUI : public QWidget
{
    Q_OBJECT
public:
    explicit calcUI();
    void paintEvent();
    QVBoxLayout *Main_Calculator; // Including the Input Dialogs, the two QGridLayouts for numbers and functions

    // Line Edit Layouts to be put in Input Dialogs
    QVBoxLayout *Input_Dialogs; // Three Line Edits with Three Labels
    QHBoxLayout *Infix_Layout;
    QHBoxLayout *Postfix_Layout;
    QHBoxLayout *Answer_Layout;
    QLineEdit   *Infix_Input;
    QLineEdit   *Postfix_Output;
    QLineEdit   *Answer_Output;
    QLabel      *InfixLabel;
    QLabel      *PostfixLabel;
    QLabel      *AnswerLabel;
    QSpacerItem *HSpacer1,*HSpacer2,*HSpacer3, *VSpacer1, *VSpacer2, *VSpacer3;


    // Button Layouts
    QHBoxLayout *Button_Layout;  // Two grids
    QGridLayout *Number_Buttons;
    QGridLayout *Function_Buttons;

    // Buttons Left (Numbers)
    QPushButton *Button_1,*Button_2,*Button_3, *Button_4, *Button_5, *Button_6, *Button_7, *Button_8, *Button_9, *Button_0;
    // Buttons Right (Functions)
    QPushButton *Button_Add, *Button_Sub, *Button_Mul, *Button_Div, *Button_Equ, *Button_Pow, *Button_LP, *Button_RP, *Button_SP;
    QPushButton *Button_CE, *Button_C, *Button_D;

signals:

public slots:
    void pressed1();
    void pressed2();
    void pressed3();
    void pressed4();
    void pressed5();
    void pressed6();
    void pressed7();
    void pressed8();
    void pressed9();
    void pressed0();
    void pressedMul();
    void pressedDiv();
    void pressedAdd();
    void pressedSub();
    void pressedPow();
    void pressedEqu();
    void pressedLP();
    void pressedRP();
    void pressedSP();
    void pressedCE();
    void pressedC();
    void pressedD();
    void pressedchar(QString pressed);
    void pressedfchar(QString pressed); // just for usability...

private:
    QString infixstring, lastinfix, result;
    InfixtoPostfix myinfix;
};
#endif // CALCUI_H
