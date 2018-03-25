#pragma once

#include <QtRedux>
#include <QWidget>

class QStandardItemModel;

class TodoListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TodoListWidget(QWidget *parent = nullptr);

signals:
    void action(QtRedux::Action);

public slots:
    void update(QtRedux::State state);

private:
    QStandardItemModel *model;
};
