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
    , store(createStore(combineReducers({
		{ "todos", todos },
		{ "visibilityFilter", visibilityFilter }
		})))
{
    auto addTodoWidget = new AddTodoWidget;
    connect(addTodoWidget, &AddTodoWidget::action,
            store.get(), &Store::dispatch);

    auto todoListWidget = new TodoListWidget;
    connect(todoListWidget, &TodoListWidget::action,
            store.get(), &Store::dispatch);
    connect(store.get(), &Store::changed,
            todoListWidget, &TodoListWidget::update);

    auto footer = new Footer;
    connect(footer, &Footer::action,
            store.get(), &Store::dispatch);
    connect(store.get(), &Store::changed,
            footer, &Footer::update);

    auto layout = new QVBoxLayout;
    layout->addWidget(addTodoWidget);
    layout->addWidget(todoListWidget);
    layout->addWidget(footer);
    setLayout(layout);

    store->dispatch();
}
