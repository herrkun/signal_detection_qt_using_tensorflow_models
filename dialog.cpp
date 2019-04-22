#include "dialog.h"
#include "ui_dialog.h"
#include <Python.h>
#include<QFileInfo>
#include<QDir>
#include<QVector>
#include<QPointF>
// 12.03 如果将#include <Python.h>放到dialog.h目录下，在添加沟槽机制会引发错误
QT_CHARTS_USE_NAMESPACE


QString Dialog::test_wyk="in dialog";
QSplineSeries* Dialog::series = new QSplineSeries();

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->lineEdit_2->setText(Dialog::test_wyk);

    // 2019 此处的初始化放在了数据加载线程中了，该方法只要初始化一个实例就会通过构造函数自动调用
//    Py_Initialize();     // 在构造函数中进行py的初始化

//    if ( !Py_IsInitialized() )
//    {
//    return;
//    }

    model=new modelproce;       // 这里的线程全都是通过实例来调用的，class的使用很有趣，下学期可以搞搞effect c++
    messe_wyk=new messeproce;
    display_wyk=new dispproce;
    connect(model,SIGNAL(sendloadmodelstate(QString)),this,SLOT(receiveloadmodelstate(QString)));
    connect(messe_wyk,SIGNAL(sendepochstate(QString)),this,SLOT(receiveepochstate(QString)));
    connect(this,SIGNAL(sendfilestate(QString)),messe_wyk,SLOT(receivefilestate(QString)));
    connect(model,SIGNAL(sendtempstate(QString)),this,SLOT(receivetempstate(QString)));
    connect(model,SIGNAL(sendseriesdata(QVector<QPointF>)),this,SLOT(receiveseriesdata(QVector<QPointF>)));

    QStringList mode_list;
    mode_list<<("None process")<<("Min-Max Normalization")<<("Mean Normaliztion");
    ui->comboBox->addItems(mode_list);
    // combb1=ui->comboBox->currentText();   // or currentIndex()

    QStringList lvbo_list;
    lvbo_list<<("None process")<<("High filter")<<("Low filter")<<("Brand filter")<<("Wave filter");
    ui->comboBox_2->addItems(lvbo_list);

    QStringList wave_list;
    wave_list<<("haar")<<("db")<<("sym")<<("blo");
    ui->comboBox_3->addItems(wave_list);

    ui->progressBar->setRange(0,100);
    ui->progressBar->reset();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);

    double dProgress = 0;
    ui->progressBar->setFormat(QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(dProgress, 'f', 1)));
    ui->progressBar->setFormat(tr("Current progress : %1%").arg(QString::number(dProgress, 'f', 1)));
    ui->progressBar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->progressBar->setValue(dProgress*100);

// 2019 一般都在UI上直接添加，方便修改大小样式位置等
//    label1=new QLabel(this);
//    label1->setText(tr("Parameter 1 :"));
//    label2=new QLabel(this);
//    label2->setText(tr("Parameter 2 :"));

//    inedit1=new QLineEdit(this);
//    inedit2=new QLineEdit(this);
//    outedit1=new QLineEdit(this);
//    outedit2=new QLineEdit(this);

//    okbutton=new QPushButton(this);
//    okbutton->setText(tr("参数重载"));

//    QGridLayout *mainlayout=new QGridLayout(this);
//    mainlayout->addWidget(label2,1,0);
//    mainlayout->addWidget(inedit1,0,1);
//    mainlayout->addWidget(inedit2,1,1);
//    mainlayout->addWidget(outedit1,0,2);
//    mainlayout->addWidget(outedit2,1,2);
//    mainlayout->addWidget(okbutton,2,1);


    axis=new QValueAxis;

    chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);      //设置坐标必须在createDefaultAxes方法之后
    chart->axisX()->setRange(0,100);
    chart->axisY()->setRange(-1,1);
    chart->setAnimationOptions(QChart::NoAnimation);  //动态画图
    chart->setTitle("railway detection system");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(650,400);
    chartView->show();

    //chartView->moveToThread(display_wyk);
    //ui->verticalLayout->moveToThread(display_wyk);
    ui->verticalLayout->addWidget(chartView);
    //QGridLayout *mainlayout=new QGridLayout(this);
    //mainlayout->addWidget(chartView,370,120);


}


int Dialog::runpy() // 2019 该方法暂时没用了（没有任何调用），之前是测试用的，暂时先放在这里作为参考
{   // 该方法暂时保存，作为第一个调用Python的demo day:1.10

    // 从初始化处获得初始值参数
    bool ok;
    combb1=ui->comboBox->currentText();
    combb2=ui->comboBox_2->currentText();
    combb3=ui->comboBox_3->currentText();
    lvbolow=ui->lineEdit_4->text();
    lvbohigh=ui->lineEdit_5->text();
    int frequence1=lvbolow.toInt(&ok);
    int frequence2=lvbohigh.toInt(&ok);
    batch=ui->lineEdit_3->text();
    int batchsize=batch.toInt(&ok);

    // 导入脚本模块
    PyObject* pModule = PyImport_ImportModule("test_wyk");
    if (!pModule) {
            tempstr="Cant open python file!";

            ui->lineEdit_2->setText(tempstr);
            return -1;
        }
   // 导入脚本中的方法
    PyObject* pFun= PyObject_GetAttrString(pModule,"hello");

    if(!pFun){
        tempstr="Get function hello failed";

        ui->lineEdit_2->setText(tempstr);
        return -1;
    }

    PyObject* pArgs = NULL;

    pArgs = Py_BuildValue("(s)", "wyk finally vic");

    PyObject_CallObject(pFun,pArgs);

//导入脚本中的方法
    pFun= PyObject_GetAttrString(pModule,"add_wyk");

    if(!pFun){
        tempstr="Get function hello failed";

        ui->lineEdit_2->setText(tempstr);
        return -1;
    }

    PyObject* result_wyk = NULL;

    pArgs = Py_BuildValue("(i,i)", 1,4);

    result_wyk=PyObject_CallObject(pFun,pArgs);
    int c=0;
    PyArg_Parse(result_wyk,"i",&c);

    tempstr=QString::number(c);
    ui->lineEdit->setText(tempstr);


// 导入脚本中的方法
    tempstr="begin to loade";
    ui->lineEdit_2->setText(tempstr);

    pFun= PyObject_GetAttrString(pModule,"GetSignalList");

    if(!pFun){
        tempstr="Get function data failed";

        ui->lineEdit_2->setText(tempstr);
        return -1;
    }

    std::string str = filepath.toStdString();
    const char* ch = str.c_str();

    pArgs = Py_BuildValue("(s)", ch);
    PyObject* pylist=PyObject_CallObject(pFun,pArgs);
    int length=PyObject_Size(pylist);

    tempstr=QString::number(length);
    ui->lineEdit->setText(tempstr);

    double signal_item;
    PyObject *list_item = NULL;

    tempstr="loaded,transfaring";
    ui->lineEdit_2->setText(tempstr);

    tempstr=QString::number(length);
    ui->lineEdit_3->setText(tempstr);

    //QVector<QPointF>* dataVec = new QVector<QPointF>(length);
    QList<QPointF> dataVec;
    QPointF tempdata;
// 就目前来看，不是Python脚本运行的问题，也不是数据转换用的时间慢，而是数据添加进图表比较慢
    for(int i=0;i<length;++i)
    {
        list_item = PyList_GetItem(pylist, i);
        signal_item=PyLong_AsDouble(list_item);
        tempdata.setX(i);
        tempdata.setY(signal_item);
        dataVec.append(tempdata);
        //series->append(i,signal_item);
    }
    //series->setUseOpenGL(true);
    //series->append(dataVec);
    //chart->axisX()->setRange(0,length);
//    chart->axisY()->setRange(-150,300);

    tempstr=QString::number(signal_item);
    ui->lineEdit->setText(tempstr);

    tempstr="everything ok";
    ui->lineEdit_2->setText(tempstr);


    Py_Finalize();


}



Dialog::~Dialog()
{
    delete ui;
}

void Dialog::receiveloadmodelstate(QString x)
{
    ui->lineEdit->setText(x);
    ui->lineEdit_2->setText(Dialog::test_wyk);
}

void Dialog::receivetempstate(QString x)
{
    ui->lineEdit_10->setText(x);
}

int temp_flag=1;
void Dialog::receiveseriesdata(QVector<QPointF> datavec)
{
    if(temp_flag)
    {
        chart->axisX()->setRange(0,batchsize);
        chart->axisY()->setRange(0,1);
        temp_flag=0;
    }
    display_vec=datavec;
    Dialog::series->replace(display_vec);
}

QList<QString> number;
QString num_str1,num_str2;
double num;
bool ok;
void Dialog::receiveepochstate(QString x)   // 进度条和lineEdit_8显示框处理程序
{
    number=x.split('/');
    num_str1=number[0];
    if(num_str1.toDouble(&ok)){num_str2=number[1];}
    if(num_str1.toDouble(&ok))
    {
        num=(num_str1.toDouble(&ok))/(num_str2.toDouble(&ok));
        num=num*100;
        ui->progressBar->setFormat(QString::fromLocal8Bit("当前进度为：%1%").arg(QString::number(num, 'f', 1)));
        ui->progressBar->setFormat(tr("Current progress : %1%").arg(QString::number(num, 'f', 1)));
        ui->progressBar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->progressBar->setValue(num);

    }
    ui->lineEdit_8->setText(x);
}



void Dialog::on_pushButton_clicked()   // loadrun按钮处理程序，启动数据加载模型，并通过一个model实例传递参数
{
    // 从初始化处获得初始值参数
    bool ok;
    combb1=ui->comboBox->currentText();
    combb2=ui->comboBox_2->currentText();
    combb3=ui->comboBox_3->currentText();
    lvbolow=ui->lineEdit_4->text();
    lvbohigh=ui->lineEdit_5->text();
    int frequence1=lvbolow.toInt(&ok);
    int frequence2=lvbohigh.toInt(&ok);
    batch=ui->lineEdit_3->text();
    batchsize=batch.toInt(&ok);

    model->SetPara(filepath,modelpath,combb1,combb2,combb3,lvbolow,lvbohigh,data_save_path,batch);

    messe_wyk->start();

    model->start();

    // no more words
}

// 该按钮暂时就是一个测试曲线的控件，后期可改为他用
void Dialog::on_pushButton_2_clicked()
{
    chart->axisX()->setRange(0,batchsize);
    chart->axisY()->setRange(0,1);
    display_wyk->start();

}

void Dialog::on_pushButton_3_clicked()// 获得数据，a .mat file
{
    filepath=QFileDialog::getOpenFileName(this,"open your files","/");     // 获得文件
    QFileInfo fileinfo(filepath);
    //parfilepath=QFileDialog::getExistingDirectory(this);                   // 获得文件夹地址
    QDir dir=fileinfo.absoluteDir();
    parfilepath=dir.absolutePath();
    emit sendfilestate(parfilepath);
    ui->lineEdit_6->setText(filepath);
}

void Dialog::on_pushButton_4_clicked()// 获得模型，a .meta file
{
    modelpath=QFileDialog::getOpenFileName(this,"open a .meta file","/");
    ui->lineEdit_7->setText(modelpath);
}

void Dialog::on_pushButton_5_clicked()
{
    data_save_path=QFileDialog::getExistingDirectory(this);
    ui->lineEdit_9->setText(data_save_path);
}
