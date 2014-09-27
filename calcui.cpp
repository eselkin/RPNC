#include "calcui.h"

calcUI::calcUI()
{

    Main_Calculator = new QVBoxLayout;
    Input_Dialogs   = new QVBoxLayout;
    Infix_Layout    = new QHBoxLayout;
    Postfix_Layout  = new QHBoxLayout;
    Answer_Layout   = new QHBoxLayout;
    Button_Layout   = new QHBoxLayout;
    Number_Buttons  = new QGridLayout;
    Function_Buttons= new QGridLayout;
    Infix_Input     = new QLineEdit;
    Postfix_Output  = new QLineEdit;
    Answer_Output   = new QLineEdit;
    //Answer_Output->setFixedWidth(this->width());
    InfixLabel      = new QLabel("Infix:");
    PostfixLabel    = new QLabel("RPN:");
    AnswerLabel     = new QLabel("Answer:");

    Answer_Layout->addWidget(AnswerLabel,0,Qt::AlignRight);
    Answer_Layout->addWidget(Answer_Output);
    //Answer_Layout->setContentsMargins(0,0,this->width()/2.0,0);
    Infix_Layout->addWidget(InfixLabel);
    Infix_Layout->addWidget(Infix_Input);
    Postfix_Layout->addWidget(PostfixLabel);
    Postfix_Layout->addWidget(Postfix_Output);
    Input_Dialogs->addLayout(Infix_Layout);
    Input_Dialogs->addLayout(Postfix_Layout);
    Input_Dialogs->addLayout(Answer_Layout);
    Input_Dialogs->setAlignment(Qt::AlignTop);
    Input_Dialogs->setAlignment(Qt::AlignRight);
    Main_Calculator->addLayout(Input_Dialogs);

    HSpacer1 = new QSpacerItem(this->width()/10.0,this->height());
    HSpacer2 = new QSpacerItem(this->width()/20.0,1);
    HSpacer3 = new QSpacerItem(this->width()/20.0,1);

    // Buttons Left (Numbers)
    Button_1 = new QPushButton("1");
    Button_2 = new QPushButton("2");
    Button_3 = new QPushButton("3");
    Button_4 = new QPushButton("4");
    Button_5 = new QPushButton("5");
    Button_6 = new QPushButton("6");
    Button_7 = new QPushButton("7");
    Button_8 = new QPushButton("8");
    Button_9 = new QPushButton("9");
    Button_0 = new QPushButton("0");
    Number_Buttons->addWidget(Button_1,0,0,1,1);
    Number_Buttons->addWidget(Button_2,0,1,1,1);
    Number_Buttons->addWidget(Button_3,0,2,1,1);
    Number_Buttons->addWidget(Button_4,1,0,1,1);
    Number_Buttons->addWidget(Button_5,1,1,1,1);
    Number_Buttons->addWidget(Button_6,1,2,1,1);
    Number_Buttons->addWidget(Button_7,2,0,1,1);
    Number_Buttons->addWidget(Button_8,2,1,1,1);
    Number_Buttons->addWidget(Button_9,2,2,1,1);
    Number_Buttons->addWidget(Button_0,3,1,1,1);
    Number_Buttons->setAlignment(Qt::AlignTop);
    Button_Layout->addItem(HSpacer2);
    Button_Layout->addLayout(Number_Buttons);
    Button_Layout->addItem(HSpacer1);

    // Buttons Right (Functions)
    Button_Add = new QPushButton("+");
    Button_Sub = new QPushButton("-");
    Button_Mul = new QPushButton("*");
    Button_Div = new QPushButton("/");
    Button_Equ = new QPushButton("=");
    Button_Pow = new QPushButton("^");
    Button_LP  = new QPushButton("(");
    Button_RP  = new QPushButton(")");
    Button_SP  = new QPushButton("SPACE");
    Button_CE  = new QPushButton("CE");
    Button_C   = new QPushButton("C");
    Function_Buttons->addWidget(Button_Div,0,0,1,1);
    Function_Buttons->addWidget(Button_Mul,0,1,1,1);
    Function_Buttons->addWidget(Button_Add,0,2,1,1);
    Function_Buttons->addWidget(Button_Sub,1,0,1,1);
    Function_Buttons->addWidget(Button_Pow,1,1,1,1);
    Function_Buttons->addWidget(Button_Equ,1,2,1,1);
    Function_Buttons->addWidget(Button_LP,2,0,1,1);
    Function_Buttons->addWidget(Button_RP,2,1,1,1);
    Function_Buttons->addWidget(Button_SP,2,2,1,1);
    Function_Buttons->addWidget(Button_CE,3,0,1,1);
    Function_Buttons->addWidget(Button_C,3,1,1,1);
    Function_Buttons->setAlignment(Qt::AlignTop);
    Button_Layout->addLayout(Function_Buttons);
    Main_Calculator->addLayout(Button_Layout);
    Button_Layout->addItem(HSpacer3);
    Button_Layout->setAlignment(Qt::AlignTop);
    setLayout(Main_Calculator);
}
