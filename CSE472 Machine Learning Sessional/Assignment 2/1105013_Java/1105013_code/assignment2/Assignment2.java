/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment2;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.LinkedList;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.TreeMap;

/**
 * @author gigabyte
 */
public class Assignment2 {

    /**
     * @param args the command line arguments
     */
    TreeMap<String, Integer> dictionary;
    String excludeWords[] = {
        "a", "an", "the", // article
        "very", // adverb
        "was", "were", "am", "is", "are", "has", "had", "been", "will", "would", "could", "can", "shall", "should", // auxilary verbwords
        "on", "up", "onto", "with", "at", "from", "into", "against", "upon", "in", // preposition
        "i", "we", "us", "i'm", "if", "your"
    };
    String dir = null;

    public Assignment2() {
        dictionary = null;
        dir = "C:\\Users\\gigabyte\\Documents\\NetBeansProjects\\Assignment2\\Data\\";
    }

    boolean DoNotExcludIT(String str) {
        for (int i = 0; i < excludeWords.length; i++) {
            if (str.equals(excludeWords[i])) {
                return false;
            }
        }
        return true;
    }

    public LinkedList<TreeMap<String, Integer>> Parse(LinkedList<String> fileNames) {
        LinkedList<TreeMap<String, Integer>> dicList = new LinkedList<TreeMap<String, Integer>>();
        TreeMap<String, Integer> Temp = new TreeMap<>();
        Temp.put("-1",-1) ;
        for (int i = 0; i < fileNames.size(); i++) {
            dictionary = new TreeMap<String, Integer>();
            String fileName = dir + "Training\\" + fileNames.get(i) + ".xml";
            System.out.println("---Parsing-----" + fileName);
            LinkedList<TreeMap<String, Integer>> dictionaryList = new ReadXMLFile(fileName).read();
            dicList.addAll(dictionaryList) ;
            dicList.add(Temp) ;
        }
        return dicList;
    }

    public LinkedList<String> AddFiles() {
        try {
            LinkedList<String> fileNames = new LinkedList<>();
            FileReader fr = new FileReader(new File(dir + "topics.txt"));
            BufferedReader bf = new BufferedReader(fr);
            String line = "";
            while ((line = bf.readLine()) != null) {
                fileNames.add(line);
            }
            return fileNames;
        } catch (Exception ex) {
            System.out.println(ex.toString());
            return null;
        }
    }

    public int KNN(LinkedList<TreeMap<String, Integer>> TrainDictionary, TreeMap<String, Integer> TestDic,int K) {
        int type = -1;
        int TestVal;
        int k=0 ;
        int minimum_hamming_distance[] = new int[K+1] ;
        int types[] = new int[K+1] ;
        for(int i=0;i<K;i++){
            minimum_hamming_distance[i]=Integer.MAX_VALUE ;
            types[i]=-1 ;
        }
        //System.out.println(TrainDictionary.size()) ;
        for (int i = 0; i < TrainDictionary.size(); i++) {
           // System.out.println(i) ;
            int temp = 0;
            TreeMap<String, Integer> TrainDic = TrainDictionary.get(i);
          //  System.out.println(TrainDic.size()+" ----------------"+TestDic.size()) ;
            if(!TrainDic.isEmpty() && TrainDic.firstEntry().getKey()=="-1"){
              //  System.out.println("shifting") ;
                k++ ;
                continue;
            }
            for (Map.Entry<String, Integer> entry : TrainDic.entrySet()) {
                String key = entry.getKey();
                if (TestDic.containsKey(key)) {
                    TestVal = 0;
                } else {
                    TestVal = 1;
                }
                temp += TestVal;
            }
            // checking for words that are in the test but not in train
            for (Map.Entry<String, Integer> entry : TestDic.entrySet()) {
                String key = entry.getKey();

                if (TrainDic.containsKey(key)) {
                    TestVal = 0;
                } else {
                    TestVal = 1;
                }
                temp += TestVal;
            }
            for(int I=0;I<K;I++){
                if(minimum_hamming_distance[I]>temp){
                    minimum_hamming_distance[I]=temp ;
                    types[I]=k ;
                    break ;
                }
            }
        }
       // System.out.println();
       int count_[] = new int [5] ;
       for(int i=0;i<5;i++){
           count_[i]=0 ;
       }
       for(int i=0;i<K;i++){
           if(types[i]!=-1) count_[types[i]]++ ;
       }
       type=-1 ;
       int Maxi=0 ;
       for(int i=0;i<3;i++){
           if(Maxi<count_[i]){
               type=i ;
               Maxi=count_[i] ;
           }
       }
        return type;
    }

    public int Euclidian(LinkedList<TreeMap<String, Integer>> TrainDictionary, TreeMap<String, Integer> TestDic,int K) {
        int type = -1;
        int TestVal;
        int k=0 ;
        int minimum_hamming_distance[] = new int[K+1] ;
        int types[] = new int[K+1] ;
        for(int i=0;i<K;i++){
            minimum_hamming_distance[i]=Integer.MAX_VALUE ;
            types[i]=-1 ;
        }
        
        for (int i = 0; i < TrainDictionary.size(); i++) {
            int temp = 0;
            TreeMap<String, Integer> TrainDic = TrainDictionary.get(i);
           // System.out.println(TrainDic.size()+" -------------"+TestDic.size()) ;
            if(TrainDic.firstEntry().getKey()=="-1"){
               // System.out.println("shifting") ;
                k++ ;
                continue;
            }
            for (Map.Entry<String, Integer> entry : TrainDic.entrySet()) {
                String key = entry.getKey();
                if (TestDic.containsKey(key)) {
                    TestVal = TrainDic.get(key).intValue() - TestDic.get(key).intValue();
                } else {
                    TestVal = TrainDic.get(key).intValue();
                }
                temp += (TestVal * TestVal);
            }
            for (Map.Entry<String, Integer> entry : TestDic.entrySet()) {
                String key = entry.getKey();
               
                if (TrainDic.containsKey(key)) {
                    TestVal = 0;
                } else {
                    TestVal = TestDic.get(key).intValue();
                }
                temp += (TestVal * TestVal);
            }
            for(int I=0;I<K;I++){
                if(minimum_hamming_distance[I]>temp){
                    minimum_hamming_distance[I]=temp ;
                    types[I]=k ;
                    break ;
                }
            }
        }
        int count_[] = new int [5] ;
       for(int i=0;i<5;i++){
           count_[i]=0 ;
       }
       for(int i=0;i<K;i++){
           if(types[i]!=-1) count_[types[i]]++ ;
       }
       type=-1 ;
       int Maxi=0 ;
       for(int i=0;i<3;i++){
           if(Maxi<count_[i]){
               type=i ;
               Maxi=count_[i] ;
           }
       }
        return type;
    }

    public void TestData(LinkedList<TreeMap<String, Integer>> TrainDictionaryList,int K) {

        double wrong = 0;
        double right = 0;
        LinkedList<String> fileNames = new Assignment2().AddFiles();
        for (int i = 0; i < fileNames.size(); i++) {
            String fileName = dir + "Test\\" + fileNames.get(i) + ".xml";
            System.out.println("Testing " + fileName);

            String line ;
            TreeMap<String, Integer> testDict = new TreeMap<>();
            try {
                BufferedReader bf = new BufferedReader(new FileReader(new File(fileName)));
               
                while ((line = bf.readLine()) != null) {
                    int idx1 = line.indexOf("Body") + 6;
                    int idx2 = line.indexOf("OwnerUserId") - 2;
                    if (idx2 < idx1)  continue ; 
                        StringTokenizer strToken = new StringTokenizer(line.substring(idx1, idx2), " \n");
                        while (strToken.hasMoreTokens()) {
                            String word = strToken.nextToken();
                            if (testDict.get(word) == null) { //this is a new entry
                                testDict.put(word, 1);
                            } else {
                                int value = testDict.get(word).intValue();
                                testDict.put(word, value + 1);
                            }
                        }
                    
                      //  System.out.println("Hello") ;
                        int res=KNN(TrainDictionaryList, testDict,K) ;
                        testDict.clear();
                        if(res==i) right++ ;
                        else wrong++ ;
                        System.out.println(right + " " + wrong);
                      //  break ;
                }

            } catch (Exception ex) {
                System.out.println("Hello"+ex.toString()) ;
            }
            System.out.println(right + " " + wrong);
          //  break ;
        }
        
    }

    public static void main(String[] args) {
        // TODO code application logic heree

        Assignment2 assignment2 = new Assignment2();
        LinkedList<String> fileList = assignment2.AddFiles();
        LinkedList<TreeMap<String, Integer>> TrainDictionarList = assignment2.Parse(fileList);
        /*
        for (int i = 0; i < TrainDictionarList.size(); i++) {
            System.out.println("Dictory for file -> " + fileList.get(i));
            TreeMap<String, Integer> dictionary = TrainDictionarList.get(i);
            for (Map.Entry<String, Integer> entry : dictionary.entrySet()) {
                String key = entry.getKey();
                Integer value = entry.getValue();
                System.out.println(key + " => " + value);
            }
        }
         */
        assignment2.TestData(TrainDictionarList,5);

    }
}
