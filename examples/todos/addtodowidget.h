#pragma once

#include <QWidget>

#include <QtRedux>

class AddTodoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddTodoWidget(QWidget *parent = nullptr);

signals:
    void action(QtRedux::Action);
};
