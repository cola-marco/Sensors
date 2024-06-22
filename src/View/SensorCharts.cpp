#include "SensorCharts.h"

SensorCharts::SensorCharts(QWidget* parent) : QWidget(parent) {
    series = new QLineSeries();
    chart = new QChart();

    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    scatterSeries->setMarkerSize(10.0);
    scatterSeries->setColor(Qt::red);
    scatterSeries->setBorderColor(Qt::black);

    chart->addSeries(series);
    chart->addSeries(scatterSeries);

    axisX = new QValueAxis;
    axisY = new QValueAxis;

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    scatterSeries->attachAxis(axisX);
    series->attachAxis(axisY);
    scatterSeries->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);

    connect(scatterSeries, &QScatterSeries::clicked, this, &SensorCharts::handlePointClicked);
}

//update the data of the chart
void SensorCharts::updateChartData(const QVector<double>& data, const QString& sensorType) {
    series->clear();
    scatterSeries->clear();
    for (int i = 0; i < data.size(); ++i) {
        series->append(i, data[i]);
        scatterSeries->append(i, data[i]);
    }
    axisX->setRange(0, data.size() - 1);

    //set the range of the Y axis based on the sensor type (temperature can go under 0)
    if (sensorType == "Temperature") {
        // Find min and max values in data
        double minValue = *std::min_element(data.begin(), data.end());
        double maxValue = *std::max_element(data.begin(), data.end());
        axisY->setRange(minValue, maxValue);
    } else {
        axisY->setRange(0, 100);
    }
}

//handle the click on a point
void SensorCharts::handlePointClicked(const QPointF &point) {
    int index = static_cast<int>(point.x());
    emit pointClicked(index); //emit the signal pointClicked
}
