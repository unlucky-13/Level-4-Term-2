from loadFile import *
from Vector import *
from Network import *
import  csv
import  random
import  math

if __name__=='__main__':

    size_of_each_phase = 1000;
    TotalDataSet = loadCsv("abalone.data.txt") ;
    [TrainDataset, ValidationDataSet, TestDataset] = splitData(TotalDataSet, size_of_each_phase)

    bestAccuracy = 0
    # trying to find the best comboination

    for LayerNo in range(5,8):
        for NeuronPerLayer_ in range(10,11):
            for Learning_rate_  in range(10,11):

                ###########################################################Training Set#############################################################################
                intputLayer = TrainDataset[0][0].row
                outputLayer = TrainDataset[0][1].row
                #print TrainDataset[0][1].Matrix
                totalLayer=LayerNo # including the hidden layer
                NeuronPerLayer = NeuronPerLayer_
                Learning_rate= 1.00/Learning_rate_
                network = Network(intputLayer, outputLayer, totalLayer, NeuronPerLayer,Learning_rate);
                #print intputLayer
                for i in range(len(TrainDataset)):
                    res =  network.forwardPropagation(TrainDataset[i][0])
                    #print "The result is"
                    #print res.Matrix
                    #print  TrainDataset[0][1]
                    network.backPropagation(TrainDataset[i][1])


                network.finishBackprop()
                #print "Weight Vectros ->"
                #for i in range(len(network.weightVectors)):
                 #   print network.weightVectors[i].Matrix


               # res = network.forwardPropagation(TrainDataset[12][0])
               # print res.Matrix
                ########################################################################Validation Phase##############################################################################

                right = 0.0
                wrong = 0.0
                for i in range(len(ValidationDataSet)):
                    res1  = network.forwardPropagation(ValidationDataSet[i][0]).Matrix[1][0]
                    res2 = ValidationDataSet[i][1].Matrix[1][0]
                   # print res1
                    if abs(res1-res2)<=eps :
                        right+=1
                    else:
                        wrong+=1

                accuracy = right/(right+wrong)
               # print "Right ->",right
              #  print "Wrong ->",wrong
             #   print "Accuracy ->" ,right/(right+wrong)
                if accuracy>bestAccuracy:
                        bestNetwork = Network(intputLayer, outputLayer, totalLayer, NeuronPerLayer,Learning_rate);
                        bestNetwork.weightVectors = network.weightVectors
                        bestAccuracy = accuracy
                       # print  accuracy

    ##########################################################################################Testing phase##############################################################



    right = 0.0
    wrong = 0.0
    for i in range(len(TestDataset)):
        predicted_res = bestNetwork.forwardPropagation(TestDataset[i][0]).Matrix[1][0]
        expected_res = TestDataset[i][1].Matrix[1][0]
        if abs(predicted_res - expected_res) <= eps:
            right += 1
        else:
            wrong += 1
    accuracy1 += right / (right + wrong)
   # print "Right ->",right
    #print "Wrong ->",wrong
    print "Accuracy ->" ,accuracy1,"%"

