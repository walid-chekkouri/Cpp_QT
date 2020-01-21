#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }// Use the standard UI namespace which is tied to the .ui file
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    // Declares our class as a QObject which is the base class
        // for all Qt objects
        // QObjects handle events
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

    // These slots are executed when a signal is
        // submitted (Ex. Number button is clicked)
private slots:
    void numPressed();
    void mathButtonPressed();
    void equalButton();
    void changeSignButton();
    void clear();
    void buttonM();

};
#endif // CALCULATOR_H
