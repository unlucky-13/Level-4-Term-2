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
def generate_weight_vector(data,weight_vector):
    weight_vector=list(weight_vector)
    #print weight_vector
    learning_rate = 0.7
    wrongly_classified=[]
    next_weight_vector=weight_vector
   # print len(weight_vector)
    for i in range(len(data)):
        cross = 0.00
        for j in range(len(weight_vector)):
            cross += (weight_vector[j] * traindata[i][j])
        # print  cross
        if cross > 0:
            classNo = 2.0
        else:
            classNo = 1.0
        if classNo != traindata[i][4]:
            wrongly_classified.append(i)



    for i in range(len(wrongly_classified)):
        idx = wrongly_classified[i]
        if data[idx][4] != 2.00:
            delta = -1.00
        else:
            delta = 1.00
        for j in range(len(weight_vector)):
            next_weight_vector[j] += (delta * learning_rate *data[idx][j])
    rightly_classified = len(data)-len(wrongly_classified)

    return [rightly_classified,next_weight_vector]
#-----------------------------------------------------------------------------------------------------------------

if __name__=='__main__':
    traindata = loadFile("Train.txt")
    pocket_vector =[1,1,1,1]
    iterations=100
    best_rightly_classified=0
    #print type(pocket_vector)
    #count=0
    while iterations>0:
     #   count+=1
        iterations-=1
        [rightly_classified,next_weight_vector] = generate_weight_vector(traindata,pocket_vector)
        if rightly_classified>=best_rightly_classified :
            pocket_vector = next_weight_vector
            best_rightly_classified=rightly_classified
            #print best_rightly_classified
        else:
            break

    #print  "-------------converges after------------- ", count, " iterations"

    right=wrong=0
    testdata = loadFile("Test.txt")
    for i in range(len(testdata)):
        cross=0.0
        for j in range(len(pocket_vector)):
            cross+=(pocket_vector[j]*testdata[i][j])
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