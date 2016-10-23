/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ann;
import java.util.LinkedList;
import java.util.concurrent.ThreadLocalRandom;

/**
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
                LinkedList<Double> ll = getRandomLinkedList(inputNeuronNo*(NeuronsPerLayer+1)) ;
                Vector vec = new Vector(inputNeuronNo,NeuronsPerLayer+1,ll) ;
                weightVecss.add(vec) ; // between the input layer and the 1st hidden layer weight vector
                for(int i=0;i<layerNo-3;i++){ // between the hidden layers weight vectors
                    ll = getRandomLinkedList((NeuronsPerLayer+1)*(NeuronsPerLayer+1)) ;
                    vec = new Vector((NeuronsPerLayer+1),(NeuronsPerLayer+1), ll) ;
                    weightVecss.add(vec) ;
                }
                // between the last hidden  layer and the output layer 
                ll = getRandomLinkedList((NeuronsPerLayer+1)*(outputNeuronNo)) ;
                vec =     new Vector(NeuronsPerLayer+1,outputNeuronNo,ll) ;
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
   public Vector forwardPropagation(Vector input){
                /*
                Vector t = Transpose(weightVecss.get(0)) ;
                System.out.println(t.row+" "+t.col) ;
                System.out.println(input.row+" "+input.col) ;
                */
      // /* 
       if(input.row!=weightVecss.get(0).row){
            System.out.println("input Dimension error") ;
            return null;
        }
        a = new LinkedList<>() ;
        a.add(input) ;
        Vector last = input ;
        for(int i=1;i<layerNo;i++){
            try{
                Vector t = Transpose(weightVecss.get(i-1)) ;
                Vector vecs = dot(t,last) ;
                vecs = activationFunction(vecs) ;
                vecs.Matrix[0][0]=1.00 ; // since it is always 1
                a.add(vecs) ;
            }catch(Exception ex){
                System.out.println("excepeiton in DOT product");
            }
        }
        /*
        for(int i=0;i<a.size();i++){
            System.out.println("Values at "+i) ;
            a.get(i).print();
        }
        */
        return a.getLast() ; // the output
        //*/
   }
   public void backPropagation(Vector output,Vector expectedOutput){
       // first calculate the error function
       
       
       LinkedList<Vector>error = new LinkedList<>() ;
       try{
            Vector last = subtract(output,expectedOutput) ;
            error.add(last) ;
            for(int i=layerNo-2;i>=1;i--){
                Vector derivative = new Vector(a.get(i+1).row, a.get(i+1).col,a.get(i+1).Matrix) ;
                derivative.print() ;
                last.print() ;
                for(int j=0;j<derivative.row;j++){
                    for(int k=0;k<derivative.col;k++){
                        derivative.Matrix[j][k] =last.Matrix[j][k]*derivative.Matrix[j][k]*(1.00-derivative.Matrix[j][k]) ;
                    }
                }
                System.out.println("-----------------------") ;
               // weightVecss.get(i).print();
                //derivative.print();
                last = dot(weightVecss.get(i),derivative) ;
                error.add(last) ;
            }
       }catch(Exception ex){
           
           System.out.println("Exception in back prop finding error vectors "+ex.toString());
       }
       // there is no error for input layer
   //    System.out.println("Printing the error vectors");
     //  System.out.println(error.size());
       /*
       for(int i=layerNo-2;i>=0;i--){
           error.get(i).print();  // here ith index error vector is for i+1 a-th 
       }
       */
       // now update the weights
       
       
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
         
        if(v1.col!=v2.row){
            System.out.println(v1.col+" "+v2.row) ;
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
                // it is done using sigmod function 
                //apply softmax function here 
            }
        }
        return vecs ;
    }
    private Vector Transpose(Vector vecs){
        LinkedList<Double> ll = new LinkedList<>() ;
        for(int j=0;j<vecs.col;j++){
            for(int i=0;i<vecs.row;i++){
                ll.add(vecs.Matrix[i][j]) ;
            }
        }
        Vector vec = new Vector(vecs.col,vecs.row,ll) ;
        return vec ;
    }

    private Vector subtract(Vector vec1, Vector vec2) throws DimensionErrorException{
        if(vec1.row!=vec2.row || vec1.col!=vec2.col){
            throw new DimensionErrorException() ;
        }
        LinkedList<Double> ll = new LinkedList<>() ;
        for(int i=0;i<vec1.row;i++){
            for(int j=0;j<vec1.col;j++){
                ll.add(vec1.Matrix[i][j]-vec2.Matrix[i][j]) ;
            }
        }
        Vector vec = new Vector(vec1.row,vec1.col,ll) ;
        return vec ;
    }
}
class DimensionErrorException extends Exception{
    public DimensionErrorException() {
        
    }
}