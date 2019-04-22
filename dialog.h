#ifndef DIALOG_H
#define DIALOG_H

#include "modelproce.h"

#include <QDialog>
#include <QProgressBar>
#include <QWidget>
#include <QLabel>
#include <QtCore/QVector>
#include <QList>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <qfiledialog>
#include "qlibrary.h"
#include "qmessagebox.h"
#include <QLibrary>
#include <QDebug>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

//extern QString test_wyk;

QT_BEGIN_NAMESPACE
class QStringListModel;
class QStringList;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString tempstr,combb1,combb2,combb3,lvbolow,lvbohigh,batch,filepath,modelpath,
    parfilepath,data_save_path;

    QStringListModel *typeModel;
    int runpy();
    static QSplineSeries *series;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axis;
    modelproce *model;
    messeproce *messe_wyk;
    dispproce  *display_wyk;

    static QString test_wyk;
    int batchsize;
    QVector<QPointF> display_vec;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

    void receiveloadmodelstate(QString);

    void receiveepochstate(QString);

    void on_pushButton_5_clicked();

    void receivetempstate(QString);

    void receiveseriesdata(QVector<QPointF>);

signals:
    void sendfilestate(QString);

private:
    Ui::Dialog *ui;

    QLabel *label1,*label2;
//    QLineEdit *inedit1,*inedit2,*outedit1,*outedit2;
//    QPushButton *okbutton;


};

#endif // DIALOG_H
