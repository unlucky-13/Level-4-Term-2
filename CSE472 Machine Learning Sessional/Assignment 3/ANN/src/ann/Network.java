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
    LinkedList<Vector>a ; // the values in the layers 
    int layerNo ,NeuronsPerLayer;
    public Network(int inputNeuronNo,int outputNeuronNo,int _layerNo,int _NeuronsPerLayer) {
                layerNo = _layerNo ; 
                NeuronsPerLayer = _NeuronsPerLayer ;
                // assigning the weight vectors 
                weightVecss = new LinkedList<>() ;
                LinkedList<Double> ll = getRandomLinkedList((inputNeuronNo+1)*(NeuronsPerLayer+1)) ;
                Vector vec = new Vector(inputNeuronNo+1,NeuronsPerLayer+1,ll) ;
                weightVecss.add(vec) ; // between the input layer and the 1st hidden layer weight vector
                for(int i=0;i<layerNo-3;i++){ // between the hidden layers weight vectors
                    ll = getRandomLinkedList((NeuronsPerLayer+1)*(NeuronsPerLayer+1)) ;
                    vec = new Vector((NeuronsPerLayer+1),(NeuronsPerLayer+1), ll) ;
                    weightVecss.add(vec) ;
                }
                // between the last hidden  layer and the output layer 
                ll = getRandomLinkedList((inputNeuronNo+1)*(outputNeuronNo+1)) ;
                vec =     new Vector(NeuronsPerLayer+1,outputNeuronNo+1,ll) ;
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
           System.out.println("Weight vectors in between layer "+i+" and "+(i+1));
           weightVecss.get(i).print();
       }
   }
   public void forwardPropagation(Vector input){
        if(input.row!=weightVecss.get(0).row){
            System.out.println("input Dimension error") ;
            return ;
        }
        a = new LinkedList<>() ;
        a.add(input) ;
        Vector last = input ;
        for(int i=1;i<layerNo;i++){
            try{
                Vector vecs = dot(weightVecss.get(i-1),last) ;
                vecs = activationFunction(vecs) ;
                vecs.Matrix[0][0]=1.00 ; // since it is always 1
                a.add(vecs) ;
            }catch(Exception ex){
                System.out.println("excepeiton in DOT product");
            }
        }
        for(int i=0;i<a.size();i++){
            System.out.println("Values at"+i) ;
            a.get(i).print();
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

    private Vector dot(Vector v1, Vector v2) throws DimensionErrorException {
        // returns the dot product
        // throws exception if dimension doesn't match
        System.out.println(v1.col+" "+v2.row) ; 
        if(v1.col!=v2.row){
            throw new DimensionErrorException() ;
        }
        LinkedList<Double> ll = new LinkedList<>() ;
        for(int i=0;i<v1.row;i++){
            for(int j=0;j<v2.col;j++){
                Double val=0.0 ;
                for(int k=0;k<v1.col;k++){
                    val += v1.Matrix[i][k]*v2.Matrix[k][j] ;
                }
                ll.add(val) ;
            }
        }
        Vector res = new Vector(v1.row,v2.col,ll) ;
        return res ;
    }

    private Vector activationFunction(Vector vecs) {
        for(int i=0;i<vecs.row;i++){
            for(int j=0;j<vecs.col;j++){
                vecs.Matrix[i][j] = 1.000/(1.00-Math.exp(vecs.Matrix[i][j])) ;
            }
        }
        return vecs ;
    }
}
class DimensionErrorException extends Exception{
    public DimensionErrorException() {
        
    }
}