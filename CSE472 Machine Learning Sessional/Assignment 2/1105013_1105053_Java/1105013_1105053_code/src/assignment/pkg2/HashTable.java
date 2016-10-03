/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package assignment.pkg2;

import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 *
 * @author User
 */
public class HashTable {
    private String className;
    private TreeMap wordMap;
    private int wordCount;
    private int documentCount;
    
    HashTable(String className){
        this.className=className;
        wordMap=new TreeMap();
        wordCount=0;
        documentCount=0;
    }
    
    public void addWord(String word){
        if(!(wordMap.containsKey(word))){
            wordMap.put(word, new Integer(1));
        }
        else{
            int count=((Integer)wordMap.get(word)).intValue();
            wordMap.put(word, new Integer(count+1));
        }
        wordCount++;
    }
    
    public double getConditionalProbability(String word,int v,double alpha){
        int count;
        double probability;
        if(!(wordMap.containsKey(word))){
            count=0;
        }
        else{
            count=((Integer)wordMap.get(word)).intValue();
        }
        probability=Math.log((double)(count+1*alpha)/(double)(wordCount+v*alpha));
        return probability;
    }
    
    public void incrementDocumentCount(){
        documentCount++;
    }
    
    public int getDocumentCount(){
        return documentCount;
    }
    
    public void show(){
        Set set=this.wordMap.entrySet();
        Iterator i=set.iterator();

        while(i.hasNext()) {
            Map.Entry me=(Map.Entry)i.next();
            System.out.println(me.getKey()+" -> "+me.getValue());
        }
        System.out.println("Document Count: "+this.documentCount+" Word Count: "+this.wordCount);
    }
    
    /*public int getTotalWordCount(){
        return wordCount;
    }*/
    
}
