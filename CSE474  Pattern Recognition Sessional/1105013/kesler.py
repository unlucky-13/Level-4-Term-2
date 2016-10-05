attributeNo=4
classNo=3
#----------------------------------------------------------------------------------------------------------
def loadFile(fileName,kesler):
    with open(fileName) as f:
        array = []
        for line in f:  # read rest of lines
            array.append([float(x) for x in line.split()])

    for data in array:
        val = data.pop()
        data.append(1.00)
        data.append(val)
    if kesler==0:
        return array

    result=[]
    for data in array:
        className=data[4]-1 # className

        for classtype in range(0, classNo):
            new_data = []
            if classtype==className:
                continue
            for i in range(3):
                if i==className:
                    for k in range(4):
                        new_data.append(data[k])
                elif classtype==i:
                        for k in range(4):
                            new_data.append(-data[k])
                else:
                    for k in range(4):
                        new_data.append(0)
           # print  new_data
            result.append(new_data)
   # print result
    return  result
#------------------------------------------------------------------------------------------------------------------
if __name__=='__main__':

    traindata = loadFile("Train_Kesler.txt",1)
    #print  trainData
    weight_vector = [1.00 for x in range(classNo*attributeNo)]
    #print  weight_vec
    count=0
    iterations = 50
    learning_rate = 0.7
    while iterations > 0:
        wrongly_classified = []
        iterations -= 1
        count+=1
        for i in range(len(traindata)):
            cross = 0.00
            for j in range(len(weight_vector)):
                cross += (weight_vector[j] * traindata[i][j])
            # print  cross
            if cross<0:
                wrongly_classified.append(i)
        if len(wrongly_classified) == 0:
            print  "converges after ",count," iterations"
            break
        for i in range(len(wrongly_classified)):
            idx = wrongly_classified[i]
            delta=1.00
            for j in range(len(weight_vector)):
                weight_vector[j] += (delta * learning_rate * traindata[idx][j])

        #print weight_vector
    #print  iterations
    testdata = loadFile("Test_Kesler.txt",0)
    wrong=0
    right=0
    for test in testdata:
        cross=0
        type=-1
        classNo=-1
        value=0
        #print len(test)," ",len(weight_vector)
        for i in range(len(weight_vector)):
            cross+=(test[i%4]*weight_vector[i])
            if (i+1)%4==0:
                if cross>value:
                    value=cross
                    type=(i+1)/4
                cross=0
        #print type," ",test[4]
        if type!=test[4]:
            wrong+=1
        else:
            right+=1

    print "Right :->",right,"Wrong :->",wrong

    print "Accuracy ->", ((right*100.00)/(right+wrong)), " % "
    #