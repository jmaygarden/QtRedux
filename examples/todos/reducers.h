#pragma once

#include <QtRedux>

extern QtRedux::Reducer todos;

extern QtRedux::Reducer visibilityFilter;

extern QVariantMap getVisibleTodos(QtRedux::State state);
