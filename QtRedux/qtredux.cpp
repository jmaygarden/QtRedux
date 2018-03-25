#include "qtredux.h"

namespace QtRedux
{

Store::Store(Reducer reducer, State preloadedState)
    : QObject()
    , reducer(reducer)
    , state(preloadedState)
{
}

Action Store::dispatch(Action action)
{
    state = reducer(state, action);
    emit changed(state);
    return action;
}

void Store::replaceReducer(Reducer nextReducer)
{
    reducer = nextReducer;
    dispatch(Action());
}

std::shared_ptr<Store> createStore(Reducer reducer,
                                   State preloadedState,
                                   Enhancer enhancer)
{
    auto store = std::shared_ptr<Store>(new Store(reducer, preloadedState));

    return enhancer ? enhancer(store)(reducer, preloadedState) : store;
}

Reducer combineReducers(Reducers reducers)
{
    return [reducers](State const &state, Action const &action)
    {
        QVariantMap nextState(state.toMap());

        for (auto it = reducers.begin(); it != reducers.end(); ++it)
        {
            QString const & key = it.key();
            Reducer reducer = it.value();

            if (reducer)
            {
                auto partition = nextState.value(key);
                nextState.insert(key, reducer(partition, action));
            }
        }

        return nextState;
    };
}

}
