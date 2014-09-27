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
    Infix_Input->setFont(QFont("ARIAL", 14));
    Postfix_Output  = new QLineEdit;
    Postfix_Output->setReadOnly(1);
    Answer_Output   = new QLineEdit;
    Answer_Output->setReadOnly(1);
    //Answer_Output->setFixedWidth(this->width());
    InfixLabel      = new QLabel("Infix:");
    PostfixLabel    = new QLabel("RPN:");
    AnswerLabel     = new QLabel("Answer:");
    VSpacer1 = new QSpacerItem(1.0,this->height()/20.0);
    VSpacer2 = new QSpacerItem(1.0,this->height()/20.0);
    VSpacer3 = new QSpacerItem(1.0,this->height()/20.0);
    Answer_Layout->addWidget(AnswerLabel,0,Qt::AlignRight);
    Answer_Layout->addWidget(Answer_Output);
    Infix_Layout->addWidget(InfixLabel);
    Infix_Layout->addWidget(Infix_Input);
    Postfix_Layout->addWidget(PostfixLabel);
    Postfix_Layout->addWidget(Postfix_Output);
    Input_Dialogs->addItem(VSpacer1);
    Input_Dialogs->addLayout(Infix_Layout);
    Input_Dialogs->addLayout(Postfix_Layout);
    Input_Dialogs->addLayout(Answer_Layout);
    Input_Dialogs->addItem(VSpacer2);
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
    connect(Button_0,SIGNAL(clicked()),this,SLOT(pressed0()));
    connect(Button_1,SIGNAL(clicked()),this,SLOT(pressed1()));
    connect(Button_2,SIGNAL(clicked()),this,SLOT(pressed2()));
    connect(Button_3,SIGNAL(clicked()),this,SLOT(pressed3()));
    connect(Button_4,SIGNAL(clicked()),this,SLOT(pressed4()));
    connect(Button_5,SIGNAL(clicked()),this,SLOT(pressed5()));
    connect(Button_6,SIGNAL(clicked()),this,SLOT(pressed6()));
    connect(Button_7,SIGNAL(clicked()),this,SLOT(pressed7()));
    connect(Button_8,SIGNAL(clicked()),this,SLOT(pressed8()));
    connect(Button_9,SIGNAL(clicked()),this,SLOT(pressed9()));
    connect(Button_Add,SIGNAL(clicked()),this,SLOT(pressedAdd()));
    connect(Button_Sub,SIGNAL(clicked()),this,SLOT(pressedSub()));
    connect(Button_Mul,SIGNAL(clicked()),this,SLOT(pressedMul()));
    connect(Button_Div,SIGNAL(clicked()),this,SLOT(pressedDiv()));
    connect(Button_Pow,SIGNAL(clicked()),this,SLOT(pressedPow()));
    connect(Button_Equ,SIGNAL(clicked()),this,SLOT(pressedEqu()));
    connect(Button_LP,SIGNAL(clicked()),this,SLOT(pressedLP()));
    connect(Button_RP,SIGNAL(clicked()),this,SLOT(pressedRP()));
    connect(Button_SP,SIGNAL(clicked()),this,SLOT(pressedSP()));
    connect(Button_C,SIGNAL(clicked()),this,SLOT(pressedC()));
    connect(Button_CE,SIGNAL(clicked()),this,SLOT(pressedCE()));

}

void calcUI::pressed1()
{
    pressedchar("1");
}

void calcUI::pressed2()
{
    pressedchar("2");
}

void calcUI::pressed3()
{
    pressedchar("3");
}

void calcUI::pressed4()
{
    pressedchar("4");
}

void calcUI::pressed5()
{
    pressedchar("5");
}

void calcUI::pressed6()
{
    pressedchar("6");
}

void calcUI::pressed7()
{
    pressedchar("7");
}

void calcUI::pressed8()
{
    pressedchar("8");
}

void calcUI::pressed9()
{
    pressedchar("9");
}

void calcUI::pressed0()
{
    pressedchar("0");
}

void calcUI::pressedMul()
{
    pressedchar("*");
}

void calcUI::pressedDiv()
{
    pressedchar("/");
}

void calcUI::pressedAdd()
{
    pressedchar("+");
}

void calcUI::pressedSub()
{
    pressedchar("-");
}

void calcUI::pressedPow()
{
    pressedchar("^");
}

void calcUI::pressedEqu()
{
// Run completed infix
}

void calcUI::pressedLP()
{
    pressedchar("(");
}

void calcUI::pressedRP()
{
    pressedchar(")");
}

void calcUI::pressedSP()
{
    pressedchar(" ");
}

void calcUI::pressedCE()
{
    infixstring.clear();
    Infix_Input->setText(infixstring);
    update();
}

void calcUI::pressedC()
{
    infixstring.clear();
    result.clear();
    lastinfix.clear();
    Infix_Input->setText(infixstring);
    update();
}

void calcUI::pressedchar(QString pressed)
{
    infixstring.append(pressed);
    Infix_Input->setText(infixstring);
    update();
}

