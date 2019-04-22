
# -*- coding: utf-8 -*-

import numpy as np
import pywt
import pywt.data
from scipy import signal
import scipy.io as sio
import os
import tensorflow as tf
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'     #消除tf avxx error
os.environ['CUDA_VISIBLE_DEVICES'] = '0' 


print("ni hao wyk ,np.version : ",np.__version__)

import time
import h5py

# 设置 GPU 按需增长
config = tf.ConfigProto()
config.gpu_options.allow_growth = True


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
time_step_set=128  
fin_signal_feature_predict=[]
fin_distance_predict=[]

def read_data(filepath,batch_size='4096',pre_mode='no',lvbo_mode='no',lvbo1=8,low=0,high=0,wave1='sym5',wave2=3):
    print(filepath)
    filepathaa1=os.path.abspath(filepath)
    file_parfile=os.path.dirname(filepath)
    with open(file_parfile+'//epoch.txt','w') as f:
        f.write(str(0)+' / '+str(0))
    global volt_data2
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

    global length

    global batch_size_set
    batch_size_set=int(batch_size)
    length=int(volt_data2.shape[0]/batch_size_set)
    
    global centers
    filepath=file_parfile+'\\fin_km_centers.h5'
    centers = h5py.File(filepath,'r')  
    centers=np.array(centers['fin_km_centers'])

    return length


def load_model(filepath,modelfile):
    print(filepath)
    #filepathaa1=os.path.abspath(filepath)
    file_parfile=os.path.dirname(filepath)
    with open(file_parfile+'//epoch.txt','w') as f:
        f.write(str(0)+' / '+str(0))

    modelfile=modelfile
    model_parfile=os.path.dirname(modelfile)

    config = tf.ConfigProto()
    config.gpu_options.allow_growth = True
    global sess
    sess= tf.Session(config=config)

    saver=tf.train.import_meta_graph(modelfile)
    graph=tf.get_default_graph()
    #tesor_name_list=[tensor.name for tensor in graph.as_graph_def().node]

    global X
    global Y
    global keep_prob
    global lae_feature_out
    X=graph.get_tensor_by_name('X_Y_input/x_input:0')

    Y=graph.get_tensor_by_name('X_Y_input/y_input:0')

    keep_prob=graph.get_tensor_by_name('keep_prob/keep_prob:0')

    lae_feature_out=graph.get_tensor_by_name('lae_feature/add:0')
    module_file = tf.train.latest_checkpoint(model_parfile)
    saver.restore(sess, module_file)


def process_data(filepath,number):
    file_parfile=os.path.dirname(filepath)
    number=int(number)
    global sess
    global volt_data2
    global X
    global Y
    global keep_prob
    global lae_feature_out
    global centers
    global length
    global batch_size_set
    time1=time.time()

    test_x=[]
    for j in range(batch_size_set):
        test_x.append(volt_data2[(number*batch_size_set+j):(number*batch_size_set+j+time_step_set)])
    test_x=np.asarray(test_x)
    time2=time.time()
    
    test_x=(test_x - test_x.mean())/test_x.std()
    
    test_x = np.reshape(test_x,[np.shape(test_x)[0],np.shape(test_x)[1],1])
    time3=time.time() 
    
    tmp_fin_output=sess.run(lae_feature_out,feed_dict={X:test_x,keep_prob: 1.0}) 
    time4=time.time()
    #fin_signal_feature_predict.append(tmp_fin_output)   
    with open(file_parfile+'//epoch.txt','w') as f:
        f.write(str(number)+' / '+str(length))     

    distance_wyk=np.zeros(shape=(len(tmp_fin_output),len(centers)))
    for i in range(len(tmp_fin_output)):
        distance_wyk[i]=np.square(tmp_fin_output[i]-centers).sum(axis=1)
    final_distance_wyk=distance_wyk.max(axis=1) 
    
    final_distance=final_distance_wyk.tolist()
    
    fin_distance_predict.extend(final_distance)
    
    time5=time.time()
    print(time2-time1)
    print(time3-time2)
    print(time4-time3)
    print(time5-time4)
    print(time3-time1)

    return final_distance


        
def data_save(data_save_path):
    data_save_path=data_save_path

    #fin_signal_feature_predict=np.asarray(fin_signal_feature_predict)
    #fin_signal_feature_predict_size=fin_signal_feature_predict.shape
    #fin_signal_feature_predict=np.reshape(fin_signal_feature_predict, (fin_signal_feature_predict_size[0] * fin_signal_feature_predict_size[1], fin_signal_feature_predict_size[2] ))
    #print ("-------------fin_signal_feature_predict is finised----------------------")   
    #print("total_time:%s s"%(time.time()-start_time)) 

    #final_distance=np.zeros(shape=(len(fin_signal_feature_predict),len(centers)))
    #for i in range(len(fin_signal_feature_predict)):
        #final_distance[i]=np.square(fin_signal_feature_predict[i]-centers).sum(axis=1)

    #np.save(data_save_path+'\\distance_wyk_nograph_test4.npy',final_distance) 
    #distance_wyk=final_distance.max(axis=1)
    np.save(data_save_path+'\\final_distance_wyk_nograph_test4_1340.npy',fin_distance_predict)

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


"""
filepath=r'D:\data_model\4.mat'
modelfile=r'D:\data_model\kmeans_model_save_4\modle.ckpt-150.meta'
data_save_path=r'D:\data_model'
number=400
batch_size=40000

time1=time.time()
length_wyk=read_data(filepath,batch_size_set)
time2=time.time()
load_model(filepath,modelfile)
#process_data(filepath,number)
time3=time.time()


test_x=[]
for j in range(batch_size_set):
    test_x.append(volt_data2[(number*batch_size_set+j):(number*batch_size_set+j+time_step_set)])
test_x=np.asarray(test_x)
time4=time.time()     
test_x=(test_x - test_x.mean())/test_x.std()
time5=time.time()    
test_x = np.reshape(test_x,[np.shape(test_x)[0],np.shape(test_x)[1],1])

        
tmp_fin_output=sess.run(lae_feature_out,feed_dict={X:test_x,keep_prob: 1.0}) 

time6=time.time()

print(time2-time1)
print(time3-time2)
print(time4-time3)
print(time5-time4)
print(time6-time5)

"""




















