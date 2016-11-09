import csv
import random
import  math

########################################################################################################################
def loadCsv(filename):
    lines = csv.reader(open(filename, "rb"))
    dataset = list(lines)
    #print dataset[0]
    for i in range(0,len(dataset)):
        try:
            dataset[i] = [int (x) for x in dataset[i]]
        except ValueError,e:
            print "error",e,"on line ",i
    return dataset
#####################################################################################################################

if __name__=='__main__':
    
    tree = [[ [0 for x in range(11)] for y in range(11)] for z in range(11)]
    filename="assignment1_data_set.csv"
    Nsubset=10
    dataset = loadCsv(filename)
    data_sub_set=[[] for x in range(Nsubset+1)]
    cur=0
    sub_set_size = len(dataset)/Nsubset
    curSubSet=0
   # print sub_set_size
    for data in dataset:
    #    print cur
        data_sub_set[curSubSet].append(data)
        cur+=1
        cur%=sub_set_size
        if cur==0: curSubSet+=1
    #print len(data_sub_set[0])," ",len(data_sub_set[1])    
        