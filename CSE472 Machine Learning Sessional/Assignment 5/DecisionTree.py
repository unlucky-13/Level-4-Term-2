import os
import  csv
import subprocess
import pandas as pd
import numpy as np
from sklearn.tree import DecisionTreeClassifier, export_graphviz

def visualize_tree(tree, feature_names):
    with open("dt.dot", 'w') as f:
        export_graphviz(tree, out_file=f, feature_names=feature_names)

    command = ["dot", "-Tpng", "dt.dot", "-o", "dt.png"]
    try:
        subprocess.check_call(command)
    except:
        exit("Could not run dot, ie graphviz, to produce visualization")

def encode_target(df, target_column):
    #print (target_column)
    df_mod = df.copy()
    #print (df_mod[target_column])
    targets = df_mod[target_column].unique()
   # print (targets)
    map_to_int = {name: n for n, name in enumerate(targets)}
    df_mod["Target"] = df_mod[target_column].replace(map_to_int)

    return (df_mod, targets)


def get_csv(filename):
    lines = csv.reader(open(filename, "rb"))
    dataset = list(lines)
    idx=-1
    #Formating the file for Decision tree library
    with open('dataset.csv', 'w') as f:
        for data in dataset:
            strr=""
            if idx!=-1: strr+=str(idx)
            idx+=1
           # print idx
            for data1 in data:
               # print  data1
                strr+=','
                if idx!=0: strr+=str(data1)
                else: strr+=data1
            strr+="\n"
            #print strr
            #print idx
            f.write(strr)
    f.close()
    df = pd.read_csv('dataset.csv', index_col=0)
    return df

if __name__ == '__main__':
    #print("\n-- get data:")
    #df = get_csv("breast_cancer_dataset.csv") ;
    #trainData=df.ix[0:630,0: ]
    #testData=df.ix[630: ,0:8]
    #testTrueResult=df.ix[630: ,8:9]
    #print("\n-- df.head():")
    #print df.head()
    #print(df)
    #features = ["Clump Thickness","Uniformity of Cell Size","Uniformity of Cell Shape","Marginal Adhesion","Single Epithelial Cell Size","Bare Nuclei","Bland Chromatin","Normal Nucleoli"]
    #trainData, targets = encode_target(trainData, "Class")
    #print (targets)
   # print(df)
    #y = trainData["Target"]
    #X = trainData[features]
#--------------------------------------------------------------------------------------------------------------
    #dt = DecisionTreeClassifier(criterion='entropy', min_samples_split=20, random_state=99)
    #dt.fit(X, y)
    #dt.predict(testData)
    #visualize_tree(dt, features)
    #print dt.predict(testData)
    #print testTrueResult[0:]

    #dataset = get_csv("breast_cancer_dataset.csv"")


    X = []
    Y = []
    Z = []
    ZZ =[]
    lines = csv.reader(open("breast_cancer_dataset.csv", "rb"))
    dataset = list(lines)
    count=0
    for i  in  range(600):
        data = dataset[i]
        x=[]
        for i in range(len(data)-1):

            x.append(data[i])
        X.append(x)
        Y.append(data[len(data)-1])

    for i in range(600,len(dataset)):
        data = dataset[i]
        x = []
        for i in range(len(data) - 1):
                x.append(data[i])

        Z.append(x)
        ZZ.append(data[len(data) - 1])

    #print  X
    #print  Y
    #print  Z
    #print  ZZ
    Dtree =DecisionTreeClassifier(criterion='entropy', min_samples_split=20, random_state=99)
    #X = [[1,2,3],[4,5,7],[1,4,5]]
    #Y = [1,2,1]
    Dtree.fit(X,Y)
    #Z = [[1,2,3]]
    result= Dtree.predict(Z)
    correct=0.0
    incorrect=0.0
    for i in range(len(result)):
        if result[i]!=ZZ[i]: incorrect+=1.0
        else: correct+=1.0

   # print correct," ",incorrect
    print "Accuracy -> ", (correct*100)/(correct+incorrect),"%"
