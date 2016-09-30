/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*package assignment.pkg2;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;*/

/**
 *
 * @author User
 */
/*public class NB {
    
}*/

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
import java.io.PrintWriter;
import java.util.LinkedList;

/**
 *
 * @author User
 */
public class NB {

    /**
     * @param args the command line arguments
     */
    private static SuperHashTable sht;
    private static SuperHashTable[] shtArray;
    private static double[] accuracy;
    NB() {
        // TODO code application logic here
        //sht=new SuperHashTable();
        accuracy=new double[50];
        double alpha=tuneAlpha();
        Train(alpha);
        //GatherData();
        //Test(alpha);
        //testXMLreading();
    }
    
    public static double[] GatherData(){
        double mean=0,sd=0;
        double[] ret=new double[2];
        for(int i=0;i<accuracy.length;i++){
            mean+=accuracy[i];
        }
        mean=mean/accuracy.length;
        for(int i=0;i<accuracy.length;i++){
            sd+=Math.pow((accuracy[i]-mean),2);
        }
        
        sd=sd/(double)(accuracy.length-1);
        sd=Math.sqrt(sd);
        //System.out.println("Mean= "+mean+"  SD= "+sd);
        ret[0]=mean;
        ret[1]=sd;
        return ret;
    }
    
    private static double tuneAlpha(){
        double alpha=0,t=0,maxAlpha=10,minAlpha=0,maxAccuracy=0,retAlpha=0;
        String topicsFile="Data/topics.txt",inputFile;
        String[] topics=new String[100];
        BufferedReader br=null;
        String fileName="",line="";
        int i,count;
        try {
            sht=new SuperHashTable();
            shtArray=new SuperHashTable[50];
            for(i=0;i<shtArray.length;i++){
                shtArray[i]=new SuperHashTable();
            }
            br=new BufferedReader(new FileReader(topicsFile));
            i=0;
            while((fileName=br.readLine())!=null){
                topics[i]=fileName;
                i++;
            }
            i=0;
            while(topics[i]!=null){
                count=0;
                inputFile="Data/Training/"+topics[i]+".xml";
                br=new BufferedReader(new FileReader(inputFile));
                for(int k=0;k<500;k++){
                    line=br.readLine();
                    if(line.indexOf("<row")!=-1){
                        String[] parts=line.split("&lt;p&gt;");
                        String input="";
                        for(int j=1;j<parts.length;j++){
                            String[] temp=parts[j].split("&lt;/p&gt;");
                            input=input+" "+temp[0];
                            //System.out.println(temp[0]);
                        }
                        count++;
                        //System.out.println(input+"\n\n");
                        shtArray[0].addDocument(topics[i], input);
                    }
                }
                i++;
                //System.out.println(inputFile+" done!"+" Line count= "+count);
            }
            //Train();
            PrintWriter writer = new PrintWriter("Alpha.txt", "UTF-8");
            //writer.println("The first line");
            //writer.println("The second line");
            //writer.close();
            writer.println("Alpha : Accuracy");
            for(alpha=1;alpha<=10;alpha++){
                t=Test(0,alpha);
                writer.println(alpha+" : "+t);
                if(t>maxAccuracy){
                    maxAccuracy=t;
                    maxAlpha=alpha;
                    minAlpha=alpha-1;
                }
            }
            for(alpha=minAlpha;alpha<=maxAlpha;alpha+=(maxAlpha-minAlpha)/(double)100){
                t=Test(0,alpha);
                writer.println(alpha+" : "+t);
                if(t>maxAccuracy){
                    maxAccuracy=t;
                    retAlpha=alpha;
                }
            }
            writer.close();
            //System.out.println("MaxAccuracy= "+maxAccuracy+"  Alpha= "+retAlpha);
            //sht.show();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br!=null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }   
        shtArray[0]=null;
        return retAlpha;
    }
    
    /*private static void testXMLreading(){
        String topicsFile="Data/topics.txt",inputFile;
        String[] topics=new String[100];
        BufferedReader br=null;
        String fileName="",line="";
        try {
            br=new BufferedReader(new FileReader("Data/Training/3d_Printer.xml"));
            line=br.readLine();
            line=br.readLine();
            while((line=br.readLine())!=null){
            String[] parts=line.split("&lt;p&gt;");
            //parts=parts[1].split("&lt;/p&gt;&#xA;");
            for(int i=1;i<parts.length;i++){
                String[] temp=parts[i].split("&lt;/p&gt;");
                System.out.println(temp[0]);
            }
            
            System.out.println("\n\n");
            }*/
            //line=br.readLine();
            /*parts=line.split("Body=\"&lt;p&gt;");
            parts=parts[1].split("&lt;/p&gt;&#xA;");
            System.out.println("\n\n"+parts[0]);*/
            //parts=line.split("&lt;p&gt;");
            //parts=parts[1].split("&lt;/p&gt;&#xA;");
            /*for(int i=1;i<parts.length;i++){
                String[] temp=parts[i].split("&lt;/p&gt;");
                System.out.println(temp[0]);
            }
            System.out.println("\n\n"+line);*/
        /*} catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br!=null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }   
    }*/
    
    private static void Train(double alpha){
        String topicsFile="Data/topics.txt",inputFile;
        String[] topics=new String[100];
        BufferedReader br=null;
        String fileName="",line="";
        int count=1,i;
        try {
            shtArray=new SuperHashTable[50];
            for(i=0;i<shtArray.length;i++){
                shtArray[i]=new SuperHashTable();
            }
            br=new BufferedReader(new FileReader(topicsFile));
            i=0;
            while((fileName=br.readLine())!=null){
                topics[i]=fileName;
                i++;
            }

            /*i=0;
            while(topics[i]!=null){
                inputFile="Data/Training/"+topics[i]+".xml";
                br=new BufferedReader(new FileReader(inputFile));
                line=br.readLine();
                line=br.readLine();
                while((line=br.readLine())!=null){
                    String[] parts=line.split("&lt;p&gt;");
                    String input="";
                    for(int j=1;j<parts.length;j++){
                        String[] temp=parts[j].split("&lt;/p&gt;");
                        input=input+" "+temp[0];
                        //System.out.println(temp[0]);
                    }

                    System.out.println(input+"\n\n");
                    sht.addDocument(topics[i], input);
                }
                i++;
            }*/
            //System.out.println("Training...");
            //while(count<=50){
            i=0;
            while(topics[i]!=null){
                count=0;
                inputFile="Data/Training/"+topics[i]+".xml";
                br=new BufferedReader(new FileReader(inputFile));
                /*line=br.readLine();
                line=br.readLine();*/
                //while((line=br.readLine())!=null){
                while(count!=4999){
                //for(int k=0;k<50;k++){
                    line=br.readLine();
                    if(line.indexOf("<row")!=-1){
                        String[] parts=line.split("&lt;p&gt;");
                        String input="";
                        for(int j=1;j<parts.length;j++){
                            String[] temp=parts[j].split("&lt;/p&gt;");
                            input=input+" "+temp[0];
                            //System.out.println(temp[0]);
                        }
                        count++;
                        //System.out.println(input+"\n\n");
                        shtArray[count/100].addDocument(topics[i], input);
                    }
                }
                i++;
                //System.out.println(inputFile+" done!");
            }
            for(i=0;i<shtArray.length;i++){
                accuracy[i]=Test(i,alpha);
                //System.out.println(i+" : "+accuracy[i]);
            }
            
            //}
            
            //sht.show();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br!=null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }   
    }
    
    private static double Test(int index,double alpha){
        double accuracy=0;
        String topicsFile="Data/topics.txt",inputFile;
        String[] topics=new String[100];
        BufferedReader br=null;
        String fileName="",line="";
        try {
            br=new BufferedReader(new FileReader(topicsFile));
            int i=0,validity=0,observed=0;
            while((fileName=br.readLine())!=null){
                topics[i]=fileName;
                i++;
            }

            /*i=0;
            while(topics[i]!=null){
                inputFile="Data/Test_test/"+topics[i]+".txt";
                br=new BufferedReader(new FileReader(inputFile));
                while((line=br.readLine())!=null){
                    int validity=sht.testResult(topics[i], line);
                    System.out.println("Result: "+validity);
                }
                i++;
            }*/
            //System.out.println("Testing...");
            i=0;
            while(topics[i]!=null){
                inputFile="Data/Test/"+topics[i]+".xml";
                br=new BufferedReader(new FileReader(inputFile));
                for(int k=0;k<50;k++){
                    line=br.readLine();
                    if(line.indexOf("<row")!=-1){
                        String[] parts=line.split("&lt;p&gt;");
                        String input="";
                        for(int j=1;j<parts.length;j++){
                            String[] temp=parts[j].split("&lt;/p&gt;");
                            input=input+" "+temp[0];
                            //System.out.println(temp[0]);
                        }

                        //System.out.println(input+"\n\n");
                        validity+=shtArray[index].testResult(topics[i], line, alpha);
                        observed++;
                    }
                }
                i++;
                //System.out.println(inputFile+" done!");
                /*for(int j=0;j<50;j++){
                    observed++;
                    line=br.readLine();
                    validity+=sht.testResult(topics[i], line);
                    //System.out.println("Result: "+validity);
                }
                i++;*/
            }
            accuracy=(validity/(double)observed);
            //System.out.println("\n\nTotal Tested: "+observed+"  Valid: "+validity/*+"  Zero: "+sht.zeroCount*/+"  Alpha= "+alpha+"  Accuracy= "+accuracy);
            
            /*inputFile="Data/Test/"+topics[0]+".xml";
            br=new BufferedReader(new FileReader(inputFile));
            i=0;
            int validity=0;
            while(i<50){
                line=br.readLine();
                validity+=sht.testResult(topics[i], line);
                //System.out.println("Result: "+validity);
                i++;
            }
            System.out.println("Total Tested: 50  Valid: "+validity);*/

            
            
            //sht.show();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br!=null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }   
        return accuracy;
    }
    
}
