/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package assignment.pkg2;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 *
 * @author User
 */
public class SuperHashTable {
    public int zeroCount=0;
    private TreeMap docMap;
    private int docCount;
    private LinkedList uniqueWords;
    private String nonKeywords[]={" ","i","me","we","us","you","she","he","him","it","they","them","that","those","this","these","which","who","whom","whose","whichever","whoever","whomever","anybody","anyone","anything","each","either","everybody","everyone","everything","neither","nobody","no","one","nothing","someone","something","both","few","many","several","all","any","most","none","some","myself","oueselves","yourself","yourselves","himself","herself","itself","themselves","what","my","your","his","her","its","our","your","their","mine","yours","his","hers","our","their","ours","yours","theirs","them","be","am","are","is","was","were","being","can","could","do","did","does","doing","have","had","has","having","may","might","must","shall","should","will","would","a","an","the","aboard","about","above","across","after","against","along","amid","among","anti","around","as","at","before","behind","below","beneath","beside","besides","between","beyond","but","by","concerning","considering","despite","down","during","except","excepting","excluding","following","for","from","in","inside","into","minus","near","of","off","on","onto","opposite","outside","over","past","per","plus","regarding","round","save","since","than","through","to","toward","towards","under","underneath","unlike","until","up","upon","versus","via","with","within","without","and","but","or","not","also","why","where","how","while","only","very","too","for","when","wheather","been"};
    private char punctuations[]={'{','}','[',']','(',')',':',',','.','"','!','?',';','-','&','#','@','<','>','\\','+','=','%','*','~','`','/','\'','1','2','3','4','5','6','7','8','9','0'};
    private int v;
    private double alpha=1;
    SuperHashTable(){
        docMap=new TreeMap();
        docCount=0;
        uniqueWords=new LinkedList();
        v=uniqueWords.size();
    }
    
    public void addDocument(String className,String docBody){
        HashTable ht;
        className=className.toLowerCase();
        docBody=docBody.toLowerCase();
        if(!(docMap.containsKey(className))){
            ht=new HashTable(className);
        }
        else{
            ht=(HashTable)docMap.get(className);
        }
        docBody=replacePunctuations(docBody);
        String[] words=docBody.split(" ");
        
        for(int i=0;i<words.length;i++){
            String s=words[i].trim();
            if(validKeyword(s) && s.length()>1 && s!=" "){
                ht.addWord(s);
                if(!(uniqueWords.contains(s))){
                    uniqueWords.add(s);
                    v=uniqueWords.size();
                }
            }
            //System.out.println("Words: "+words[i]);
        }
        ht.incrementDocumentCount();
        docMap.put(className, ht);
        this.docCount++;
    }
    
    public double getPriorProbability(String className){
        double probability;
        HashTable ht=(HashTable)docMap.get(className);
        probability=Math.log((double)ht.getDocumentCount()/(double)docCount);
        //System.out.println("Prior: "+probability);
        return probability;
    }
    
    public double getConditionalProbability(String word,String className){
        double probability;
        HashTable ht=(HashTable)docMap.get(className);
        probability=ht.getConditionalProbability(word,this.uniqueWords.size(),alpha);
        return probability;
    }
    
    public String replacePunctuations(String s){
        for(int i=0;i<this.punctuations.length;i++){
            if(s.indexOf(punctuations[i])!=-1){
                s=s.replace(this.punctuations[i],' ');
            }
            //System.out.println(punctuations[i]);
        }
        return s;
    }
    
    public boolean validKeyword(String word){
        for(int i=0;i<this.nonKeywords.length;i++){
            if(word.equalsIgnoreCase(nonKeywords[i])){
                return false;
            }
        }
        return true;
    }
    
    public int testResult(String className,String docBody,double alpha){
        this.alpha=alpha;
        double maxProbability=-1000000,tempProbability=1;
        int j;
        String resultantClass="";
        Set set=this.docMap.entrySet();
        HashTable ht;
        Iterator i=set.iterator();
        
        className=className.toLowerCase();
        docBody=docBody.toLowerCase();
        docBody=this.replacePunctuations(docBody);
        String[] words=docBody.split(" ");
        
        tempProbability=0;
        Map.Entry me=(Map.Entry)i.next();
        //System.out.println("\n"+me.getKey()+": ");
        ht=(HashTable)docMap.get(me.getKey());
        for(j=0;j<words.length;j++){
            String s=words[j].trim();
            if(this.validKeyword(s) && s.length()>1 && !s.equalsIgnoreCase(" ")){
                //System.out.println("Temp: "+tempProbability);
                tempProbability+=this.getConditionalProbability(s,(String)me.getKey());
            }
        }
        tempProbability+=this.getPriorProbability((String)me.getKey());
        maxProbability=tempProbability;
        resultantClass=(String)me.getKey();
        
        while(i.hasNext()) {
            tempProbability=0;
            me=(Map.Entry)i.next();
            //System.out.println("\n"+me.getKey()+": ");
            ht=(HashTable)docMap.get(me.getKey());
            for(j=0;j<words.length;j++){
                String s=words[j].trim();
                if(this.validKeyword(s) && s.length()>1 && !s.equalsIgnoreCase(" ")){
                    //System.out.println("Temp: "+tempProbability);
                    tempProbability+=this.getConditionalProbability(s,(String)me.getKey());
                }
            }
            //tempProbability*=Math.pow(10,100);
            /*while(j<words.length){
                String s=words[j].trim();
                if(this.validKeyword(s) && s.length()>1 && s!=" "){
                    //System.out.println("Temp: "+tempProbability);
                    tempProbability*=this.getConditionalProbability(s,(String)me.getKey());
                }
                j++;
            }*/
            
            tempProbability+=this.getPriorProbability((String)me.getKey());
            //tempProbability*=Math.pow(10,308);
            //System.out.println("Temp Probability: "+tempProbability);
            if(tempProbability>maxProbability){
                maxProbability=tempProbability;
                resultantClass=(String)me.getKey();
            }
            //ht.show();
        }
        if(maxProbability==0){
            zeroCount++;
        }
        //System.out.println("Actual: "+className+"  Result: "+resultantClass+"  Probability: "+maxProbability);
        if(resultantClass.equalsIgnoreCase(className)){
            return 1;
        }
        else{
            return 0;
        }
    }
    
    public void show(){
        Set set=this.docMap.entrySet();
        HashTable ht;
        Iterator i=set.iterator();

        while(i.hasNext()) {
            Map.Entry me=(Map.Entry)i.next();
            System.out.println("\n"+me.getKey()+": ");
            ht=(HashTable)docMap.get(me.getKey());
            ht.show();
        }
        System.out.println("\n\nTotal Document Count: "+this.docCount);
    }
}
