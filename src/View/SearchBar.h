#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QStringList>
#include <QListWidget>

#include "SensorInfo.h"

class SearchBar : public QWidget {
    Q_OBJECT

private:
    QLineEdit* search_sensor;
    SensorInfo* sensorInfo;

public:
    explicit SearchBar(QWidget* parent = nullptr);

signals:
    void searchTextChanged(const QString& text);
    void addButtonClicked();

public slots:
    void refresh();

};

#endif // SEARCHBAR_H
