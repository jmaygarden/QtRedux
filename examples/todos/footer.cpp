#include "actions.h"
#include "footer.h"

#include <QtWidgets>

using namespace QtRedux;

Footer::Footer(QWidget *parent)
    : QWidget(parent)
    , group(new QButtonGroup)
{
    auto layout = new QHBoxLayout;
    auto filters = getVisibilityFilters();

    for (auto it = filters.begin(); it != filters.end(); ++it)
    {
        auto button = new QRadioButton(it.value());
        layout->addWidget(button);
        group->addButton(button, it.key());
    }

    setLayout(layout);

    connect(group, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, [this](int id)
    {
        auto visibilityFilter = static_cast<VisibilityFilter> (id);
        emit action(setVisibilityFilter(visibilityFilter));
    });
}

void Footer::update(QtRedux::State state)
{
    auto visibilityFilter = state.toMap().value("visibilityFilter").toInt();

    group->button(visibilityFilter)->setChecked(true);
}
