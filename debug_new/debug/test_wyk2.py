
# -*- coding: utf-8 -*-

import numpy as np
import pywt
import pywt.data
from scipy import signal
import scipy.io as sio
import os
import tensorflow as tf
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'     #消除tf avxx error


print("ni hao 6 bits",np.__version__)

import time
import random
import h5py

# 设置 GPU 按需增长
config = tf.ConfigProto()
config.gpu_options.allow_growth = True
sess = tf.Session(config=config)
####参数设置
input_size=1  ###x 数据的特征维数,等于输入维数
output_size=1

rnn_unit=100     #隐藏节点数目
num_layer=2      #层数

lr=0.01  #学习率
decay_rate=0.97 ###学习衰减率

keep_prob_train=1
epoch_num=300
epoch_num_checkpoint=5
stop_mse=1e-8

train_en=0
countinue_train=0

time_step_train=25
batch_index_train=200

pre_state="The predict step:"
state=pre_state+str(0)
"""
# this function works well,just test whether model is successfully loaded
def reload_model(modelfile):
    modelfile=modelfile
    model_parfile=os.path.dirname(modelfile)
    sess= tf.Session()
    saver = tf.train.import_meta_graph(modelfile)
    module_file = tf.train.latest_checkpoint(model_parfile)
    saver.restore(sess, module_file)
    
    graph = tf.get_default_graph()
    test = graph.get_tensor_by_name("lstm/b_in:0")
    b=sess.run(test)
    b=b.tolist()
    return b
"""
tf.reset_default_graph()  





def reload_model(filepath,modelfile,pre_mode='no',lvbo_mode='no',lvbo1=8,low=0,high=0,wave1='sym5',wave2=3):
    print(filepath)
    filepathaa1=os.path.abspath(filepath)
    file_parfile=os.path.dirname(filepath)
    with open(file_parfile+'//epoch.txt','w') as f:
    	f.write(str(0)+' / '+str(0))
    volt_data2 = sio.loadmat(filepath)  # r'E:\huihuang_mat\4/4-11.mat'
    volt_data2 = volt_data2['signal_whole']     # 此处有可能不对，以后也不用mat文件了
    volt_data2 = volt_data2.reshape(volt_data2.shape[0],)
    volt_data2=(volt_data2 - volt_data2.mean())/volt_data2.std()

    if pre_mode=="Min-Max Normalization":

        volt_min=volt_data2.min()
        volt_max=volt_data2.max()

        volt_data2=(volt_data2-volt_min)/(volt_max-volt_min)

        volt_data2=volt_data2*2-1
    if pre_mode=="Mean Normaliztion":
        volt_data2=(volt_data2 - volt_data2.mean())/volt_data2.std()

    if lvbo_mode=="High filter":
        high=float((2*high)/5000)
        b, a = signal.butter(lvbo1, high, 'highpass')
        volt_data2 = signal.filtfilt(b, a, volt_data2)
    if lvbo_mode=="Low filter":
        low=float((2*low)/5000)
        b, a = signal.butter(lvbo1, 0.02, 'lowpass')  
        volt_data2 = signal.filtfilt(b, a, volt_data2)    
    if lvbo_mode=="Brand filter":
        low=float((2*low)/5000)
        high=float((2*high)/5000)
        b, a = signal.butter(lvbo1, [low,high], 'bandpass')
        volt_data2 = signal.filtfilt(b, a, volt_data2)  

    if lvbo_mode=="Wave filter":   # 此处需要修改，只返回一个值，因为数据量太大，不支持有多个
        w = pywt.Wavelet(wave1)#选取小波函数
        a = volt_data2
        ca = []#近似分量
        cd = []#细节分量
        mode = pywt.Modes.smooth
        for i in range(5):
            (a, d) = pywt.dwt(a, w, mode)#进行5阶离散小波变换
            ca.append(a)
            cd.append(d)
       #选择特定的层数进行小波变换     
        coeff_list = [None,cd[wave2]] + [None] * wave2
        volt_data2=pywt.waverec(coeff_list, w)

    test,y_label,batch_num=SplitData(volt_data2,4096)

    modelfile=modelfile
    model_parfile=os.path.dirname(modelfile)


    sess= tf.Session()
    
    test_predict=[]
    start_time=time.time()

    saver=tf.train.import_meta_graph(modelfile)
    graph=tf.get_default_graph()
    tesor_name_list=[tensor.name for tensor in graph.as_graph_def().node]

    X=graph.get_tensor_by_name('X_Y_input/x_input:0')

    Y=graph.get_tensor_by_name('X_Y_input/y_input:0')

    keep_prob=graph.get_tensor_by_name('keep_prob/keep_prob:0')

    pred_out=graph.get_tensor_by_name('lstm/lstm_out/add:0')
    module_file = tf.train.latest_checkpoint(model_parfile)
    saver.restore(sess, module_file)

    global state
    global pre_state
    for step in range(batch_num):
        prob=sess.run(pred_out,feed_dict={X:test[step*4096:(step+1)*4096],keep_prob: 1.0})
        predict=prob.reshape((-1))
        test_predict.extend(predict)
        if step%100==0:
            with open(file_parfile+'//epoch.txt','w') as f:
                f.write(str(step)+' / '+str(batch_num))
            state=pre_state+str(step)         
            print("The predict step:",step)        
    test_predict=np.array(test_predict)
    signal=y_label-test_predict
    with open(file_parfile+'//epoch.txt','w') as f:
        f.write("save files")
        f.write(" / ")
        f.write(model_parfile+'\\signal_wyk.npy')
    np.save(model_parfile+'\\signal_wyk_nograph.npy',signal)   
    #sio.savemat(model_parfile+'\\signal_wyk2.mat', {'signal':signal}) #####保存为mat文件，result为Python中的变量，vect为mat中的变量，tst为文件名         
    
    #return signal


def add_wyk(a,b):
	return a+b

def GetSignalList(filepath,pre_mode='no',lvbo_mode='no',lvbo1=8,low=0,high=0,wave1='sym5',wave2=3):
    # this function just for test 
    print(filepath)
    filepathaa1=os.path.abspath(filepath)
    print('lalaal')
    print(filepathaa1)
    volt_data2 = sio.loadmat(filepath)  # r'E:\huihuang_mat\4/4-11.mat'
    volt_data2 = volt_data2['signal'] 
    volt_data2 = volt_data2.reshape(volt_data2.shape[0],)

    if pre_mode=="Min-Max Normalization":

        volt_min=volt_data2.min()
        volt_max=volt_data2.max()

        volt_data2=(volt_data2-volt_min)/(volt_max-volt_min)

        volt_data2=volt_data2*2-1
    if pre_mode=="Mean Normaliztion":
        volt_data2=(volt_data2 - volt_data2.mean())/volt_data2.std()

    if lvbo_mode=="High filter":
        high=float((2*high)/5000)
        b, a = signal.butter(lvbo1, high, 'highpass')
        volt_data2 = signal.filtfilt(b, a, volt_data2)
    if lvbo_mode=="Low filter":
        low=float((2*low)/5000)
        b, a = signal.butter(lvbo1, 0.02, 'lowpass')  
        volt_data2 = signal.filtfilt(b, a, volt_data2)    
    if lvbo_mode=="Brand filter":
        low=float((2*low)/5000)
        high=float((2*high)/5000)
        b, a = signal.butter(lvbo1, [low,high], 'bandpass')
        volt_data2 = signal.filtfilt(b, a, volt_data2)  

    if lvbo_mode=="Wave filter":   # 此处需要修改，只返回一个值，因为数据量太大，不支持有多个
        w = pywt.Wavelet(wave1)#选取小波函数
        a = volt_data2
        ca = []#近似分量
        cd = []#细节分量
        mode = pywt.Modes.smooth
        for i in range(5):
            (a, d) = pywt.dwt(a, w, mode)#进行5阶离散小波变换
            ca.append(a)
            cd.append(d)
       #选择特定的层数进行小波变换     
        coeff_list = [None,cd[wave2]] + [None] * wave2
        volt_data2=pywt.waverec(coeff_list, w)
    
    model_parfile='E:\\huihuang_mat\\4'
    #sio.savemat(model_parfile+'\\signal_wyk2.mat', {'signal':volt_data2})
    ecg = pywt.data.ecg()
    data2=volt_data2.tolist()
    return data2


def SplitData(rowdata,batchsize):    # 这里的data依旧是array
    length=rowdata.shape[0]
    dim=1
    timestep=25
    data=np.zeros([length-timestep,timestep,dim])
    temp=np.zeros(timestep)
    #label=np.zeros(length-timestep,1)      # 测试不用label
    for i in range(length-timestep):
        temp=rowdata[i:i+timestep]
        temp=temp.reshape([timestep,dim])
        data[i]=temp
        
    batch_num=int((length-timestep)/batchsize)    #向下取整
    y_label=rowdata[:batch_num*batchsize]
    
    return data,y_label,batch_num

def get_state():
    global state
    return state
"""
def ReadData():
#################################
##数据解析
#################################
#wfs_file_path=r'D:\PCI-2-DATA\11月最新信号-加注释\04\STREAM20181112-070729-914.wfs'
    wfs_file_path=r'F:\EXAMPLE20181203-063255-686.wfs'     #暂时还是手动指定模型路径
    wfs_file=open(wfs_file_path,'rb')

    def equal(a,b):              # 判断解析出来的数据和软件导出的数据是否一样
        if abs(a-b)<0.00001:
            return True
        else:
            return False
    data=[]            # 读取文件，先解析成十六进制进行保存
    while True:           # 可以取得每一个十六进制
        a=wfs_file.read(1)      # read（1）表示每次读取一个字节长度的数值
        if not a:
            break
        else:
            if(ord(a)<=15):
                data.append(("0x0"+hex(ord(a))[2:])[2:])
            else:
                data.append((hex(ord(a)))[2:])

    length=len(data)

    volt_data=[]              # 把十六进制的文件进行解析，换算为真实的电压数据
    standard_volt=0.00030517578125    # 间隔电压

    index=0

    while True:
    # 此处以及下面的判断条件一定要严格一些，否则会出现读取到中间某一段就停止的情况，数据读取不完整
        if data[index]=='08' and data[index+1]=='ae'and data[index+2]=='01'and data[index+3]=='64':
            index=index+29    # 跳过ID的说明字段，29个字节以后才是真正的数据
            while True:
                if data[index]=='1c' and data[index+1]=='08'and data[index+2]=='ae'and data[index+3]=='01':
                    break
                if data[index]=='07' and data[index+1]=='00'and data[index+2]=='0f'and data[index+3]=='ff'and data[index+4]=='ff':
                    break
                final=data[index+1]+data[index]
                if int(final[0],16)>7:
                    volt=((int(final,16))^(int('ffff',16)))+1
                    volt=volt*(-standard_volt)
                    volt_data.append(volt)
                else:
                    volt=int(final,16)
                    volt=volt*standard_volt
                    volt_data.append(volt)
                index=index+2
            
        if data[index]=='07' and data[index+1]=='00'and data[index+2]=='0f'and data[index+3]=='ff'and data[index+4]=='ff':
            break
    
        index=index+1
    
    volt_data=np.array(volt_data)
    return volt_data


def PreData():
    #filepath='no',pre_mode='no',lvbo_mode='no',lvbo1=8,low=0,high=0,wave1='sym5',wave2=3
    filepath=r'E:\huihuang_mat\4/4-11.mat'
    volt_data2 = sio.loadmat(r'E:\huihuang_mat\4/4-11.mat')  
    volt_data2 = volt_data2['signal'] 
    volt_data2 = volt_data2.reshape(volt_data2.shape[0],)
#################################
##数据归一化
#################################
#volt_data is a list, convert it to array
    #volt_data2=np.array(volt_data2)
    
    if pre_mode=="Min-Max Normalization":

        volt_min=volt_data2.min()
        volt_max=volt_data2.max()

        volt_data2=(volt_data2-volt_min)/(volt_max-volt_min)

        volt_data2=volt_data2*2-1
    if pre_mode=="Mean Normaliztion":
        volt_data2=(volt_data2 - volt_data2.mean())/volt_data2.std()

#################################
##数据滤波
#################################
    if lvbo_mode=="High filter":
        high=float((2*high)/5000)
        b, a = signal.butter(lvbo1, high, 'highpass')
        volt_data2 = signal.filtfilt(b, a, volt_data2)
    if lvbo_mode=="Low filter":
        low=float((2*low)/5000)
        b, a = signal.butter(lvbo1, 0.02, 'lowpass')  
        volt_data2 = signal.filtfilt(b, a, volt_data2)    
    if lvbo_mode=="Brand filter":
        low=float((2*low)/5000)
        high=float((2*high)/5000)
        b, a = signal.butter(lvbo1, [low,high], 'bandpass')
        volt_data2 = signal.filtfilt(b, a, volt_data2)  

    if lvbo_mode=="Wave filter":   # 此处需要修改，只返回一个值，因为数据量太大，不支持有多个
        w = pywt.Wavelet(wave1)#选取小波函数
        a = volt_data2
        ca = []#近似分量
        cd = []#细节分量
        mode = pywt.Modes.smooth
        for i in range(5):
            (a, d) = pywt.dwt(a, w, mode)#进行5阶离散小波变换
            ca.append(a)
            cd.append(d)
       #选择特定的层数进行小波变换     
        coeff_list = [None,cd[wave2]] + [None] * wave2
        volt_data2=pywt.waverec(coeff_list, w)
        

    volt_data2=volt_data2.tolist()
    return volt_data2
        
        
"""

"""

# 小波各个层次的重构
        rec_a = []
        rec_d = []

        for i, coeff in enumerate(ca):
            coeff_list = [coeff, None] + [None] * i
            rec_a.append(pywt.waverec(coeff_list, w))#重构

        for i, coeff in enumerate(cd):
            coeff_list = [None, coeff] + [None] * i
            rec_d.append(pywt.waverec(coeff_list, w))

"""

"""

def SplitData(rowdata,batchsize):    # 这里的data依旧是array
    length=rowdata.shape[0]
    dim=1
    timestep=25
    data=np.zeros([length-timestep,timestep,dim])
    temp=np.zeros(timestep)
    #label=np.zeros(length-timestep,1)      # 测试不用label
    for i in range(length-timestep):
        temp=rowdata[i:i+timestep]
        temp=temp.reshape([timestep,dim])
        data[i]=temp
        
    batch_num=int((length-timestep)/batchsize)    #向下取整
    
    return data,batch_num
"""



"""

train_x = sio.loadmat(r'E:\huihuang_mat\4/4-11.mat')  
train_x = train_x['signal'] 
train_x = train_x.reshape(train_x.shape[0],)
print("train_x shape:", train_x.shape)

plt.figure()
plt.plot(train_x)
    
train_x=PreData(train_x,'Min-Max Normalization')

    
train_x=PreData(train_x,'Mean Normaliztion')
plt.figure()
plt.plot(train_x)
    
train_x=PreData(train_x,'Mean Normaliztion',"Brand filter",low=200,high=800)
plt.figure()
plt.plot(train_x)
    
train_x=PreData(train_x,'Mean Normaliztion',"Wave filte")
plt.figure()
plt.plot(train_x)
    
test_data,batch_num=SplitData(train_x,100)
#data1=PreData(data,'Mean Normaliztion',"Wave filter",wave2=2)

"""