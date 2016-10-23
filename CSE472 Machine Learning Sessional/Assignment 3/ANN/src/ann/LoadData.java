/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package ann;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import static java.lang.Math.pow;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedList;

/**
 *
 * @author User
 */
public class LoadData{

    /**
     * @param args the command line arguments
     */
    private static int[][][] trainData,testData;
    private static int[] trainLabel,testLabel;
   
    public  LinkedList<Data> ReadTrainData(){
        
        LinkedList<Data> TrainData = new LinkedList<>() ;
        int index;
        String imageCount="",rowCount="",colCount="";
        Path path;
        byte[] data;
        try {
            System.out.print("Reading training data...");
            path=Paths.get("Data/train-images.idx3-ubyte");
            data=Files.readAllBytes(path);
            for(int i=4;i<8;i++){
                imageCount+=String.format("%8s",Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');    
            }
            for(int i=8;i<12;i++){
                rowCount+=String.format("%8s",Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            for(int i=12;i<16;i++){
                colCount+=String.format("%8s",Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            trainData=new int[GetValue(imageCount)][GetValue(rowCount)][GetValue(colCount)];
            index=16;
            
            byte[] data1=null;
            String imageCount1="";
            Path path1=Paths.get("Data/train-labels.idx1-ubyte");
            data1=Files.readAllBytes(path1);
            for(int i=4;i<8;i++){
                imageCount1+=String.format("%8s",Integer.toBinaryString(data1[i] & 0xFF)).replace(' ', '0');    
            }
            trainLabel=new int[GetValue(imageCount1)];
            int index1=8;
           // System.out.println(trainData.length);
           int iterations = Math.min(trainData.length,10) ; // heapspace dosn't allocate so much space for 60 0000 Train Data
            for(int i=0;i<iterations;i++){
                LinkedList<Double> x = new LinkedList<>() ;
                LinkedList<Double> y = new LinkedList<>() ;
                x.add(1.00) ; // since the 0 th input is always 1
                for(int j=0;j<trainData[i].length;j++){
                    for(int k=0;k<trainData[i][j].length;k++){
                        //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                        //trainData[i][j][k]=GetValue(s);
                        trainData[i][j][k]=(data[index] & 0xFF);
                        x.add((double)trainData[i][j][k]) ;
                        index++;
                        /*
                        if(trainData[i][j][k]>0){
                            System.out.print(String.format("%03d",trainData[i][j][k])+" ");
                        }
                        else{
                            System.out.print("    ");
                        }
                        */
                    }
                    //System.out.print("\n");
                }
                
                //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                //trainLabel[i]=GetValue(s);
                trainLabel[i]=(data1[index1] & 0xFF);
                for(int k=0;k<10;k++){
                    if(trainLabel[i]==k){
                        y.add(1.00) ;
                    }else y.add(0.00) ;
                }
                Vector in = new Vector(x.size(),1,x) ; // the input  784 x 1 Dimsion vector
                Vector out = new Vector(y.size(),1,y) ; // the expected output 10 x 1 Dimsion vector
                TrainData.add(new Data(in,out)) ;
                index1++;
                //System.out.println(trainLabel[i]);
               // System.out.println(TrainData.size());
            }
            
            System.out.print(" Train Data read DONE!!!\n");
        }catch(Exception ex){
                    System.out.println("Exception found in Train Data Read "+"\n"+ex.toString());
                    
        }
        return TrainData ;
       // return null ;
    }
    
    
    public Data [] ReadTestData(){
        return null ;
    }
    
    private int GetValue(String s){
        int value=0,power=s.length()-1;
        for(int i=0;i<s.length();i++){
            value+=(Character.getNumericValue(s.charAt(i)))*Math.pow(2,power);
            power--;
        }
        
        return value;
    } 
}