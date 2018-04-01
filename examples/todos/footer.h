#pragma once

#include <QVariantMap>
#include <QWidget>

class QButtonGroup;

class Footer : public QWidget
{
    Q_OBJECT
public:
    explicit Footer(QWidget *parent = nullptr);

signals:
    void action(QVariantMap);

public slots:
    void update(QVariant state);

private:
    QButtonGroup *group;
};
