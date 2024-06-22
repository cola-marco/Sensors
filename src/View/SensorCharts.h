#ifndef SENSORCHARTS_H
#define SENSORCHARTS_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QtCharts/QScatterSeries>


class SensorCharts : public QWidget {
    Q_OBJECT

public:
    explicit SensorCharts(QWidget* parent = nullptr);

    void updateChartData(const QVector<double>& data, const QString& sensorType);

signals:
    void pointClicked(int index);

private:
    QChartView* chartView;
    QLineSeries* series;
    QChart* chart;
    QValueAxis* axisX;
    QValueAxis* axisY;

    QScatterSeries* scatterSeries;

private slots:
    void handlePointClicked(const QPointF &point);

};

#endif // SENSORCHARTS_H
