#ifndef MODELPROCE_H
#define MODELPROCE_H

//#include <Python.h>
#include<QThread>
#include<QFile>
#include<QMutex>

class modelproce : public QThread
{
    Q_OBJECT
public:
    modelproce();
    QString modelstr,wyk_fielpath,wyk_modelfile,temp_string,length_index;
    QString pre_meth,lvbo_meth,wave_meth,lvbo_meth_low,lvbo_meth_high,wyk_data_save,batch_size;

    QString GetStates();
    QString GetLength();
    void DataDispaly();

    void SetPara(QString s1,QString s2,QString pre_meth1,QString lvbo_meth1,QString wave_meth1,
                 QString lvbo_meth_low1,QString lvbo_meth_high1,QString data_save_path,QString batch);

    QString states;
    int temp_length,temp_length1,batch_length;
    QMutex mutex;


protected:
    void run();

signals:
    void sendloadmodelstate(QString);
    void sendtempstate(QString);
    void sendseriesdata(QVector<QPointF>);
};


class messeproce : public QThread
{
    Q_OBJECT
public:
    messeproce();

    QString epoch_state,par_file;
   // QFile *epoch_file;

protected:
    void run();

signals:
    void sendepochstate(QString);

private slots:
    void receivefilestate(QString);

};


class dispproce : public QThread
{
    Q_OBJECT
public:
    dispproce();
    QMutex mutex;

protected:
    void run();

};

#endif // MODELPROCE_H
