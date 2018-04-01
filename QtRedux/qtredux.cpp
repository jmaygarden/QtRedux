#include "qtredux.h"

namespace QtRedux
{
    QVariantStore::QVariantStore(Reducer<QVariant, QVariantMap> reducer, QVariant preloadedState)
        : QObject()
        , reducer(std::move(reducer))
        , state(std::move(preloadedState))
    {
    }

    QVariantMap QVariantStore::dispatch(QVariantMap action)
    {
        state = reducer(state, action);
        emit changed(state);
        return action;
    }

    void QVariantStore::replaceReducer(Reducer<QVariant, QVariantMap> nextReducer)
    {
        reducer = nextReducer;
        dispatch(QVariantMap());
    }

    Reducer<QVariant, QVariantMap> combineReducers(
        Reducers<QVariant, QVariantMap> reducers)
    {
        return [reducers](QVariant const& state, QVariantMap const &action)
        {
            QVariantMap nextState(state.toMap());

            for (auto it = reducers.begin(); it != reducers.end(); ++it)
            {
                QString const & key = it.key();
                auto reducer = it.value();

                if (reducer)
                {
                    auto partition = nextState.value(key).toMap();
                    nextState.insert(key, reducer(partition, action));
                }
            }

            return nextState;
        };
    }

}
