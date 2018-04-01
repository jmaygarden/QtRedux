#pragma once

#include <QVariant>
#include <QWidget>

class QStandardItemModel;

class TodoListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TodoListWidget(QWidget *parent = nullptr);

signals:
    void action(QVariantMap);

public slots:
    void update(QVariant state);

private:
    QStandardItemModel *model;
};
