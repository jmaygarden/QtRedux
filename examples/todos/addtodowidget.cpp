#include "actions.h"
#include "addtodowidget.h"

#include <QtWidgets>

AddTodoWidget::AddTodoWidget(QWidget *parent)
    : QWidget(parent)
{
    auto lineEdit = new QLineEdit;
    auto button = new QPushButton("Add Todo");
    auto layout = new QHBoxLayout;
    layout->addWidget(lineEdit);
    layout->addWidget(button);
    setLayout(layout);

    auto lambda = [this, lineEdit]()
    {
        emit action(addTodo(lineEdit->text()));
        lineEdit->clear();
    };
    connect(lineEdit, &QLineEdit::returnPressed, this, lambda);
    connect(button, &QPushButton::clicked, this, lambda);
}
