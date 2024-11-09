#include "mainwindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentResult(0), typingNewNumber(true) {

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    display = new QLineEdit(centralWidget);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    QGridLayout *layout = new QGridLayout(centralWidget);
    layout->addWidget(display, 0, 0, 1, 4);

    // Create number buttons
    for (int i = 0; i < 10; ++i) {
        QPushButton *button = new QPushButton(QString::number(i), centralWidget);
        connect(button, &QPushButton::clicked, [this, i] { onNumberClicked(i); });
        layout->addWidget(button, (i / 3) + 1, i % 3);
    }

    // Add operator buttons
    QStringList operators = {"+", "-", "*", "/"};
    for (int i = 0; i < operators.size(); ++i) {
        QPushButton *button = new QPushButton(operators[i], centralWidget);
        connect(button, &QPushButton::clicked, [this, operators, i] { onOperatorClicked(operators[i]); });
        layout->addWidget(button, i + 1, 3);
    }

    QPushButton *equalsButton = new QPushButton("=", centralWidget);
    connect(equalsButton, &QPushButton::clicked, this, &MainWindow::onCalculate);
    layout->addWidget(equalsButton, 5, 3);
}

void MainWindow::onNumberClicked(int number) {
    if (typingNewNumber) {
        display->clear();
        typingNewNumber = false;
    }
    display->setText(display->text() + QString::number(number));
}

void MainWindow::onOperatorClicked(QString op) {
    if (!typingNewNumber) {
        onCalculate();
    }
    pendingOperator = op;
    currentResult = display->text().toDouble();
    typingNewNumber = true;
}

void MainWindow::onCalculate() {
    if (pendingOperator.isEmpty() || typingNewNumber) {
        return;
    }
    double currentValue = display->text().toDouble();
    if (pendingOperator == "+") {
        currentResult += currentValue;
    } else if (pendingOperator == "-") {
        currentResult -= currentValue;
    } else if (pendingOperator == "*") {
        currentResult *= currentValue;
    } else if (pendingOperator == "/") {
        if (currentValue != 0) {
            currentResult /= currentValue;
        } else {
            QMessageBox::warning(this, "Error", "Division by zero is not allowed.");
            return;
        }
    }
    display->setText(QString::number(currentResult));
    pendingOperator.clear();
    typingNewNumber = true;
}
