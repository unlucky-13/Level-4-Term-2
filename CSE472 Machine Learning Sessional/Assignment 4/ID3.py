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
def splitDataset(dataset,splitRatio): # here some changes for ada boosting
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

def decisionTreeLearning(examples,attributes,parrent_examples,tree,parent,depth): # returns a tree
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
    elif len(attributes)==0 or depth==0:
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
            childTree = decisionTreeLearning(exa,att,examples,tree,keyAttribute,depth-1)
            #print keyAttribute ," value -> ",i," branch ",at
           # print keyAttribute, " has parent ->", parent, " for value ->",i," next ",at
            tree.adjList[i]=childTree
        return tree
###################################################################################################################
def Hypothesis(tree,data): # returns 1 if the hyppthesis by the tree is correct 0 otherwise
    currrentTree = tree
    while currrentTree.attribute >= 0:
        currrentTree = currrentTree.adjList[data[currrentTree.attribute]]
    v = currrentTree.attribute
    if v + 2 == data[8]:
        match = 1.00
    else:
        match = 0.00
    return match

def AdaptiveBoosting(dataset,k):

    bostedTrees = []
    betaValues = []
    [trainData, testData] = splitDataset(dataset, 0.6)

    while k>0:
        #print k," -> Boosting"
        tree = [[ [0 for x in range(11)] for y in range(11)] for z in range(11)]
        # Now pick the actual train Data dataset by weights
        actualTrainDataset  = []
        copyDataset = []
        for data in trainData:
            copyDataset.append(data)
        #print len(trainData)
        while len(actualTrainDataset)<200:
            #print len(actualTrainDataset)
            randomVal = random.uniform(0, 1.00)
            scale = 0.0
            for data in copyDataset:
                scale += data[9]
            #print scale
            total=0
            for i in range(len(copyDataset)) :
                total+=(copyDataset[i][9]/scale)
                if total<=randomVal:
                    actualTrainDataset.append(copyDataset[i])
                    #copyDataset.pop(i)
                    break
        attributes=[]
        #print  len(trainData)
        for i in range(0,8):
            attributes.append(i)
        #    print informationGain(dataset,1)
        mainTree=decisionTreeLearning(actualTrainDataset,attributes,actualTrainDataset,tree,0,1)
        error=0.00
        scale=0.00
        for data in trainData:
            scale+=data[9]
        #print  scale
        for data in trainData:
            error+=Hypothesis(mainTree,data)*(data[9]/scale)


       # print  k, "->",error
        beta = error / (1.00 - error)
        #print  beta
        # print root
        ########################################################################################################################

        if error>0.5:
            k=0
            #print "Boosting ended"
            continue
        bostedTrees.append(mainTree)
        betaValues.append(beta)
        nexDataSet = []
        for data in trainData:
            hypothesis = Hypothesis(mainTree,data)
            if hypothesis==1:
                data[9] = data[9]*pow(beta,1) # correctly predicted make the weight less
            else:
                data[9] = data[9] *pow(beta,0)
            nexDataSet.append(data)
        k-=1
        #print len(nexDataSet)," ",len(trainData)
        trainData = nexDataSet
########################################################################################################################
#!!!!!!!!!!!!!!!!!!!!!!!!!!OUTPUT STAGE
    accuracy=0.00
    for data in testData:
        yes=0
        no=0
        for i  in range(len(bostedTrees)):
            result = Hypothesis(bostedTrees[i], data)
            if result==1.00:
                if betaValues[i]!=0:
                    yes+=math.log10(1.00/betaValues[i])
            else:
                if betaValues[i]!=0:
                    no+=math.log10(1.00/betaValues[i])

        if yes>no:ans=1.00
        else:ans=0.00

        if ans==data[8]:
            accuracy+=1.00
   # print  accuracy," ",len(testData)
    return accuracy/(len(testData))

if __name__ == '__main__':

    filename = "assignment1_data_set.csv"
    dataset = loadCsv(filename)
    # print "loaded datafile",filename," with ",len(dataset)," rows"
    for data in dataset:
        data.append(1.000)

    K = [5,10,20,30]
    iterations=100
    for k in K:
        accuracy=0.00
        for i in range(iterations): # adding weight as the last value
            for data in dataset:
                data[9]=1.00
            accuracy += AdaptiveBoosting(dataset,k)
        print k," - >>>",accuracy