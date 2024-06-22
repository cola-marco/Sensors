#include "View/SearchBar.h"

SearchBar::SearchBar(QWidget* parent) : QWidget(parent) {

    search_sensor = new QLineEdit(this);

    // creates widgets
    QVBoxLayout* Vlayout = new QVBoxLayout(this);
    Vlayout->setAlignment(Qt::AlignHCenter  | Qt::AlignTop);

    QLabel* title_search = new QLabel(this);
    title_search->setAlignment(Qt::AlignHCenter);
    Vlayout->addWidget(search_sensor);

    QFormLayout* form = new QFormLayout();
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    form->addRow("Search Sensor", search_sensor);
    Vlayout->addLayout(form);

    //Adds commands
    QGridLayout* commands = new QGridLayout();
    Vlayout->addLayout(commands);

    setLayout(Vlayout);
    connect(search_sensor, &QLineEdit::textChanged, this, &SearchBar::searchTextChanged);
}

//refresh method
void SearchBar::refresh() {
    sensorInfo->show();
}

