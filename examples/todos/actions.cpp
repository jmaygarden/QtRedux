#include "actions.h"

#include <QUuid>

QVariantMap addTodo(QString const & text)
{
    QVariantMap action;
    action.insert("type", AddTodo);
    action.insert("id", QUuid::createUuid().toString());
    action.insert("text", text);
    return action;
}

QVariantMap setVisibilityFilter(VisibilityFilter filter)
{
    QVariantMap action;
    action.insert("type", SetVisibilityFilter);
    action.insert("filter", filter);
    return action;
}

QVariantMap toggleTodo(QString const & id)
{
    QVariantMap action;
    action.insert("type", ToggleTodo);
    action.insert("id", id);
    return action;
}

QMap<int, QString> getVisibilityFilters()
{
    QMap<int, QString> map;
    map.insert(ShowAll, "Show All");
    map.insert(ShowCompleted, "Show Completed");
    map.insert(ShowActive, "Show Active");
    return map;
}
