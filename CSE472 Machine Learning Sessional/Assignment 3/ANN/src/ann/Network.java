/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ann;
import java.util.Random ;
import java.util.LinkedList;
import java.util.concurrent.ThreadLocalRandom;

/**
 *
 * @author mazharul
 */
public class Network {
    
    
    
    LinkedList<Vector> weightVecss  ;
    public Network(int inputNeuronNo,int outputNeuronNo,int layerNo,int NeronsPerLayer) {
                
                // assigning the weight vectors 
                weightVecss = new LinkedList<>() ;
                LinkedList<Double> ll = getRandomLinkedList((inputNeuronNo+1)*(NeronsPerLayer+1)) ;
                Vector vec = new Vector(inputNeuronNo+1,NeronsPerLayer+1,ll) ;
                weightVecss.add(vec) ; // between the input layer and the 1st hidden layer weight vector
                for(int i=0;i<layerNo-3;i++){ // between the hidden layers weight vectors
                    ll = getRandomLinkedList((NeronsPerLayer+1)*(NeronsPerLayer+1)) ;
                    vec = new Vector((NeronsPerLayer+1),(NeronsPerLayer+1), ll) ;
                }
                // between the last hidden  layer and the output layer 
                ll = getRandomLinkedList((inputNeuronNo+1)*(outputNeuronNo+1)) ;
                vec =     new Vector(inputNeuronNo+1,outputNeuronNo+1,ll) ;
                weightVecss.add(vec) ;
    }
    public LinkedList<Double> getRandomLinkedList(int size){ // for initializing the weight vectors
        LinkedList<Double> ll = new LinkedList<>() ;
        for(int i=0;i<size;i++){
            ll.add(ThreadLocalRandom.current().nextDouble(0,1.00)) ;
        } 
        return ll ;
    }
   public void printWeightVectos(){
       for(int i=0;i<weightVecss.size();i++){
           System.out.println("Weight vectos in between laye "+i+" and "+(i+1));
           weightVecss.get(i).print();
       }
   }
    public static void main(String args[]){
                LoadData ld = new LoadData() ;
                LinkedList<Data> TrainData  = ld.ReadTrainData() ;
                /*
                for(int i=0;i<1;i++){
                    testData[i].in.print(); 
                     testData[i].out.print(); 
                }
                */
                
                
    }
}
