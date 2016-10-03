package assignment.pkg2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.Map;
import java.util.TreeMap;

/**
 *
 * @author Mazharul
 */
public class KNN {

    /**
     * @param args the command line arguments
     */
    private static  TreeMap<String,Double> TDF_value_holders  ;
    private static TreeMap<String, Integer> dictionary;
    private static final String dir = "Data/";
    private static final String topicListFileName = "topics.txt";
    public static LinkedList<String> topicsList = null;
    public static final double PI = Math.acos(-1) ;


    KNN() {
        dictionary = null;
        topicsList = new LinkedList<String>();
        TDF_value_holders = new TreeMap<>() ;
        // Add files name 
        try {

            BufferedReader bf = new BufferedReader(new FileReader(dir + topicListFileName));
            String Line;
            while ((Line = bf.readLine()) != null) {
                topicsList.add(Line);
            }
        } catch (Exception ex) {
            System.out.println("can not read file -> " + topicListFileName);
        }
    }
        private static double getIDF(LinkedList<ClassDictionary> TrainDictionary, String key) {
        if(TDF_value_holders.containsKey(key)){
            return TDF_value_holders.get(key).doubleValue() ;
        }
        double count1=0 ;
        for(ClassDictionary classDictionary: TrainDictionary){
            if(classDictionary.dict.containsKey(key)) count1++ ;
        }
        
        double count2 = TrainDictionary.size() ;
        double IDF = Math.log(count2/(1+count1)) ; // same for bot
        TDF_value_holders.put(key, IDF) ;
        return IDF ;
    }
    public static LinkedList<ClassDictionary> Parse(LinkedList<String> fileNames,int start) {

        LinkedList<ClassDictionary> dicList = new LinkedList<ClassDictionary>();

        for (int i = 0; i < fileNames.size(); i++) {
            dictionary = new TreeMap<String, Integer>();
            //String fileName = dir + "Training\\" + fileNames.get(i) + ".xml";
            String fileName = dir + "Training/" + fileNames.get(i) + ".xml";
            //System.out.println("---Parsing-----" + fileName);
            LinkedList<ClassDictionary> Temp = new ReadXMLFile(fileName, 100,i,start).read();
            dicList.addAll(Temp);
        }
        return dicList;
    }

    public static int KNN(LinkedList<ClassDictionary> TrainDictionary, ClassDictionary TestDic, int K) {
        // System.out.println(K) ;
        int type;
        int TestVal;
        Pair[] minimum_hamming_distance = new Pair[K + 1];
        for (int i = 0; i < K; i++) {
            minimum_hamming_distance[i] = new Pair(Double.MAX_VALUE, -1);
        }
        //System.out.println(TrainDictionary.size()) ;
        for (int i = 0; i < TrainDictionary.size(); i++) {
            // System.out.println(i) ;
            int temp = 0;
            TreeMap<String, Integer> TrainDic = TrainDictionary.get(i).dict;
            //  System.out.println(TrainDic.size()+" ----------------"+TestDic.size()) ;
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
            for (Map.Entry<String, Integer> entry : TestDic.dict.entrySet()) {
                String key = entry.getKey();

                if (TrainDic.containsKey(key)) {
                    TestVal = 0;
                } else {
                    TestVal = 1;
                }
                temp += TestVal;
                //  System.out.println(temp);
            }
            //   System.out.println(temp) ;
            minimum_hamming_distance[K] = new Pair(temp, TrainDictionary.get(i).classID);
            Arrays.sort(minimum_hamming_distance, new CustomComparator());
        }

        //    for(int I=0;I<K;I++){
        //        System.out.print(minimum_hamming_distance[I].value+" ");
        //    }
        //   System.out.println("");
        //   for(int I=0;I<K;I++){
        //       System.out.print(minimum_hamming_distance[I].type+" ");
        //    }
        //   System.out.println("");
        // System.out.println();
        int count_[] = new int[topicsList.size()];
        for (int i = 0; i < topicsList.size() ; i++) {
            count_[i] = 0;
        }
        for (int i = 0; i < K; i++) { // total topic 4 ta
            if (minimum_hamming_distance[i].type != -1) {
                count_[minimum_hamming_distance[i].type]++;
            }
        }
        type = -1;
        int Maxi = 0;
        for (int i = 0; i < topicsList.size(); i++) {
            if (Maxi < count_[i]) {
                type = i;
                Maxi = count_[i];
            }
        }
        //System.out.println(Maxi);
        return type;
    }

    public static int Euclidian(LinkedList<ClassDictionary> TrainDictionary, ClassDictionary TestDic, int K) {
        int type, TestVal;
        Pair[] minimum_eucldian_distance = new Pair[K + 1];
        for (int i = 0; i < K; i++) {
            minimum_eucldian_distance[i] = new Pair(Double.MAX_VALUE, -1);
        }

        for (int i = 0; i < TrainDictionary.size(); i++) {
            int temp = 0;
            TreeMap<String, Integer> TrainDic = TrainDictionary.get(i).dict;
            for (Map.Entry<String, Integer> entry : TrainDic.entrySet()) {
                String key = entry.getKey();
                if (TestDic.containsKey(key)) {
                    TestVal = TestDic.dict.get(key).intValue() - TrainDic.get(key).intValue();
                } else {
                    TestVal = TrainDic.get(key).intValue();
                }
                temp += (TestVal * TestVal);
            }
            // checking for words that are in the test but not in train
            for (Map.Entry<String, Integer> entry : TestDic.dict.entrySet()) {
                String key = entry.getKey();
                if (TrainDic.containsKey(key)) {
                    TestVal = 0; // already considered
                } else {
                    TestVal = TestDic.dict.get(key).intValue();
                }
                temp += (TestVal * TestVal);
            }
            // System.out.println(temp);
            minimum_eucldian_distance[K] = new Pair(temp, TrainDictionary.get(i).classID);
            Arrays.sort(minimum_eucldian_distance, new CustomComparator());
        }

        int count_[] = new int[topicsList.size()];
        for (int i = 0; i < topicsList.size(); i++) {
            count_[i] = 0;
        }
        /*
        for (int I = 0; I < K; I++) {
            System.out.print(minimum_eucldian_distance[I].value + " ");
        }
        System.out.println("");
        for (int I = 0; I < K; I++) {
            System.out.print(minimum_eucldian_distance[I].type + " ");
        }
        System.out.println("");
        */
        //System.out.println();
        for (int i = 0; i < K; i++) { // total topic 4 ta
            if (minimum_eucldian_distance[i].type != -1) {
                count_[minimum_eucldian_distance[i].type]++;
            }
        }
        type = -1;
        int Maxi = 0;
        for (int i = 0; i < topicsList.size(); i++) {
            if (Maxi < count_[i]) {
                type = i;
                Maxi = count_[i];
            }
        }
      //  System.out.println(type);
        return type;
    }

    public static int TDF_IDF(LinkedList<ClassDictionary> TrainDictionary, ClassDictionary TestDic, int K) {
        int type;
        Pair[] minimum_eucldian_distance = new Pair[K + 1];
        for (int i = 0; i < K; i++) {
            minimum_eucldian_distance[i] = new Pair(Double.MAX_VALUE, -1);
        }

        for (int i = 0; i < TrainDictionary.size(); i++) {
            int temp = 0;
            TreeMap<String, Integer> TrainDic = TrainDictionary.get(i).dict;
            
            
            double crossValue=0 ;
            double Len1 = 0 ;
            double Len2 = 0 ;
           // System.out.println(TrainDictionary.size()) ;
            for (Map.Entry<String, Integer> entry : TrainDic.entrySet()) {
                String key = entry.getKey();
                double IDF1 = getIDF(TrainDictionary,key) ; 
                double TDF1 = TrainDictionary.get(i).getTDF(key) ;
                double IDF2=IDF1 ;
                double TDF2=TestDic.getTDF(key) ; 
               // System.out.println(IDF1+" "+IDF2+" "+TDF1+" "+TDF2) ;
               //  System.out.println(IDF1*IDF2*TDF1*TDF2) ;
                crossValue += (IDF1*IDF2*TDF1*TDF2) ;
                Len1+= entry.getValue()*entry.getValue() ;
            }
          //  System.out.println(i);
            // consider the words which are not in the Train Dic but are in the Test Dic
            for (Map.Entry<String, Integer> entry : TestDic.dict.entrySet()) {
                String key = entry.getKey();
                Len2+=entry.getValue()*entry.getValue() ;
            }    
            Len1 = Math.sqrt(Len1) ;
            Len2 = Math.sqrt(Len2) ;
        //    System.out.println(crossValue+" "+Len1+" "+Len2) ;
         //   System.out.println(crossValue/(Len1*Len2)) ;
            double angle = ((crossValue/(Len1*Len2))) ;
            
            angle  = Math.acos(angle) ; 
          //  System.out.println(angle);
            minimum_eucldian_distance[K] = new Pair(angle,TrainDictionary.get(i).classID);
            Arrays.sort(minimum_eucldian_distance, new CustomComparator());
           // break ;
        }

        int count_[] = new int[topicsList.size()];
        for (int i = 0; i < topicsList.size() ; i++) {
            count_[i] = 0;
        }
        /*
        for (int I = 0; I < K; I++) {
            System.out.print(minimum_eucldian_distance[I].value + " ");
        }
        System.out.println("");
        for (int I = 0; I < K; I++) {
            System.out.print(minimum_eucldian_distance[I].type + " ");
        }
        System.out.println("");
        System.out.println();
        */
        for (int i = 0; i < K; i++) { // total topic 4 ta
            if (minimum_eucldian_distance[i].type != -1) {
                count_[minimum_eucldian_distance[i].type]++;
            }
        }
        type = -1;
        int Maxi = 0;
        for (int i = 0; i < topicsList.size(); i++) {
            if (Maxi < count_[i]) {
                type = i;
                Maxi = count_[i];
            }
        }
        //System.out.println(type);
        return type;
    }

    public static double TestData(LinkedList<ClassDictionary> TrainDictionaryList, int K,int algo,int start) {

        double wrong = 0;
        double right = 0;
        //System.out.println("YES");
        for (int i = 0; i < topicsList.size(); i++) {
            String fileName = dir + "Test/" + topicsList.get(i) + ".xml";
            //    System.out.println("Testing Data for -> " + fileName);
            LinkedList<ClassDictionary> dict_list = new ReadXMLFile(fileName, 50, i,0).read();
            // System.out.println("Dict size -> "+dict_list.size()) ;
            //System.out.println("parsing done!!!!!") ;
            for (ClassDictionary testData : dict_list) {
                // here are the testing
                int type ;
                if(algo==0) type= KNN(TrainDictionaryList, testData, K);
                else if(algo==1) type= Euclidian(TrainDictionaryList, testData, K) ;
                else type = TDF_IDF(TrainDictionaryList, testData, K) ;
                //  System.out.println(type) ;
                if (type == testData.classID) {
                    right++;
                } else {
                    wrong++;
                }
               // System.out.println(right+" "+wrong);
            }
            //System.out.println(right+" "+wrong);
        }
        return (right / (right + wrong));
    }

    public static double[] GatherData(int Runs) {
        // TODO code application logic heree
        double[] ret = new double[Runs+1];
        KNN knn = new KNN();
         LinkedList<ClassDictionary> TrainDictionaryList =new LinkedList<>()  ;
        /*
        
        LinkedList<ClassDictionary> TrainDictionaryList = knn.Parse(knn.topicsList,0);
        /*
        for(ClassDictionary t:TrainDictionaryList){
            System.out.println(t.classID) ;
        }
         */
        double bestAccuracy =0.81  ;
        int bestK =43 ;
        int bestAlgo =2 ;
        /*
        for(int algo=0;algo<3;algo++){
            // trinary search
            int lo=0 ;
            int hi= TrainDictionaryList.size()-1; 
            while(lo<=hi){
                int K1 = lo+(hi-lo)/3 ;
                int K2 = hi-(hi-lo)/3 ;
                double accuracyK1 = knn.TestData(TrainDictionaryList, K1,algo,0);
                double accuracyK2 = knn.TestData(TrainDictionaryList, K1,algo,0);
                if(accuracyK1<accuracyK2){
                    lo=K1 ;
                }else{
                    hi=K2 ;
                }
            }
               double accuracy = knn.TestData(TrainDictionaryList, hi,algo,0);
               if(accuracy>bestAccuracy){
                   bestAccuracy=accuracy ;
                   bestAlgo=algo ;
                   bestK=hi ;
               }
        }
        */
  //      double accuracy =  knn.TestData(TrainDictionaryList,60,2);
//        System.out.print(accuracy);
        /*
        for(int algo=0;algo<3;algo++){
            for(int k=1;k<=100;k++){
                
                double accuracy =  knn.TestData(TrainDictionaryList, k,algo,0);
                if(accuracy>bestAccuracy){
                    bestAlgo=algo ;
                    bestK = k ;
                    bestAccuracy  = accuracy ;
                }
                System.out.println(accuracy);
            }
        }

       System.out.println(bestK+" "+bestAccuracy+" "+bestAlgo);
       */
       /* 
       ret[0] = .65;
        ret[1] = .023;
        /*
       */
       
       ret = new double[Runs+1] ;
       for(int runs=0;runs<=50;runs++){
            TrainDictionaryList.clear(); 
            TrainDictionaryList = knn.Parse(topicsList,runs*100) ;
            ret[runs] = TestData(TrainDictionaryList, bestK,bestAlgo,0) ;
       }
       /*for(int i=0;i<Runs;i++){
           System.out.println(i+" "+ret[i]);
       }*/
       double[] returnVal=new double[2];
       returnVal[0]=0;
       returnVal[1]=0;
       for(int i=0;i<Runs;i++){
           returnVal[0]+=ret[i];
       }
       returnVal[0]/=(double)Runs;
       for(int i=0;i<Runs;i++){
           returnVal[1]+=Math.pow((ret[i]-returnVal[0]),2);
       }
       returnVal[1]/=(double)(Runs-1);
       returnVal[1]=Math.sqrt(returnVal[1]);
       return returnVal;

    }

    public static void main(String args[]) {
        KNN knn = new KNN();
        knn.GatherData(50);
    }
}

class Pair {

    double  value ;
    int type;

    public Pair(double value, int type) {
        this.value = value;
        this.type = type;
    }
}

class CustomComparator implements Comparator<Pair> { // for sorting the Pair class
    @Override
    public int compare(Pair o1, Pair o2) {
        if (o1.value > o2.value) {
            return 1;
        }
        return -1;
    }
}
