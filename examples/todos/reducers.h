#pragma once

#include <QtRedux>

extern QtRedux::Reducer<QVariant, QVariantMap> todos;

extern QtRedux::Reducer<QVariant, QVariantMap> visibilityFilter;

extern QVariantMap getVisibleTodos(QVariantMap state);
