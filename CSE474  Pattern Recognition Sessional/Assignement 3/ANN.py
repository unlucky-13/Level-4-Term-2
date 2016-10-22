import  csv
import  random
import  math

#------------------------------------------------------------------------------------------------------------------
def loadCsv(filename):
    lines = csv.reader(open(filename, "rb"))
    dataset = list(lines)
    #print dataset[0]
    data = []
    for i in range(0,len(dataset)):
        x = Vector(len(dataset[i]),1)
        y = Vector(len(dataset[i]),1)
        #print len(dataset[i])
        # x is the input
        #y is the expected output
        x.Matrix[0][0]=1
        y.Matrix[0][0]=0
        #print dataset[i]
        for j in range(1,len(dataset[i])):
            if j==1:
                if dataset[i][j-1]=='M':
                    x.Matrix[j][0] = 0.00
                elif dataset[j][0]=='F':
                    x.Matrix[j][0] = 1.00
                else:
                    x.Matrix[j][0] = 2.00
            else:
                x.Matrix[j][0] = float(dataset[i][j-1])

            if j==len(dataset[i])-1:
                y.Matrix[j][0] = float(dataset[i][j])
            else: y.Matrix[j][0]=0.00
        data.append([x,y])
    return data
#-------------------------------------------------------------------------------------------------------------
class Vector:
    def __init__(self,row,col):
        self.row=row
        self.col =col
        self.Matrix = [ [1.00 for j in range(col)] for i in range(row)]
        for i in range(0,row):
            for j in range(0,col):
                self.Matrix[i][j]=random.random()
#------------------------------------------------------------------------------------------------------------
def activationfunc(vec):
    for i in range(vec.row):
        for j in range(vec.col):
            vec.Matrix[i][j] = 1.00/(1.00-math.exp(-vec.Matrix[i][j]))
    return vec
#-----------------------------------------------------------------------------------------------------------
def dot(p,q):
    #print p.Matrix
    #print q.Matrix
    if p.col!=q.row :
        print "Dimension error"
        return
    r = Vector(p.row,q.col)
    #print "Multiplying"
    #print "P -> ",p.Matrix
    #print "Q ->",q.Matrix
    for i in range(0,p.row):
        for j in range(0,q.col):
            value=0.00
            for k in range(0,p.col):
                value+=(p.Matrix[i][k]*q.Matrix[k][j])
            r.Matrix[i][j]=value
    #print "Result is ->",r.Matrix
    return r
#-------------------------------------------------------------------------------------------------------------
def subtract(p,q):
    if p.row !=q.row or p.col!=q.col:
        print "Dimension error"
        return
    r = Vector(p.row,p.col)
    for i in range(0,p.row):
        for j in range(0,p.col):
            r.Matrix[i][j] = p.Matrix[i][j]-q.Matrix[i][j]
    return r
#-------------------------------------------------------------------------------------------------------------
def add(p,q):
    if p.row !=q.row or p.col!=q.col:
        print "Dimension error"
        return
    r = Vector(p.row,p.col)
    for i in range(0,p.row):
        for j in range(0,p.col):
            r.Matrix[i][j] = p.Matrix[i][j]+q.Matrix[i][j]
    return r
#-------------------------------------------------------------------------------------------------------------
def Transpose(p):
    r = Vector(p.col,p.row)
    for i in range(p.col):
        for j in range(p.row):
                r.Matrix[i][j]=p.Matrix[j][i]


    return  r
#-------------------------------------------------------------------------------------------------------------
class Network:
    layers =0
    No = 0
    weightVecs = []
    a = []
    def __init__(self,layers,No):
        self.layers= layers
        self.No = No+1
        for i in range(layers-1):
            self.weightVecs.append(Vector(No+1,No+1))
        self.a =  [[]for i in range(No)]

    def forwardPropagation(self,input):
         #print type(input)
         #print len(input)," ",self.No
         if input.row!=self.No:
             print "Input No doesn't Match!!!!"
             return
         else:
            self.a[0] = input
            #print self.a[0].Matrix
            for i in range(1,self.layers):
                    self.a[i] = dot(self.weightVecs[i-1],self.a[i-1]) # apply activation function here
                    self.a[i] = activationfunc(self.a[i])
                    self.a[i].Matrix[0][0]= 1 # this always should be 1 bias value


    def backPropagation(self,output):
        if output.row!=self.No:
            print "Output No doesn't Match"
            return
        else:
            learning_rate = -0.5
            #print output.Matrix
            error=[]
            last = subtract(self.a[self.layers-1],output)
            error.append(last)
            for i in range(self.layers-2,0,-1):
                A = Vector(self.a[i].row,1)
                for I in range(A.row):
                        A.Matrix[I][0] = last.Matrix[I][0]*self.a[i].Matrix[I][0]*(1.00-self.a[i].Matrix[I][0])

                # Make the weighVecs tranpos
                transpose=Transpose(self.weightVecs[i])
                A = dot(transpose,A)
                last = A
                error.append(last)

            #for i in range(len(error)):
                #print error[i].Matrix
	  #  A = Vector(self.a[i].row,1)

	    for i in range(self.layers-2,-1,-1):
                transpose=Transpose(self.a[i])
                self.weightVecs[i] = add(self.weightVecs[i],dot(error[i],transpose))
               # print self.weightVecs[i].Matrix
#--------------------------------------------------------------------------------------------------------------
if __name__=='__main__':
    TrainDataSet = loadCsv("abalone.data.txt") ;
    KNN = Network(3,8)
    for i in range(len(TrainDataSet)):
        KNN.forwardPropagation(TrainDataSet[1][0])
        KNN.backPropagation(TrainDataSet[1][1])
    for i in range(0,2):
        print KNN.weightVecs[i].Matrix
