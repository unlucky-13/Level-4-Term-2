from PIL import  Image
import  numpy as np
import  math
def C(m,n,test,ref):

    nominator   =  0.0
    denominator1=  0.0
    denominator2 = 0.0
    for i in range(len(ref)):
        for j in range(len(ref[i])):
                if i+m>=len(test) or j+n>=len(test[i+m]): t= 0
                else :  t = float(test[i+m][j+n])
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
def LogarithmicSearch(cx,cy,d,test,ref):
    if d==0:
        return [cx,cy]

    sign = [-1,0,1]
    maxi=0
    [I,J] = [-1,-1]
    for s1 in sign:
        for s2 in sign:
            c = C(s1*d+cx,s2*d+cy,test,ref)
            if c>maxi:
                maxi=c
                [I,J] = [s1*d+cx,s2*d+cy]
    print [I,J]," -> ",maxi
    return LogarithmicSearch(I,J,d/2,test,ref)
#------------------------------------------------------------------------------------------------------------------------
if __name__=='__main__':

    test = getImage("test.bmp")
    ref = getImage("ref2.bmp")
    p = 100
    k = math.ceil(math.log(p,2))
    d = int(math.pow(2,k-1))
    print LogarithmicSearch(len(test)/2,len(test)/2,d,test,ref)