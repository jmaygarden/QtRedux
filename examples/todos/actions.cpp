#include "actions.h"

using namespace QtRedux;

Action addTodo(QString const & text)
{
    QtRedux::Action action;
    action.insert("type", AddTodo);
    action.insert("id", QUuid::createUuid().toString());
    action.insert("text", text);
    return action;
}

Action setVisibilityFilter(VisibilityFilter filter)
{
    QtRedux::Action action;
    action.insert("type", SetVisibilityFilter);
    action.insert("filter", filter);
    return action;
}

Action toggleTodo(QString const & id)
{
    QtRedux::Action action;
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
