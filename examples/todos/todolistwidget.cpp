#include "actions.h"
#include "reducers.h"
#include "todolistwidget.h"

#include <QtWidgets>

TodoListWidget::TodoListWidget(QWidget *parent)
    : QWidget(parent)
    , model(new QStandardItemModel)
{
    auto listView = new QListView;
    listView->setModel(model);

    auto layout = new QVBoxLayout;
    layout->addWidget(listView);
    setLayout(layout);

    connect(listView, &QListView::clicked,
            this, [this](QModelIndex const &index)
    {
        auto id = index.data(Qt::UserRole).toString();
        emit action(toggleTodo(id));
    });
}

void TodoListWidget::update(QVariant state)
{
    auto todos = getVisibleTodos(state.toMap());

    model->clear();

    for(auto it = todos.begin(); it != todos.end(); ++it)
    {
        auto todo = it.value().toMap();
        auto text = todo.value("text").toString();
        auto completed = todo.value("completed").toBool();

        auto item = new QStandardItem(text);
        auto font = item->font();
        font.setStrikeOut(completed);
        item->setFont(font);
        item->setData(it.key(), Qt::UserRole);
        model->appendRow(item);
    }
}
