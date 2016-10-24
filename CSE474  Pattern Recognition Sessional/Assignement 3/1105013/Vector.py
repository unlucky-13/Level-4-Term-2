import  csv
import  random
import  math
#-------------------------------------------------------------------------------------------------------------
class Vector:
    def __init__(self,row,col):
        self.row=row
        self.col =col
        self.Matrix = [ [1.00 for j in range(col)] for i in range(row)]
        for i in range(0,row):
            for j in range(0,col):
                self.Matrix[i][j]=random.random()
#-----------------------------------------------------------------------------------------------------------
def dot(p,q):
    #print p.row," ",p.col
   # print q.col," ",q.col
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

def multiply(scale,vec):
    for i in range(vec.row):
        for j in range(vec.col):
            vec.Matrix[i][j]*=scale


    return vec