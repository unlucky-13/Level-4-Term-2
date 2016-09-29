import csv
import random
import  math
###########################################################################################################################
class Tree:
    def __init__(self,root):
        self.adjList = [ 0 for i in range(0,11)]
        self.attribute=root

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
def splitDataset(dataset,splitRatio):
    trainSize=len(dataset)*splitRatio
    #print trainSize
    trainData=[]
    copyDataset=list(dataset)
    while len(trainData)<trainSize:
        randomIndex=random.randrange(len(copyDataset))
        trainData.append(copyDataset.pop(randomIndex))

    return [trainData,copyDataset]

#####################################################################################################################
def entropy(examples,attributeID):
    count = [[0 for x in range(2)] for y in range(12)]
    for i in range(11):
        for j in range(2):
            count[i][j]= 0 ;
            count[i][j] = 0;


    for sample in examples:
        if sample[8]==1:
            count[sample[attributeID]][0]+=1 ;
        else:
            try:
                count[sample[attributeID]][1]+=1 ;
            except TypeError,e:
                print "error",sample
    S = 0
    for i in range(1,11):
        positiveFraction=0
        negativeFraction=0
        if count[i][0]+count[i][1]!=0:
            positiveFraction = (count[i][0]*1.00)/(count[i][0]+count[i][1]) ;
            negativeFraction =    (count[i][1]*1.00)/(count[i][0]+count[i][1]) ;

        ss= 0 ;
        if positiveFraction!=0 and negativeFraction!=0: # positive fraction zero means entropy is zero
            ss -= 	positiveFraction*math.log(positiveFraction,2)
            ss -=    negativeFraction*math.log(negativeFraction,2)
            fraction = ((count[i][0]+count[i][1])*1.00)/len(examples) ;
            S += (ss*fraction)

    return S

############################################################################################################################
def informationGain(dataset,attribute):
    positive = 0
    negative = 0
    for x in dataset:
        if x[8]==1:
            positive+=1
        else:
            negative+=1

    #print positive," ",negative
    positiveFraction=  (positive*1.00)/(positive+negative)
    negativeFraction = (negative*1.00)/(positive+negative)
    #	print positiveFraction," ",negativeFraction
    #	print math.log(positiveFraction,2)," ",math.log(negativeFraction,2)
    totalEntropy =  -positiveFraction*math.log(positiveFraction,2)-negativeFraction*math.log(negativeFraction,2)
    #	print "total ",totalEntropy
    return  totalEntropy - entropy(dataset,attribute)
##################################################################################################################

def plurality_value(dataset):
    yes=0
    no=0
    for x in dataset:
        if x[8]==0:
            yes+=1
        else:
            no+=1

    if yes>no:
        return 1
    else:
        return 0
######################################################################################################################
def same_classification(dataset):

    ret=1
    for x in dataset:
        if x[8]!=dataset[0][8]:
            return 0
    return 1
#################################################################################################################
def Importance(examples,attributes):

    returnAtrribute=-1
    maxInformationGain=0
    for attibuteVal in attributes:
        informationGainVal = informationGain(examples,attibuteVal)
        if informationGainVal>maxInformationGain:
            returnAtrribute=attibuteVal
            maxInformationGain=informationGainVal
    return  returnAtrribute
#####################################################################################################################

def decisionTreeLearning(examples,attributes,parrent_examples,tree,parent): # returns a tree
    if len(examples)==0:
        #print "example shesh"

        ret=plurality_value(parrent_examples)-2
        tree = Tree(ret)
        return  tree
    elif same_classification(examples):
        #print "same classification"
        ret = examples[0][8]-2 # returing the classification -2 is No -1 is Yes
        tree = Tree(ret)
        return  tree
    elif len(attributes)==0:
        #print "attribute shesh"
        ret =  plurality_value(parrent_examples)-2
        tree = Tree(ret)
        return tree
    else:
        keyAttribute = Importance(examples,attributes)
        tree = Tree(keyAttribute) ;
        att = list(attributes)
        att.remove(keyAttribute)
        for i in range(1,11):
            exa = []
            for x in examples:
                if x[keyAttribute]==i:
                    exa.append(x)
           # print i,"->" ,exa
            childTree = decisionTreeLearning(exa,att,examples,tree,keyAttribute)
            #print keyAttribute ," value -> ",i," branch ",at
           # print keyAttribute, " has parent ->", parent, " for value ->",i," next ",at
            tree.adjList[i]=childTree
        return tree
###################################################################################################################
def singleRun():
    tree = [[ [0 for x in range(11)] for y in range(11)] for z in range(11)]
    filename="assignment1_data_set.csv"
    dataset = loadCsv(filename)
    #print "loaded datafile",filename," with ",len(dataset)," rows"

    [trainData,testData]= splitDataset(dataset,0.9)
    attributes=[]
    for i in range(0,8):
        attributes.append(i)
#    print informationGain(dataset,1)
    mainTree=decisionTreeLearning(trainData,attributes,trainData,tree,0)
   # print root



    ########################################################################################################################
    truePositive=0
    falsePositive=0
    trueNegative=0
    falseNegative=0
    for data in trainData:
        currrentTree = mainTree
        while currrentTree.attribute>=0:
            currrentTree = currrentTree.adjList[data[currrentTree.attribute]]


        v = currrentTree.attribute
        if v+2==data[8]:
            if data[8]==1:
                truePositive+=1
            else:
                falseNegative+=1
        else:
            #print "Not matched"
            if data[8]==1:
                trueNegative+=1
            else:
                falsePositive+=1
  #  print "on training data"
    #print  matched," ",notmatch
   # print trueNegative," ",falsePositive
    recall1 = (truePositive*(1.00))/(truePositive+falseNegative)
    #print "Recall ->" ,(truePositive*(1.00))/(truePositive+falseNegative)
    precession1 = (truePositive*1.00)/(truePositive+falsePositive)
   # print "Precession ->", (truePositive*1.00)/(truePositive+falsePositive)
    accuracy1 = ((truePositive+falseNegative)*(1.00))/(truePositive+falseNegative+trueNegative+falsePositive)
  #  print "Accuracy ->",((truePositive+falseNegative)*(1.00))/(truePositive+falseNegative+trueNegative+falsePositive)

    truePositive=0
    falsePositive=0
    trueNegative=0
    falseNegative=0

    for data in testData:
        currrentTree = mainTree
        while currrentTree.attribute >= 0:
            currrentTree = currrentTree.adjList[data[currrentTree.attribute]]

        v = currrentTree.attribute
        if v + 2 == data[8]:
            if data[8] == 1:
                truePositive += 1
            else:
                falseNegative += 1
        else:
            # print "Not matched"
            if data[8] == 1:
                trueNegative += 1
            else:
                falsePositive += 1
  #  print "on test data"
    # print  matched," ",notmatch
   # print trueNegative, " ", falsePositive
    recall2 = (truePositive * (1.00)) / (truePositive + falseNegative)
    # print "Recall ->" ,(truePositive*(1.00))/(truePositive+falseNegative)
    precession2 = (truePositive * 1.00) / (truePositive + falsePositive)
    # print "Precession ->", (truePositive*1.00)/(truePositive+falsePositive)
    accuracy2 = ((truePositive + falseNegative) * (1.00)) / (truePositive + falseNegative + trueNegative + falsePositive)
    #  print "Accuracy ->",((truePositive+falseNegative)*(1.00))/(truePositive+falseNegative+trueNegative+falsePositive)

    return [recall1,precession1,accuracy1,recall2,precession2,accuracy2]
########################################################################################################################

if __name__ == '__main__':

    recall1=recall2=0.00
    precession1=precession2=0.00
    accuracy1=accuracy2=0.00

    for i in range(0,100):
        [R1,P1,A1,R2,P2,A2] = singleRun()
      #  print A1," ",A2
        recall1+=R1
        precession1+=P1
        accuracy1+=A1

        recall2+=R2 ;
        precession2+=P2 ;
        accuracy2+=A2

    print "Train : Recall", recall1/100.00," Precession -> ",precession1/100,"accuracy ->",accuracy1/100.00
    print "Test : Recall", recall2 / 100.00, " Precession -> ", precession2 / 100, "accuracy ->", accuracy2 / 100.00

