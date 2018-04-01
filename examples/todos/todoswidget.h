#pragma once

#include <QtRedux>
#include <QWidget>

class TodosWidget : public QWidget
{
    Q_OBJECT

public:
    TodosWidget(QWidget *parent = 0);

private:
    std::unique_ptr<QtRedux::QVariantStore> store;
};
