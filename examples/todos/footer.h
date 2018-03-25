#pragma once

#include <QtRedux>
#include <QWidget>

class QButtonGroup;

class Footer : public QWidget
{
    Q_OBJECT
public:
    explicit Footer(QWidget *parent = nullptr);

signals:
    void action(QtRedux::Action);

public slots:
    void update(QtRedux::State state);

private:
    QButtonGroup *group;
};
