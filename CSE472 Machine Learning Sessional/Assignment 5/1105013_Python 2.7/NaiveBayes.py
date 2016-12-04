from  sklearn.naive_bayes import  BernoulliNB
import numpy as np
import  re
def isValid(word):
    if len(word)==1: return  False
    if re.search('^-?[0-9]+$', word): return False
    return True

def buildDictioary(filenames):
        Map={}
        for filename in filenames:
                #print filename
                lines = open("Data/Training/"+filename+".xml").read().splitlines()
                count=0
                for line in lines:
                        #print  line
                        if count>100: break
                        else : count+=1
                        words = re.sub("[^\w]", " ", line).split()
                        for word in words:
                                word = word.lower()
                                Map[word]=0

                lines = open("Data/Test/" + filename + ".xml").read().splitlines()
                count = 0
                for line in lines:
                        # print  line
                        if count > 100:
                                break
                        else:
                                count += 1
                        words = re.sub("[^\w]", " ", line).split()
                        for word in words:
                                word = word.lower()
                                Map[word] = 0
        return  Map
#---------------------------------------------------------------------------------------------------------------------
def add(filename,Map,X,Y,idx):
        x=[]
        lines = open("Data/Training/" + filename + ".xml").read().splitlines()
        count=0
        NewMap = Map
        for line in lines:
                # print  line
                if count > 100:
                        break
                count += 1

                words = re.sub("[^\w]", " ", line).split()
                for word in words:
                        word  = word.lower()
                        if isValid(word) and NewMap[word]!=-1:
                            NewMap[word]+=1

        for key in NewMap:
            x.append(NewMap[key])
        X.append(x)
        Y.append(idx)
        return
#---------------------------------------------------------------------------------------------------------------------------
def add1(filename, Map,Z,ZZ,idx):
        lines = open("Data/Test/" + filename + ".xml").read().splitlines()
        count = 0
        NewMap = Map
        for line in lines:
                # print  line
                if count > 100:
                        break
                count += 1

                words = re.sub("[^\w]", " ", line).split()
                for word in words:
                        word = word.lower()
                        if isValid(word) and NewMap[word]!=-1:
                            NewMap[word] += 1
                x = []
                for key in NewMap:
                        x.append(NewMap[key])
                Z.append(x)
                ZZ.append(idx)

        return
if __name__=='__main__':
    #X = np.random.randint(10,size=(10,10))
    #print X
    filenames = ["3d_Printer", "Anime", "Arduino", "Astronomy"]
    excludeFiles = ["html_tag_list.txt", "Words.txt"]
    excludeWords = []
    for file in excludeFiles:
       lines = open(file).read().splitlines()
       for line in lines:
         words = re.sub("[^\w]", " ", line).split()
         for word in words:
            excludeWords.append(word)

    filenames = ["3d_Printer", "Anime", "Arduino", "Astronomy"]
    features = buildDictioary(filenames)
    for word in excludeWords:
        features[word]=-1

    X = []
    Y = []
    Z = []
    ZZ =[]
    idx = 0
    for filename in filenames:
        add(filename, features, X, Y, idx)
        add1(filename, features, Z,ZZ,idx)
        idx += 1
    knn = BernoulliNB()
    knn.fit(X, Y)
    testresult = knn.predict(Z)
    count = 0
    correct = 0.00
    incorrect = 0.00
    count=0
    for x in testresult:
        if ZZ[count] == x:
            correct += 1
        else:
            incorrect += 1
        count+=1
    # print  correct," ",incorrect
    print (correct * 100.00) / (incorrect + correct),"%"