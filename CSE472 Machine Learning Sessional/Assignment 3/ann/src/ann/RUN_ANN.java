/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package ann;

import java.util.LinkedList;
import java.util.concurrent.ThreadLocalRandom;

/**
 *
 * @author User
 */
public class RUN_ANN {
    private static double[][] trainingSet;
    private static double[][] validationSet;
    private static double[][] testSet;
    private static int[] trainLabel,validationLabel,testLabel;
    private static double weights[][][],values[][],errors[][];
    private static int layerCount;
    private static double eita;
        
    RUN_ANN(int[][][] trainSet,int[][][] testSet,int[] trainLabel,int[] testLabel,int hiddenLayers,int[] nodeCount,double eita){
        this.trainLabel=new int[(int)(trainSet.length*.8)];
        this.validationLabel=new int[trainSet.length-(int)(trainSet.length*.8)];
        this.testLabel=new int[testSet.length];
        this.trainingSet=new double[(int)(trainSet.length*.8)][trainSet[0].length*trainSet[0][0].length];
        this.validationSet=new double[trainSet.length-(int)(trainSet.length*.8)][trainSet[0].length*trainSet[0][0].length];
        this.testSet=new double[testSet.length][testSet[0].length*testSet[0][0].length];
        layerCount=2+hiddenLayers;
        this.errors=new double[layerCount-1][];
        for(int i=0;i<errors.length-1;i++){
            errors[i]=new double[nodeCount[i]];
        }
        errors[errors.length-1]=new double[10];
        this.eita=eita;
        values=new double[layerCount][];
        values[0]=new double[trainSet[0].length*trainSet[0][0].length+1];
        values[values.length-1]=new double[11];
        for(int i=1;i<values.length-1;i++){
            values[i]=new double[nodeCount[i-1]+1];
        }
        
        weights=new double[layerCount-1][][];
        for(int i=0;i<weights.length;i++){
            weights[i]=new double[values[i+1].length-1][values[i].length];
        }
        
        int index,startIndex;
        for(int i=0;i<trainingSet.length;i++){
            index=0;
            this.trainLabel[i]=trainLabel[i];
            for(int j=0;j<trainSet[i].length;j++){
                for(int k=0;k<trainSet[i][j].length;k++){
                    trainingSet[i][index]=trainSet[i][j][k]/(double)1000;
                    index++;
                }
            }
        }
        
        startIndex=(int)(trainSet.length*.8);
        for(int i=startIndex;i<trainSet.length;i++){
            index=0;
            this.validationLabel[i-startIndex]=trainLabel[i];
            for(int j=0;j<trainSet[i].length;j++){
                for(int k=0;k<trainSet[i][j].length;k++){
                    validationSet[i-startIndex][index]=trainSet[i][j][k]/(double)1000;
                    index++;
                }
            }
        }
        
        for(int i=0;i<testSet.length;i++){
            index=0;
            this.testLabel[i]=testLabel[i];
            for(int j=0;j<testSet[i].length;j++){
                for(int k=0;k<testSet[i][j].length;k++){
                    this.testSet[i][index]=testSet[i][j][k]/(double)1000;
                    index++;
                }
            }
        }
        
        SetWeights();
    }
    
    private void SetWeights(){
        for(int i=0;i<weights.length;i++){
            for(int j=0;j<weights[i].length;j++){
                for(int k=0;k<weights[i][j].length;k++){
                    weights[i][j][k]=ThreadLocalRandom.current().nextDouble(0,1.00);
                }
            }
        }
    }
    
    private static void ForwardPropagation(int index,String set){
        if(set.equals("TRAIN")){
            for(int i=0;i<trainingSet[index].length;i++){
                values[0][i+1]=trainingSet[index][i];
            }
        }
        else if(set.equals("TEST")){
            for(int i=0;i<testSet[index].length;i++){
                values[0][i+1]=testSet[index][i];
            }
        }
        else if(set.equals("VALIDATION")){
            for(int i=0;i<validationSet[index].length;i++){
                values[0][i+1]=validationSet[index][i];
            }
        }
        values[0][0]=1;
        
        for(int i=1;i<values.length;i++){
            Softmax(values[i-1],weights[i-1],values[i]);
        }
     
    }
    
    private static void BackwardPropagation(int index){
        CalculateErrors(index);
        UpdateWeights(eita);
    }
    
    private static void CalculateErrors(int index){
        int tk;
        double ok;
        for(int i=0;i<errors[errors.length-1].length;i++){
            if(i==index){
                tk=1;
            }
            else{
                tk=0;
            }
            ok=values[values.length-1][i+1];
            errors[errors.length-1][i]=ok*(1-ok)*(tk-ok);
        }
        
        for(int i=layerCount-2;i>=1;i--){
            for(int j=0;j<errors[i-1].length;j++){
                double sum=0;
                for(int k=0;k<weights[i].length;k++){
                    sum+=weights[i][k][j+1]*errors[i][k];
                }
                ok=values[i][j+1];
                errors[i-1][j]=sum*ok*(1-ok);
            }
        }
    }
    
    private static void UpdateWeights(double eita){
        for(int i=0;i<weights.length;i++){
            for(int j=0;j<weights[i].length;j++){
                for(int k=1;k<weights[i][j].length;k++){
                    weights[i][j][k]=weights[i][j][k]+eita*errors[i][j]*values[i][k];
                }
            }
        }
    }
    
    private static void Softmax(double[] inValues,double[][] weights,double[] outValues){
        outValues[0]=1;
        double total=0;
        if(inValues.length!=weights[0].length || weights.length!=(outValues.length-1)){
            System.out.println("Error!!! Dimentions not matched!!");
            return;
        }
        for(int i=1;i<outValues.length;i++){
            total=0;
            for(int j=0;j<weights[i-1].length;j++){
                total+=weights[i-1][j]*inValues[j];
            }
            outValues[i]=total;
        }
        
        total=0;
        for(int i=1;i<outValues.length;i++){
            total+=Math.exp(outValues[i]);
        }
        for(int i=1;i<outValues.length;i++){
            outValues[i]=Math.exp(outValues[i])/total;
        }
        
    }
    
    public static void Run(){
        int count=0,count2=0;
        double[][][] updatedWeights=new double[weights.length][][];
        double acc,lowerBound=0.8;
        while(count<trainingSet.length){
            ForwardPropagation(count,"TRAIN");
            BackwardPropagation(trainLabel[count]);
            count++;
            count2++;
            if(count2%50==0){
                acc=GetAccuracy("VALIDATION");
                count2=0;
                //System.out.println(acc);
                if(acc>lowerBound){
                    for(int i=0;i<updatedWeights.length;i++){
                        updatedWeights[i]=weights[i];
                    }
                    lowerBound=acc;
                }
            }
        }
        for(int i=0;i<weights.length;i++){
            weights[i]=updatedWeights[i];
        }
        System.out.println("Accuracy in VALIDATION set: "+lowerBound);
        System.out.println("Accuracy in TEST set: "+GetAccuracy("TEST"));
        
    }
    
    private static double GetAccuracy(String set){
        int accuracy=0,total=0,count=0;
        if(set.equals("TEST")){
            count=testSet.length;
        }
        else if(set.equals("VALIDATION")){
            count=validationSet.length;
        }
        else{
            System.out.println("ERROR!!!");
            return 0;
        }
        for(int i=0;i<count;i++){
            ForwardPropagation(i,set);
            double maxVal=-100;
            int predictedLabel=-1,expectedlabel=-1;
            for(int j=1;j<values[values.length-1].length;j++){
                if(values[values.length-1][j]>maxVal){
                    maxVal=values[values.length-1][j];
                    predictedLabel=j;
                }            
            }
            if(set.equals("TEST")){
                expectedlabel=testLabel[i];
            }
            else if(set.equals("VALIDATION")){
                expectedlabel=validationLabel[i];
            }
            else{
                System.out.println("ERROR!!!");
                return 0;
            }
            if(predictedLabel-1==expectedlabel){
                accuracy++;
            }
            total++;
        }
        return (accuracy/(double)total);
    }
    
}
