import  csv
import  random
import  math
def loadCsv(filename):
    lines = csv.reader(open(filename, "rb"))
    dataset = list(lines)
    #print dataset[0]
    for i in range(0,len(dataset)):
        try:
            dataset[i] = [ x for x in dataset[i]]
        except ValueError,e:
            print "error",e,"on line ",i
    return dataset

def splitData(copyDataset):
    traindata=[]
    testdata=[]

    while len(traindata)<40:
        randomIndex = random.randrange(len(copyDataset))
        traindata.append(copyDataset.pop(randomIndex))

    while len(testdata) <10:
        randomIndex = random.randrange(len(copyDataset))
        testdata.append(copyDataset.pop(randomIndex))

    return [traindata,testdata]

def calculate_mean_sd(dataset):
    count = [0.00  for x in range(4)]
    for data in dataset:
        for i in range(4):
            count[i] = count[i]+float(data[i])

    mean=[0.00  for x in range(4)]

    for i in range(4):
        mean[i] = count[i]/len(dataset)

    #print mean

    sd = [0.00 for x in range(4)]
    for data in dataset:
        for i in range(4):
            sd[i] = sd[i]+(mean[i]-float(data[i]))*(mean[i]-float(data[i]))

    for i in range(4):
        sd[i] = sd[i]/len(dataset)
        sd[i] = math.sqrt(sd[i])

    #print sd

    return [mean,sd]

def P_x_c(mean,sd,value):

    poweer = -((value-mean)*(value-mean))/(2.00*sd*sd)
    probabilty = (1.00/math.sqrt(2.00*sd*sd*math.pi))*math.exp(poweer)
    return  probabilty

def naive_bayes(testdatavector,mean1,sd1,mean2,sd2,mean3,sd3):
    #print  testdatavector
    max_propabilty=0.00
    class_type=-1
    for i in range(3): #for every class fiding the probabilty
        probabilty = 1.00
        for j in range(4):
            #print testdatavector[j]
            if i==0:
                mean = mean1[j]
                sd = sd1[j]
            elif i==1:
                mean = mean2[j]
                sd = sd2[j]
            else:
                mean = mean3[j]
                sd=sd3[j]

           # print type(sd)," ",type(mean)," ",type(testdatavector)
            probabilty = probabilty*P_x_c(float(sd),float(mean),float(testdatavector[j]))

        if probabilty>max_propabilty:
            class_type=i
            max_propabilty=probabilty
    #print  max_propabilty," ",class_type
    return  class_type

if __name__ == '__main__':
    filename = "iris.data"
    dataset = loadCsv(filename) ;

    testdata1=traindata1 = []
    testdata2 = traindata2 = []
    testdata3 = traindata3 = []
    copydata = []

    for i in range(50):
        copydata.append(dataset[i])
    [traindata1,testdata1] = splitData(copydata);
    copydata=[]
    for i in range(50,100):
        copydata.append(dataset[i]);
    [traindata2, testdata2] = splitData(copydata);
    copydata = []
    for i in range(100,150):
        copydata.append(dataset[i]);

    [traindata3, testdata3] = splitData(copydata);

    [mean1,sd1] = calculate_mean_sd(traindata1)
    [mean2,sd2] = calculate_mean_sd(traindata2)
    [mean3,sd3] = calculate_mean_sd(traindata3)


    wrong=0.00
    right=0.00
    for data in testdata1:
        class_type = naive_bayes(data,mean1,sd1,mean2,sd2,mean3,sd3)
        if class_type==0:
            right+=1
        else:
            wrong+=1

    for data in testdata2:
        class_type = naive_bayes(data,mean1,sd1,mean2,sd2,mean3,sd3)
        if class_type==1:
            right+=1
        else:
            wrong+=1

    for data in testdata3:
        class_type = naive_bayes(data,mean1,sd1,mean2,sd2,mean3,sd3)
        if class_type==2:
            right+=1
        else:
            wrong+=1

    print "Wrong ->",wrong
    print "Right ->", right
    print "Accuracy ->" ,right/(wrong+right)