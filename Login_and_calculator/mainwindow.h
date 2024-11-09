#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onCalculate();
    void onNumberClicked(int number);
    void onOperatorClicked(QString op);

private:
    QLineEdit *display;
    double currentResult;
    QString pendingOperator;
    bool typingNewNumber; // Flag to check if we are typing a new number
};

#endif // MAINWINDOW_H
