/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ann;

import java.util.LinkedList;

/**
 *
 * @author mazharul
 */
public class Main {
    public static void main(String args[]){
        LoadData loadData = new LoadData() ;
        
//          TRAINING PHASE          ////////////////////////////////////
        LinkedList<Data> TrainData  = loadData.ReadTrainData() ; // the TrainData is a linked list of pair(x,y) where x is the input and y is the expected output for this input
        Network network = new Network(TrainData.get(0).in.row,TrainData.get(0).out.row ,5, 20) ; 
        // int  NeuronNo in the input layer 
        // int NeuronNo in the output layer 
        // int total layer no including hiddenlayer+inputlaye+outputlayer
        // int No of Nerons in the hidden layers
        //network.printWeightVectos();  // after randomly initializaing printing the wieght vecs in between the layers 
        int i=0 ;
///  for(int i=0;i<TrainData.size();i++){
            Vector output = network.forwardPropagation(TrainData.get(i).in) ;
            network.backPropagation(output,TrainData.get(i).out) ; // 
      //  }
    }
}
