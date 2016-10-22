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
public class LoadData {

    /**
     * @param args the command line arguments
     */
    private static int[][][] trainData, testData;
    private static int[] trainLabel, testLabel;

    private LinkedList<Vector> ReadTrainData() {
        int index;
        String imageCount = "", rowCount = "", colCount = "";
        Path path;
        byte[] data;
        LinkedList<Vector> TrainData = new LinkedList<>();
        try {
            System.out.print("Reading training data...");
            path = Paths.get("Data/train-images.idx3-ubyte");
            data = Files.readAllBytes(path);
            for (int i = 4; i < 8; i++) {
                imageCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            for (int i = 8; i < 12; i++) {
                rowCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            for (int i = 12; i < 16; i++) {
                colCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            trainData = new int[GetValue(imageCount)][GetValue(rowCount)][GetValue(colCount)];
            index = 16;
            System.out.println(trainData.length);
            System.out.println(trainData[0].length + " " + trainData[0][0].length);
            for (int i = 0; i < trainData.length; i++) {
                LinkedList<Double> temp = new LinkedList<>();
                for (int j = 0; j < trainData[i].length; j++) {
                    for (int k = 0; k < trainData[i][j].length; k++) {
                        //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                        //trainData[i][j][k]=GetValue(s);
                        trainData[i][j][k] = (data[index] & 0xFF);
                        index++;
                        temp.add((double) testData[i][j][k]);
                        /*if(trainData[i][j][k]>0){
                            System.out.print(String.format("%03d",trainData[i][j][k])+" ");
                        }
                        else{
                            System.out.print("    ");
                        }*/
                    }
                    //System.out.print("\n");
                }
                Vector vec = new Vector(temp.size(), 1, temp); // input is 784 x 1 Vector
                //System.out.print("\n");
            }
            data = null;
            imageCount = "";
            path = Paths.get("Data/train-labels.idx1-ubyte");
            data = Files.readAllBytes(path);
            for (int i = 4; i < 8; i++) {
                imageCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            trainLabel = new int[GetValue(imageCount)];
            index = 8;
            for (int i = 0; i < trainLabel.length; i++) {
                //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                //trainLabel[i]=GetValue(s);
                trainLabel[i] = (data[index] & 0xFF);
                index++;
                //System.out.println(trainLabel[i]);
            }
            System.out.print(" DONE!!!\n");
        } catch (Exception ex) {

        }
        return TrainData;
    }

    public Data[] ReadTestData() {
        Data[] TestData = new Data[testData.length+1] ;
        try {
            System.out.print("Reading test data...");
            int index;
            String imageCount = "", rowCount = "", colCount = "";
            byte[] data;
            Path path = Paths.get("Data/t10k-images.idx3-ubyte");
            data = Files.readAllBytes(path);
            for (int i = 4; i < 8; i++) {
                imageCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            for (int i = 8; i < 12; i++) {
                rowCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            for (int i = 12; i < 16; i++) {
                colCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            testData = new int[GetValue(imageCount)][GetValue(rowCount)][GetValue(colCount)];
            index = 16;
            for (int i = 0; i < testData.length; i++) {
                LinkedList<Double> in = new LinkedList<>();
                for (int j = 0; j < testData[i].length; j++) {
                    for (int k = 0; k < testData[i][j].length; k++) {
                        //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                        //testData[i][j][k]=GetValue(s);
                        testData[i][j][k] = (data[index] & 0xFF);
                        index++;
                      //  System.out.println((double(testData[i][j][k]);
                        in.add((double) testData[i][j][k]);
                        /*if(testData[i][j][k]>0){
                            System.out.print(String.format("%03d",testData[i][j][k])+" ");
                        }
                        else{
                            System.out.print("    ");
                        }*/
                    }
                    //System.out.print("\n");
                }
                
                TestData[i].in = new Vector(in.size(), 1, in); // input is 784 x 1 Vector
                //System.out.print("\n");
            }
            data = null;
            imageCount = "";
            path = Paths.get("Data/t10k-labels.idx1-ubyte");
            data = Files.readAllBytes(path);
            for (int i = 4; i < 8; i++) {
                imageCount += String.format("%8s", Integer.toBinaryString(data[i] & 0xFF)).replace(' ', '0');
            }
            testLabel = new int[GetValue(imageCount)];
            index = 8;
            for (int i = 0; i < testLabel.length; i++) {
                //String s=String.format("%8s",Integer.toBinaryString(data[index] & 0xFF)).replace(' ', '0');
                //testLabel[i]=GetValue(s);
                LinkedList<Double> out = new LinkedList<>();
                testLabel[i] = (data[index] & 0xFF);
                for(int k=0;k<=9;i++){
                    if(testLabel[i]==k){
                        out.add(1.00) ;
                    }else out.add(0.00) ;
                }
                TestData[i].out = new Vector(out.size(),1,out) ;
                index++;
                System.out.println(testLabel[i]);
            }
            System.out.print(" DONE!!!\n");
         
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return TestData;
    }

    private static int GetValue(String s) {
        int value = 0, power = s.length() - 1;
        for (int i = 0; i < s.length(); i++) {
            value += (Character.getNumericValue(s.charAt(i))) * Math.pow(2, power);
            power--;
        }
        return value;
    }
}

