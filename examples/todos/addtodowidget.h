#pragma once

#include <QVariant>
#include <QWidget>

class AddTodoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddTodoWidget(QWidget *parent = nullptr);

signals:
    void action(QVariantMap);
};
