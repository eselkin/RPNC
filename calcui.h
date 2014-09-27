#ifndef CALCUI_H
#define CALCUI_H
#include <iostream>

#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QWidget>
#include <QTextEdit>
#include <QGLWidget>
#include <QSpacerItem>
#include <QLabel>
#include <QWidget>
#include <QInputDialog>
#include <QLineEdit>
#include "calcwidget.h"

class calcUI : public QWidget
{
    Q_OBJECT
public:
    explicit calcUI();
    //calcwidget *cwidget; // No GL Painting, unless we want to make it a game!

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
    QSpacerItem *HSpacer1,*HSpacer2,*HSpacer3;

    // Button Layouts
    QHBoxLayout *Button_Layout;  // Two grids
    QGridLayout *Number_Buttons;
    QGridLayout *Function_Buttons;

    // Buttons Left (Numbers)
    QPushButton *Button_1,*Button_2,*Button_3, *Button_4, *Button_5, *Button_6, *Button_7, *Button_8, *Button_9, *Button_0;
    // Buttons Right (Functions)
    QPushButton *Button_Add, *Button_Sub, *Button_Mul, *Button_Div, *Button_Equ, *Button_Pow, *Button_LP, *Button_RP, *Button_SP;
    QPushButton *Button_CE, *Button_C;

signals:

public slots:

};

#endif // CALCUI_H
