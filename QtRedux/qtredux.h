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
#include <vector>

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace QtRedux
{
    template<typename State, typename Action>
    using Reducer = std::function<State(State const &, Action const &)>;

    template<typename State>
    using Subscriber = std::function<void(State const &)>;

    template<typename State, typename Action>
    class Store
    {
    public:
        Store(Reducer<State, Action> reducer, State preloadedState)
            : reducer(std::move(reducer))
            , state(std::move(preloadedState))
            , subscribers()
        {
        }

        State const & getState() const { return state; }

        Action dispatch(Action action)
        {
            state = reducer(state, action);
            
            for (auto subscriber : subscribers)
            {
                subscriber(state);
            }

            return action;
        }

        void replaceReducer(Reducer<State, Action> nextReducer)
        {
            reducer = nextReducer;
            dispatch(Action());
        }

        std::function<void(void)> subscribe(Subscriber<State> subscriber)
        {
            subscribers.push_back(std::move(subscriber));
            auto it = std::prev(subscribers.cend());
            return [subscribers, it]()
            {
                subscribers.erase(it);
            };
        }

    private:        
        Reducer<State, Action> reducer;
        State state;
        std::vector<Subscriber<State>> subscribers;
    };

    template<typename Store, typename State, typename Action>
    using StoreCreator = std::function<std::unique_ptr<Store>(Reducer<State, Action>, State)>;

    template<typename Store, typename State, typename Action>
    using Enhancer = std::function<StoreCreator<Store, State, Action>(StoreCreator<Store, State, Action>)>;

    template<typename Store, typename State, typename Action>
    std::unique_ptr<Store> createStore(
        Reducer<State, Action> reducer,
        State preloadedState = State())
    {
        return std::unique_ptr<Store>(new Store(reducer, preloadedState));
    }

    template<typename Store, typename State, typename Action>
    std::unique_ptr<Store> createStore(
        Reducer<State, Action> reducer,
        State preloadedState,
        Enhancer<Store, State, Action> enhancer)
    {
        return enhancer(static_cast<std::unique_ptr<Store>(*)(Reducer<State, Action>, State)>
            (createStore))(reducer, preloadedState);
    }

    template<typename Store, typename State, typename Action>
    std::unique_ptr<Store> createStore(
        Reducer<State, Action> reducer,
        Enhancer<Store, State, Action> enhancer)
    {
        return createStore(reducer, State(), enhancer);
    }

    template<typename State, typename Action>
    using Reducers = QMap<QString, Reducer<State, Action>>;

    class QTREDUXSHARED_EXPORT QVariantStore : public QObject
    {
        Q_OBJECT

    public:
        QVariantStore(Reducer<QVariant, QVariantMap> reducer, QVariant preloadedState);

        QVariant const & getState() const { return state; }

    public slots:
        QVariantMap dispatch(QVariantMap action);

        void replaceReducer(Reducer<QVariant, QVariantMap> nextReducer);

    signals:
        void changed(QVariant const&);

    private:
        Reducer<QVariant, QVariantMap> reducer;
        QVariant state;
    };

    QTREDUXSHARED_EXPORT Reducer<QVariant, QVariantMap> combineReducers(
        Reducers<QVariant, QVariantMap> reducers);

    /// \todo Implement the applyMiddleware function.
    /// \todo Implement the compose function.

}
