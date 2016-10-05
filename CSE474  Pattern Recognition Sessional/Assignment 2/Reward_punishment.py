#----------------------------------------------------------------------------------------------------------
def loadFile(fileName):
    with open(fileName) as f:
        array = []
        for line in f:  # read rest of lines
            array.append([float(x) for x in line.split()])


    for data in array:
        val = data.pop()
        data.append(1.00)
        data.append(val)
    #print array
    return  array
#--------------------------------------------------------------------------------------------------------

if __name__=='__main__':
    traindata = loadFile("Train.txt")
    weight_vector =[1,1,1,1]
    iterations=4
    learning_rate = 0.7
    while iterations>0:
        iterations-=1
        for i in range(len(traindata)):
            cross = 0.00
            for j in range(len(weight_vector)):
                cross+=(weight_vector[j]*traindata[i][j])
            #print  cross
            if cross>0:
                classNo=2.0
                delta=-1.00
            else:
                classNo=1.0
                delta=1.00
            if classNo!=traindata[i][4]:

                for j in range(len(weight_vector)):
                    weight_vector[j]+=(delta*learning_rate*traindata[i][j])
        #print weight_vector

    right=wrong=0.00
    testdata = loadFile("Test.txt")
    for i in range(len(testdata)):
        cross=0.0
        for j in range(len(weight_vector)):
            cross+=(weight_vector[j]*testdata[i][j])
        if cross>0:
            classNo=2.0
        else:
            classNo=1.0
      #  print  classNo
        if classNo!=testdata[i][4]:
            wrong+=1
        else:
            right+=1
    print "Right :->",right,"Wrong :->",wrong

    print "Accuracy ->", ((right*100.00)/(right+wrong)), " % "