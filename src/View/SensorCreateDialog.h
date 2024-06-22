#ifndef SENSORCREATEDIALOG_H
#define SENSORCREATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QLabel>

class SensorCreateDialog : public QDialog {
    Q_OBJECT

public:
    SensorCreateDialog(QWidget *parent = nullptr);

    QString getSelectedSensorType() const;
    QString getSensorName() const;

private:
    QRadioButton* tempRadioButton;
    QRadioButton* humRadioButton;
    QRadioButton* dustRadioButton;
    QLineEdit* sensorNameLineEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;

private slots:
    void onOkButtonClicked();

};

#endif // SENSORCREATEDIALOG_H
