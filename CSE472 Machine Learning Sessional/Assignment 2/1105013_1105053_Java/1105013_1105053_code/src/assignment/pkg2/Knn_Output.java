/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment.pkg2;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.LinkedList;

/**
 *
 * @author mazharul
 */
public class Knn_Output {
    
    public static void main(String args[]) throws FileNotFoundException{
        KNN knn = new KNN() ;
        LinkedList<ClassDictionary> TrainDictionaryList = knn.Parse(knn.topicsList, 0) ; 
        PrintWriter pw = new PrintWriter(new File("output.txt")) ;
        
        String [] algonames={
            "KNN","Euclidian","TD-IDF"
        } ;
        pw.printf("%20s%20s%20s\n","AlgoName","K","Accuracy");
        pw.println("------------------------------------------------------------") ;
        for(int algo=0;algo<3;algo++){
            for(int K=1;K<6;K+=2){
                double accuracy = knn.TestData(TrainDictionaryList,K,algo,0) ;
                pw.printf("%20s%20d%20f\n",algonames[algo],K,accuracy);
                
            }
        }
        pw.flush();
    }
}
