//#include "modelproce.h"
#include <Python.h>
#include <QList>
#include <QQueue>


#include "dialog.h"

static PyObject* pModule;


QQueue<QVector<QPointF>> wyk_data;

modelproce::modelproce()
{


    Py_SetPythonHome((const wchar_t *)(L"D:/anaconda"));

    Py_Initialize();     // 在构造函数中进行py的初始化

    if ( !Py_IsInitialized() )
    {
        emit sendloadmodelstate("python error");
    return;
    }

}

messeproce::messeproce()
{
    //epoch_file=new QFile("epoch.txt");
}


void messeproce::receivefilestate(QString x)
{
    par_file=x;

}

dispproce::dispproce()
{}

QString modelproce::GetStates()
{
    return states;
}
QString modelproce::GetLength()
{
    QString temp=QString::number(temp_length1);
    return temp;
}

void modelproce::SetPara(QString s1,QString s2,QString pre_meth1,QString lvbo_meth1,QString wave_meth1,
                         QString lvbo_meth_low1,QString lvbo_meth_high1,QString data_save_path,QString batch)
{
    wyk_fielpath=s1;
    wyk_modelfile=s2;
    pre_meth=pre_meth1;
    lvbo_meth=lvbo_meth1;
    wave_meth=wave_meth1;
    lvbo_meth_low=lvbo_meth_low1;
    lvbo_meth_high=lvbo_meth_high1;
    wyk_data_save=data_save_path;
    batch_size=batch;
}

void modelproce::run()
{
    states="unloaded";
    std::string str,str1,str2,str3,str4,str5,str6,str_length_index;
    PyObject* pArgs = NULL;
    PyObject* pFun = NULL;
    PyObject* length_wyk = NULL;
    PyObject* pylist=NULL;
    int data_length=0;

    emit sendloadmodelstate("loading....");
    Dialog::test_wyk="in modelproce";

    // 导入脚本模块
    pModule = PyImport_ImportModule("test_wyk4");      // 2019 test_wyk2文件使用的是no_graph的加载方式，和test_wyk文件不一样，经测试无误
    if (!pModule) {
        emit sendloadmodelstate("Cant open file");
            modelstr="Cant open python file!";
            return;
        }
   // 导入脚本中的方法

    str1 = wyk_fielpath.toStdString();
    const char* ch1 = str1.c_str();
    str2 = wyk_modelfile.toStdString();
    const char* ch2 = str2.c_str();

    str3 = pre_meth.toStdString();
    const char* ch3 = str3.c_str();
    str4 = wyk_modelfile.toStdString();
    const char* ch4 = str4.c_str();
    str5 = wyk_data_save.toStdString();
    const char* ch5 = str5.c_str();        // 从软件界面传入的参数，数据预处理参数
    str6 = batch_size.toStdString();
    const char* ch6 = str6.c_str();

    length_index=QString::number(data_length,10);
    str_length_index = length_index.toStdString();
    const char* ch_length_index = str_length_index.c_str();

/***
* 读数据，获得长度等信息
***/
    pFun= PyObject_GetAttrString(pModule,"read_data");

    if(!pFun){
        emit sendloadmodelstate("read_data function failed");
        modelstr="Get read_data function failed";
        return ;
    }
    pArgs = Py_BuildValue("(s,s,s)", ch1,ch6,ch3);
    length_wyk=PyObject_CallObject(pFun,pArgs);
    PyArg_Parse(length_wyk,"i",&data_length);

    temp_string=QString::number(data_length,10);
    emit sendtempstate(temp_string);

/***
* 加载模型
***/
    pFun= PyObject_GetAttrString(pModule,"load_model");

    if(!pFun){
        emit sendloadmodelstate("load_model function failed");
        modelstr="Get load_model function failed";
        return ;
    }
    pArgs = Py_BuildValue("(s,s)", ch1,ch2);
    PyObject_CallObject(pFun,pArgs);
    emit sendtempstate("model loaded");


/***
* 分段处理数据
***/

    double signal_item;         // 放在外部避免多次定义
    PyObject *list_item = NULL;

    QVector<QPointF> dataVec;
    QPointF tempdata;

    for(int i=0;i<data_length;i++)
    {

    length_index=QString::number(i,10);
    dataVec.clear();
    str_length_index = length_index.toStdString();
    ch_length_index = str_length_index.c_str();

    pFun= PyObject_GetAttrString(pModule,"process_data");

    if(!pFun){
        emit sendloadmodelstate("process_data function failed");
        modelstr="Get process_data function failed";
        return ;
            }
    pArgs = Py_BuildValue("(s,s)", ch1,ch_length_index);
    pylist=PyObject_CallObject(pFun,pArgs);
 /***
 * 显示前的数据处理
 ***/

    batch_length=batch_size.toInt();
    // 就目前来看，不是Python脚本运行的问题，也不是数据转换用的时间慢，而是数据添加进图表比较慢
    for(int i=0;i<batch_length;++i)
    {
    list_item = PyList_GetItem(pylist, i);
    signal_item=PyFloat_AsDouble(list_item);
    tempdata.setX(i);
    tempdata.setY(signal_item);
    dataVec.append(tempdata);
    //  series->append(i,signal_item);   // 另一种一个个往里面添加数据的方式
    }
    mutex.lock();
    wyk_data.push_back(dataVec);
    dataVec.clear();
    emit sendtempstate(QString::number(wyk_data.size(),10));
    //emit sendseriesdata(dataVec);
    mutex.unlock();

    }

/***
* 数据保存
***/
    emit sendtempstate("saving data... ");
    pFun= PyObject_GetAttrString(pModule,"data_save");

    if(!pFun){
        emit sendloadmodelstate("data_save function failed");
        modelstr="Get data_save function failed";
        return ;
    }
    pArgs = Py_BuildValue("(s)", ch5);
    PyObject_CallObject(pFun,pArgs);
    emit sendtempstate("data saved");


/***
// 2019 测试用的其他方法

 // 导入脚本中的方法
//    pFun= PyObject_GetAttrString(pModule,"add_wyk");

//    if(!pFun){
//        modelstr="Get function hello failed";
//        return;
//    }

//    PyObject* result_wyk = NULL;

//    pArgs = Py_BuildValue("(i,i)", 1,4);

//    result_wyk=PyObject_CallObject(pFun,pArgs);
//    int c=0;
//    PyArg_Parse(result_wyk,"i",&c);


    // 导入脚本中的方法

//     pFun= PyObject_GetAttrString(pModule,"GetSignalList");

//        if(!pFun){
//            modelstr="Get function data failed";
//            return;
//        }

//        str = wyk_fielpath.toStdString();
//        const char* ch10 = str.c_str();

//        str1 = pre_meth.toStdString();   // in GetSignalList function test whether parameters works well
//        const char* ch11 = str1.c_str();

//        pArgs = Py_BuildValue("(s,s)", ch10,ch11);
//        PyObject* pylist=PyObject_CallObject(pFun,pArgs);

//        int length=PyObject_Size(pylist);

//        temp_length=length;

//        double signal_item;
//        PyObject *list_item = NULL;

//        //QVector<QPointF>* dataVec = new QVector<QPointF>(length);
//        QList<QPointF> dataVec;
//        QPointF tempdata;
//    // 就目前来看，不是Python脚本运行的问题，也不是数据转换用的时间慢，而是数据添加进图表比较慢
//        for(int i=0;i<1000;++i)
//        {
//            list_item = PyList_GetItem(pylist, i);
//            signal_item=PyLong_AsDouble(list_item);
//            tempdata.setX(i);
//            tempdata.setY(signal_item);
//            dataVec.append(tempdata);
//            //series->append(i,signal_item);   // 另一种一个个往里面添加数据的方式
//        }
//        series->setUseOpenGL(true);
//        series->append(dataVec);
//        chart->axisX()->setRange(0,length);
//        chart->axisY()->setRange(-150,300);
***/
        emit sendloadmodelstate("ok.....");
        states=" Successfully ";
}

void messeproce::run()
{
    // 模型加载状态显示线程，单独开的线程，这里不能再调用上面的脚本了，会报错，相当于两个应用同时打开一个文件，因此这里通过一个写入和读取TXT文件实现状态共享
    // while ture,loop all the time, once changed ,emit text, thread ended in model finished time

    QFile epoch_file(par_file+"//epoch.txt");
    if(!epoch_file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        epoch_state="creat txt failed";
        emit sendepochstate(epoch_state);
        return;
    }
    epoch_file.close();

    if(!epoch_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        epoch_state="loaded txt failed";
        emit sendepochstate(epoch_state);
        return;
    }

    QByteArray line=epoch_file.readLine();
    QString temp_str(line);

    epoch_file.close();

    epoch_state="txt loaded l ";
    //emit sendepochstate(epoch_state);
    int i=0;
    while(true)
    {  // 不断的进行数据的读取
        i=i+1;
        if(i%10000000==0)       // 不能一直向主界面发送状态，要有间隔，否则主界面会一直响应，会卡死无法响应其他事件了
        {   i=0;
            //QFile epoch_file("epochqt.txt");
            if(!epoch_file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                epoch_state="loaded txt failed la ";
                emit sendepochstate(epoch_state);
                return;
            }

            line=epoch_file.readLine();
            temp_str=line;
            epoch_file.close();
            emit sendepochstate(temp_str);
        }
        if(i==100000000)
        {
            i=0;
        }


//        temp_str=epoch_state;

//        if(temp_str!=epoch_state)
//        {
//            emit sendepochstate(epoch_state);
//        }

    }

}

void dispproce::run()
{
    //准备开的数据显示线程，单独进行数据的显示
    int i=0,temp=0;;
    QVector<QPointF> disp_dataVec;
    while(true)
    {
        disp_dataVec.clear();
        i=i+1;
        if(i%1000000==0)            // 需要改进为timer定时
        {i=0;
            temp=temp+1;
            if(temp>10)
            {temp=0;}
        if(!wyk_data.empty())       // 问题得以解决，不是生产不均衡的问题，而是内存泄漏问题，之前的vector
            // 每次append之后没有清空，导致自身不断增大，所以这里的vector使用后都要进行clear
        {
            mutex.lock();
            disp_dataVec=wyk_data.front();
            wyk_data.pop_front();
            mutex.unlock();
            //for(int j=0;j<10000;j++)
            //{
                //disp_dataVec.append(QPointF(j,temp));    //
           // }
            Dialog::series->replace(disp_dataVec);
        }

        }

    }
}
