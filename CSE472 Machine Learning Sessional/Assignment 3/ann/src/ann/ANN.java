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

/**
 *
 * @author User
 */
public class ANN {

    /**
     * @param args the command line arguments
     */
    private static int[][][] trainData,testData;
    private static int[] trainLabel,testLabel;
    public static void main(String[] args) {
        // TODO code application logic here
        ReadData();
        int[] nodes=new int[2];
        nodes[0]=28;
        nodes[1]=15;
        RUN_ANN ra=new RUN_ANN(trainData,testData,trainLabel,testLabel,2,nodes,4);
        ra.Run();
    }
    
    private static void ReadData(){
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
            for(int i=0;i<trainData.length;i++){
                for(int j=0;j<trainData[i].length;j++){
                    for(int k=0;k<trainData[i][j].length;k++){
                        //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                        //trainData[i][j][k]=GetValue(s);
                        trainData[i][j][k]=(data[index] & 0xFF);
                        index++;
                        /*if(trainData[i][j][k]>0){
                            System.out.print(String.format("%03d",trainData[i][j][k])+" ");
                        }
                        else{
                            System.out.print("    ");
                        }*/
                    }
                    //System.out.print("\n");
                }
                //System.out.print("\n");
            }
            data=null;
            imageCount="";
            path=Paths.get("Data/train-labels.idx1-ubyte");
            data=Files.readAllBytes(path);
            for(int i=4;i<8;i++){
                imageCount+=String.format("%8s",Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');    
            }
            trainLabel=new int[GetValue(imageCount)];
            index=8;
            for(int i=0;i<trainLabel.length;i++){
                //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                //trainLabel[i]=GetValue(s);
                trainLabel[i]=(data[index] & 0xFF);
                index++;
                //System.out.println(trainLabel[i]);
            }
            System.out.print(" DONE!!!\n");
            System.out.print("Reading test data...");
            imageCount="";
            rowCount="";
            colCount="";
            data=null;
            path=Paths.get("Data/t10k-images.idx3-ubyte");
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
            testData=new int[GetValue(imageCount)][GetValue(rowCount)][GetValue(colCount)];
            index=16;
            for(int i=0;i<testData.length;i++){
                for(int j=0;j<testData[i].length;j++){
                    for(int k=0;k<testData[i][j].length;k++){
                        //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                        //testData[i][j][k]=GetValue(s);
                        testData[i][j][k]=(data[index] & 0xFF);
                        index++;
                        /*if(testData[i][j][k]>0){
                            System.out.print(String.format("%03d",testData[i][j][k])+" ");
                        }
                        else{
                            System.out.print("    ");
                        }*/
                    }
                    //System.out.print("\n");
                }
                //System.out.print("\n");
            }
            data=null;
            imageCount="";
            path=Paths.get("Data/t10k-labels.idx1-ubyte");
            data=Files.readAllBytes(path);
            for(int i=4;i<8;i++){
                imageCount+=String.format("%8s",Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');    
            }
            testLabel=new int[GetValue(imageCount)];
            index=8;
            for(int i=0;i<testLabel.length;i++){
                //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                //testLabel[i]=GetValue(s);
                testLabel[i]=(data[index] & 0xFF);
                index++;
                //System.out.println(testLabel[i]);
            }
            System.out.print(" DONE!!!\n");
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static int GetValue(String s){
        int value=0,power=s.length()-1;
        for(int i=0;i<s.length();i++){
            value+=(Character.getNumericValue(s.charAt(i)))*Math.pow(2,power);
            power--;
        }
        
        return value;
    } 
    
}
