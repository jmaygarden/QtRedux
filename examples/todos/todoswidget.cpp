#include "actions.h"
#include "addtodowidget.h"
#include "footer.h"
#include "reducers.h"
#include "todolistwidget.h"
#include "todoswidget.h"

#include <QtRedux>
#include <QtWidgets>

using namespace QtRedux;

TodosWidget::TodosWidget(QWidget *parent)
    : QWidget(parent)
    , store(createStore<QVariantStore>(
        combineReducers({
		{ "todos", todos },
		{ "visibilityFilter", visibilityFilter }
		})))
{
    auto addTodoWidget = new AddTodoWidget;
    connect(addTodoWidget, &AddTodoWidget::action,
            store.get(), &QVariantStore::dispatch);

    auto todoListWidget = new TodoListWidget;
    connect(todoListWidget, &TodoListWidget::action,
            store.get(), &QVariantStore::dispatch);
    connect(store.get(), &QVariantStore::changed,
            todoListWidget, &TodoListWidget::update);

    auto footer = new Footer;
    connect(footer, &Footer::action,
            store.get(), &QVariantStore::dispatch);
    connect(store.get(), &QVariantStore::changed,
            footer, &Footer::update);

    auto layout = new QVBoxLayout;
    layout->addWidget(addTodoWidget);
    layout->addWidget(todoListWidget);
    layout->addWidget(footer);
    setLayout(layout);

    store->dispatch(QVariantMap());
}
