#include "calculator.h"
#include "ui_calculator.h"

double calcValue{0.0};// Holds current value of calculation
double savedValueM{0.0};// Holds saved M value of calculation
// Will define if this was the last math button clicked
bool divTrigger{false};
bool multTrigger{false};
bool addTrigger{false};
bool subTrigger{false};

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->displayer->setText(QString::number(calcValue));//set display text, cast from double to string
    QPushButton* numButtons[10];// Will hold references to all the number buttons
    for(int i=0; i<10;++i)
    {
        QString buttonName = "button_"+QString::number(i);
        numButtons[i]= Calculator::findChild<QPushButton *>(buttonName);//add the number Buttons to our array.We searched for a widget by providing its name.
        connect(numButtons[i],SIGNAL(released()),this,SLOT(numPressed()));// When the button is released call num_pressed()
    }
    // Connect signals and slots for math buttons
    connect(ui->button_Add,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->button_Subtract,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->button_Mult,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->button_Divide,SIGNAL(released()),this,SLOT(mathButtonPressed()));

    connect(ui->button_Equal,SIGNAL(released()),this,SLOT(equalButton()));
    connect(ui->button_SignSwitch,SIGNAL(released()),this,SLOT(changeSignButton()));
    connect(ui->button_AC,SIGNAL(released()),this,SLOT(clear()));

    connect(ui->button_MAdd,SIGNAL(released()),this,SLOT(buttonM()));
    connect(ui->button_MClear,SIGNAL(released()),this,SLOT(buttonM()));
    connect(ui->button_MAccess,SIGNAL(released()),this,SLOT(buttonM()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numPressed()
{
    QPushButton *button = (QPushButton *)sender();// Sender returns a pointer to the button pressed
    QString buttonValue = button->text();
    QString displayValue = ui->displayer->text();
    if((displayValue.toDouble()==0) || (displayValue.toDouble()==0.0))
    {
        ui->displayer->setText(buttonValue);
    }else
    {
        QString newValue = displayValue + buttonValue;
        double doubleNewValue= newValue.toDouble();
         ui->displayer->setText(QString::number(doubleNewValue,'g',16));
    }
}

void Calculator::mathButtonPressed()
 {
     divTrigger=false;
     multTrigger=false;
     addTrigger=false;
     subTrigger=false;

      QString displayValue = ui->displayer->text();
      calcValue=displayValue.toDouble();
      QPushButton *button = (QPushButton *)sender();
      QString buttonValue = button->text();
    if(QString::compare(buttonValue,"/",Qt::CaseSensitive)==0)//we have a match
        {
         divTrigger=true;
        }else if(QString::compare(buttonValue,"*",Qt::CaseSensitive)==0)
        {
         multTrigger=true;
        }else if(QString::compare(buttonValue,"+",Qt::CaseSensitive)==0)
        {
          addTrigger=true;
        }else
         {
          subTrigger=true;
         }
    ui->displayer->setText("");
 }

void Calculator::equalButton()
  {
      double solution{0};
      QString displayValue = ui->displayer->text();
      double doubleDisplayValue = displayValue.toDouble();
      if(divTrigger || multTrigger || addTrigger || subTrigger)
      {
          if(addTrigger)
          {
              solution=calcValue + doubleDisplayValue;
          }else if(subTrigger)
          {
              solution=calcValue - doubleDisplayValue;
          }else if(multTrigger)
          {
              solution=calcValue * doubleDisplayValue;
          }else
          {
              solution=calcValue / doubleDisplayValue;
          }

      }
      ui->displayer->setText(QString::number(solution));
  }

void Calculator::changeSignButton()
{
      QString displayValue = ui->displayer->text();
      QRegExp reg("[-]?[0-9.]*");
      if(reg.exactMatch(displayValue))
      {
        double doubleDisplayValue = displayValue.toDouble();
        double doubleDisplayValueSign = -1 * doubleDisplayValue;
        ui->displayer->setText(QString::number(doubleDisplayValueSign));
      }
}

void Calculator::clear()
{
    ui->displayer->setText("");
}

void Calculator::buttonM()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
  if(QString::compare(buttonValue,"M+",Qt::CaseSensitive)==0)
  {
      savedValueM=ui->displayer->text().toDouble();
  }else if(QString::compare(buttonValue,"M-",Qt::CaseSensitive)==0)
  {
      savedValueM=0.0;
  }else
  {
      ui->displayer->setText(ui->displayer->text()+QString::number(savedValueM));
  }

}
