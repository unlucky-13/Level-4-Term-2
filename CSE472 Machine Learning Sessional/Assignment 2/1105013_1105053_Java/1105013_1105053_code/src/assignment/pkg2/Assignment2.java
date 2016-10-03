/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package assignment.pkg2;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;

/**
 *
 * @author User
 */
public class Assignment2 {

    /**
     * @param args the command line arguments
     */
    private static NB nb;
    private static KNN knn;
    private static SuperHashTable sht;
    private static SuperHashTable[] shtArray;
    private static double[] accuracy;
    private static double[] NBdata,KNNdata;
    private static double t_05=1.66715,t_01=2.3812,t_005=2.64845,d=.12;
    public static void main(String[] args) {
        nb=new NB();
        NBdata=nb.GatherData();
        knn=new KNN();
        KNNdata=knn.GatherData(50); // number of runs = 50
        System.out.println(NBdata[0]+" "+NBdata[1]+" || "+KNNdata[0]+" "+KNNdata[1]);
        double t=(NBdata[0]-KNNdata[0]-d)/Math.sqrt((Math.pow(NBdata[1],2)+Math.pow(KNNdata[1],2))/(double)50);
        double dof=Math.pow((Math.pow(NBdata[1],2)+Math.pow(KNNdata[1],2))/50,2)/((Math.pow(NBdata[1],4)+Math.pow(KNNdata[1],4))/122500);
        dof=Math.round(dof);
        t=Math.abs(t);
        System.out.println("d.o.f.: "+dof+"  t: "+t);
        System.out.println("Null Hypothesis:  Mean_NB - Mean_KNN >= "+d*100);
        System.out.println("Alternative Hypothesis:  Mean_NB - Mean_KNN < "+d*100);
        System.out.println("\n\nAlpha = 0.05");
        if(t>t_05){
            System.out.println("Null Hypothesis Rejected And Alternative Hypothesis Accepted!");
        }
        else{
            System.out.println("Null Hypothesis Cannot Be Rejected And Alternative Hypothesis Cannot Be Accepted!");
        }
        System.out.println("\n\nAlpha = 0.005");
        if(t>t_005){
            System.out.println("Null Hypothesis Rejected And Alternative Hypothesis Accepted!");
        }
        else{
            System.out.println("Null Hypothesis Cannot Be Rejected And Alternative Hypothesis Cannot Be Accepted!");
        }
        System.out.println("\n\nAlpha = 0.01");
        if(t>t_01){
            System.out.println("Null Hypothesis Rejected And Alternative Hypothesis Accepted!");
        }
        else{
            System.out.println("Null Hypothesis Cannot Be Rejected And Alternative Hypothesis Cannot Be Accepted!");
        }
    }
    
}
