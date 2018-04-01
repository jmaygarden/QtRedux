#include "actions.h"
#include "reducers.h"

#include <algorithm>

using namespace QtRedux;

Reducer<QVariant, QVariantMap> todos = [](QVariant state, QVariantMap action)
{
    switch(action.value("type").toInt())
    {
    case AddTodo:
    {
        auto id = action.value("id");

        if (id.isValid())
        {
            auto nextState = state.toMap();
            QVariantMap todo;
            todo.insert("text", action.value("text"));
            todo.insert("completed", false);
            nextState.insert(id.toString(), todo);
            return QVariant(nextState);
        }
        else
        {
            return state;
        }
    }

    case ToggleTodo:
    {
        auto id = action.value("id");

        if (id.isValid())
        {
            auto nextState = state.toMap();
            auto todo = nextState.value(id.toString()).toMap();
            todo.insert("completed", !todo.value("completed").toBool());
            nextState.insert(id.toString(), todo);
            return QVariant(nextState);
        }
        else
        {
            return state;
        }
    }

    default:
        return state.isValid() ? state : QVariantMap();
    }
};

Reducer<QVariant, QVariantMap> visibilityFilter = [](QVariant state, QVariantMap action)
{
    switch(action.value("type").toInt())
    {
    case SetVisibilityFilter:
        return QVariant(action.value("filter", ShowAll));

    default:
        return state.isValid() ? state : ShowAll;
    }
};

QVariantMap getVisibleTodos(QVariantMap state)
{
    auto visibilityFilter = state.value("visibilityFilter").toInt();
    auto todos = state.value("todos").toMap();

    switch(visibilityFilter)
    {
    case ShowAll:
        return QVariantMap(todos);

    case ShowCompleted:
    {
        QVariantMap filtered;
        for(auto it = todos.begin(); it != todos.end(); ++it)
        {
            if (it.value().toMap().value("completed").toBool())
            {
                filtered.insert(it.key(), it.value());
            }
        }
        return filtered;
    }

    case ShowActive:
    {
        QVariantMap filtered;
        for(auto it = todos.begin(); it != todos.end(); ++it)
        {
            if (!it.value().toMap().value("completed").toBool())
            {
                filtered.insert(it.key(), it.value());
            }
        }
        return filtered;
    }

    default:
        return QVariantMap();
    }
}
