from loadFile import *
from Vector import *
import  csv
import  random
import  math

#-------------------------------------------------------------------------------------------------------------
class Network:
    def __init__(self,_inputLayers,_outputLayers,_totalLayers,_NeuronsPerLayer,_learning_rate):
        self.inputLayers=_inputLayers
        self.outputLayers=_outputLayers
        self.totalLayer = _totalLayers
        self.NeronPerLayer = _NeuronsPerLayer
        self.weightVectors = []
        self.learning_rate = _learning_rate
        # initialize the weight vectors randomly
        # the first weight vector in between the input layer and the hidden layer
        vec = Vector(_inputLayers,_NeuronsPerLayer)
        self.weightVectors.append(vec)
        # for other hidden layers
        for i in range(1,_totalLayers-2):
            vec = Vector(_NeuronsPerLayer,_NeuronsPerLayer)
            self.weightVectors.append(vec)

        # the weight vec in the last hidden layer and the output layer
        vec = Vector(_NeuronsPerLayer,_outputLayers)
        self.weightVectors.append(vec)
        #print len(self.weightVectors)
        self.E = []
        for i in range(len(self.weightVectors)):
            vec = Vector(self.weightVectors[i].row,self.weightVectors[i].col)
            for I in range(0,vec.row):
                for J in range(0,vec.col):
                    vec.Matrix[I][J]=0.00

            self.E.append(vec)

    def forwardPropagation(self,input):
         if input.row!=self.weightVectors[0].row:
             print "Input No doesn't Match!!!!"
             return
         else:
            self.a = []
            self.a.append(input)
            last = input
            #print self.a[0].Matrix
            for i in range(1,self.totalLayer):
                    vec = Transpose(self.weightVectors[i-1])
                    vec = dot(vec,last)
                    vec= activationfunc(vec)
                    last = vec
                    last.Matrix[0][0]=1.00
                    self.a.append(last)

            #print "SIZE ", len(self.a)
            return last

    def backPropagation(self,output):
        if output.row!=self.weightVectors[self.totalLayer-2].col:
            print output.row," ",self.weightVectors[self.totalLayer-2].row
            print "Output No doesn't Match"
            return
        else:


            #print output.Matrix
            error=[]
#            print self.a[self.totalLayer-1].Matrix
 #           print output.Matrix
            last = subtract(self.a[self.totalLayer-1],output)
            error.append(last)
            for i in range(self.totalLayer-2,0,-1):
                derivative  = Vector(self.a[i+1].row,self.a[i+1].col)
                for I in range(derivative.row):
                    for J in range(derivative.col):
                        derivative.Matrix[I][J] = last.Matrix[I][J]*derivative.Matrix[I][J]*(1.00-derivative.Matrix[I][J])

                last = dot(self.weightVectors[i],derivative)
                error.append(last)

              #  print "Error Matrices"
               # for  i in range(len(error)):
                #    print error[i].Matrix
                #return
               # print self.totalLayer-1," ",len(self.E)
            for i in range(self.totalLayer-1):
                errorTranspose = Transpose(error[self.totalLayer-2-i]) ;
                self.E[i] = add(self.E[i],multiply(self.learning_rate,dot(self.a[i],errorTranspose)))
#--------------------------------------------------------------------------------------------------------------
    def finishBackprop(self):
       # print "Error sumation ->"
        #for  i in range(len(self.E)):
         #   print self.E[i].Matrix

        for i in range(len(self.weightVectors)):
            self.weightVectors[i] = add(self.weightVectors[i],self.E[i])

        # Now clean up E

        for i in range(len(self.E)):
            for I in range(self.E[i].row):
                for J in range(self.E[i].col):
                    self.E[i].Matrix[I][J]=0.00
#--------------------------------------------------------------------------------------------------------------------------
def activationfunc(V):
    for i in range(V.row):
        for j in range(V.col):
            try:
                V.Matrix[i][j] = 1.00/(1.00-math.exp(-V.Matrix[i][j]))
            except Exception:
                    x = 1
                    #print ""
                    #print "exception caught"," ",-V.Matrix[i][j]
    return V
#------------------------------------------------------------------------------------------------------------



























































































