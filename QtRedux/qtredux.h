/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-present Judge Maygarden
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "qtredux_global.h"

#include <functional>
#include <memory>

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace QtRedux
{

typedef QVariantMap Action;

typedef QVariant State;

typedef std::function<State(State const &, Action const &)> Reducer;

typedef QMap<QString, Reducer> Reducers;

typedef std::function<Action(Action)> Dispatcher;

class QTREDUXSHARED_EXPORT Store : public QObject
{
    Q_OBJECT

public:
    Store(Reducer reducer, State preloadedState);

    State const & getState() const { return state; }

public slots:
    Action dispatch(Action action = Action());

    void replaceReducer(Reducer nextReducer);

signals:
    void changed(State);

private:
    Reducer reducer;
    State state;
};

typedef std::function<std::unique_ptr<Store>(Reducer, State)> StateCreator;

typedef std::function<StateCreator(StateCreator)> Enhancer;

QTREDUXSHARED_EXPORT std::unique_ptr<Store> createStore(
    Reducer reducer,
    State preloadedState = State(),
    Enhancer enhancer = nullptr);

QTREDUXSHARED_EXPORT Reducer combineReducers(Reducers reducers);

/// \todo Implement the applyMiddleware function.
/// \todo Implement the compose function.

}
