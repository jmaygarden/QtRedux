#pragma once

#include <QtRedux>

#include <QtCore/QUuid>

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

extern QtRedux::Action addTodo(QString const & text);

extern QtRedux::Action setVisibilityFilter(VisibilityFilter filter);

extern QtRedux::Action toggleTodo(QString const & id);

extern QMap<int, QString> getVisibilityFilters();
