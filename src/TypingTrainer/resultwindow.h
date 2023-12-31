#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include "mainwindow.h"
#include <QDialog>
namespace Ui {class resultwindow;}

class resultwindow : public QDialog
{
    Q_OBJECT
    Ui::resultwindow *ui;
public:
    explicit resultwindow(QWidget *parent = nullptr);
    void setCounterTypingSpeed(int typingSpeed);
    void setErrorCounter(int errorsCounter);
    void setAccyracyСounter(int accyracy);
    int get_maxNumberErrors(){
        return maxNumberErrors;
    }
    void offOrOnNextButton(bool visible);
    ~resultwindow();
private:
    int minSpeed = 60;
    int maxNumberErrors = 2;
    void connectSignalsAndSlots();
signals:
    void againSignal();
    void nextSignal();

};

#endif // RESULTWINDOW_H
