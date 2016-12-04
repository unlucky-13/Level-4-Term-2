from PIL import  Image
import  numpy as np
import  math
def C(m,n,test,ref):
    #if arr[m][n]!=-1.00:
        #print "Return"
     #   return arr[m][n]
    if m+len(ref)>len(test) or n+len(ref)>len(test) or m<0 or n<0:
        return -100000000

    nominator=0.0
    denominator1=0.0
    denominator2 = 0.0
    for i in range(len(ref)):
        for j in range(len(ref[i])):
                t = float(test[i+m][j+n])
                r = float(ref[i][j])
                #print t," -> ",r
                nominator+= t*r
                denominator1+= t*t
                denominator2+=r*r
    #arr[m][n]=nominator/math.sqrt(denominator1*denominator2)
    #print nominator," ",math.sqrt(denominator1*denominator2)
    return float(nominator)/float(math.sqrt(denominator1*denominator2))
#---------------------------------------------------------------------------------------------------------
def getImage(name):
    im = Image.open(name)
    p = np.array(im)
    return  p
#------------------------------------------------------------------------------------------------------------------------
if __name__=='__main__':

    test = getImage("test.bmp")
    ref = getImage("ref2.bmp") ;
    M = len(test)
    N = len(test[0])
    m = len(ref)
    n = len(ref[0])

    I=0
    J=0
    maxi=0.00
    for i in range(M-m):
        #for j in range(N-n):
            j  = i
            c = C(i,i,test,ref)
            if maxi<c:
                [I,J]=[i,j]
                maxi=c
                print I," ",J," ",maxi
       # print i

    #print C(385,385,test,ref)


    #test = np.array([[ test[i+m][j+n] for j in range(len(ref[0]))] for i in range(len(ref))])
    #RT1 = np.multiply(test,ref)
    #RT2 = np.multiply(test,test)
    #RT3 = np.multiply(ref,ref)
    #nominator=0.0
    #denominator1=0.0
    #denominator2 = 0.0
    #RT1 = RT1.sum(axis=0)
    #RT2 = RT2.sum(axis=0)
    #RT3 = RT3.sum(axis=0)
    #print RT1," ",RT2," ",RT3
    #for v in RT1:
     #   nominator+=v
    #for v in RT2:
     #   denominator1+=v
    #for v in RT3:
     #   denominator2+=v

    #return nominator/math.sqrt(denominator1*denominator2)