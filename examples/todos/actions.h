#pragma once

#include <QVariantMap>

enum Actions
{
    NullAction,
    AddTodo,
    SetVisibilityFilter,
    ToggleTodo
};

enum VisibilityFilter
{
    ShowAll,
    ShowCompleted,
    ShowActive
};

extern QVariantMap addTodo(QString const & text);

extern QVariantMap setVisibilityFilter(VisibilityFilter filter);

extern QVariantMap toggleTodo(QString const & id);

extern QMap<int, QString> getVisibilityFilters();
