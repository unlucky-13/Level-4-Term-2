import os
import  csv
import subprocess
import pandas as pd
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
import  re
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
                                Map[word] = 0
        return  Map
#---------------------------------------------------------------------------------------------------------------------
def add(filename,Map,X,Y,idx):
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
                        NewMap[word]+=1
                x=[]
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
                        NewMap[word] += 1
                x = []
                for key in NewMap:
                        x.append(NewMap[key])
                Z.append(x)
                ZZ.append(idx)
        return
if __name__=='__main__':
        filenames = ["3d_Printer","Anime","Arduino","Astronomy"]
        features = buildDictioary(filenames)
        #print len(features)
        # Now build the feature and result vectos
        X =[]
        Y = []
        Z = []
        ZZ = []
        idx=0
        for filename in filenames:
                add(filename,features,X,Y,idx)
                add1(filename,features,Z,ZZ,idx)
                idx+=1
        knn = KNeighborsClassifier()
        knn.fit(X,Y)
        testresult =   knn.predict(Z)
        count=0
        correct=0.00
        incorrect=0.00
        for x in testresult:
                #print x
                if ZZ[count]==x:
                        correct+=1
                else:
                        incorrect+=1
                count+=1
        #print  correct," ",incorrect
        print "Acuraccy -> ",(correct*100.00)/(incorrect+correct),"%"

