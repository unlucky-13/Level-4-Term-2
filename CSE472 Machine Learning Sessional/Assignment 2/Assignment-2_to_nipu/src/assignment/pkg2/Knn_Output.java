/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment.pkg2;

import java.util.LinkedList;

/**
 *
 * @author mazharul
 */
public class Knn_Output {
    
    public static void main(String args[]){
        KNN knn = new KNN() ;
        LinkedList<ClassDictionary> TrainDictionaryList = knn.Parse(knn.topicsList, 0) ;
        String [] algonames={
            "KNN","Euclidian","TD-IDF"
        } ;
        System.out.println("Algo Name\t"+"K\t"+"Accuracy\n");
        for(int algo=0;algo<3;algo++){
            for(int K=1;K<6;K+=2){
                double accuracy = knn.TestData(TrainDictionaryList,K,algo,0) ;
                System.out.println(algonames[algo]+"\t"+K+"\t"+accuracy+"\n") ;
            }
        }
    }
}
