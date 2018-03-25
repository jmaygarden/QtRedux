#pragma once

#include <QtRedux>
#include <QWidget>

class TodosWidget : public QWidget
{
    Q_OBJECT

public:
    TodosWidget(QWidget *parent = 0);

private:
    std::shared_ptr<QtRedux::Store> store;
};

