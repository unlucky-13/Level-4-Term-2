/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment.pkg2;

import java.util.Map;
import java.util.TreeMap;

/**
 *
 * @author mazharul
 */
public class ClassDictionary {

    String className;
    int classID;
    TreeMap<String, Integer> dict = null;
    double  total_words ;
    public ClassDictionary(String _className, int _classID) {
        className = _className;
        classID = _classID;
        total_words = 0 ;
        dict = new TreeMap<>();
    }

    public void add_word_to_dictionary(String docBody) {
        String[] words = docBody.split(" ");
        for (String my_word : words) {
            if(my_word.length()<=1) continue ;
            if (dict.containsKey(my_word)) {
                dict.put(my_word, dict.get(my_word) + 1);
            } else {
                dict.put(my_word, 1);
            }
        }
        total_words++ ;
    }
    public boolean containsKey(String key){
        if(dict.containsKey(key)){
            return true ;
        }
        return false ;
    }
    
    public void show_dict() {

        for (Map.Entry<String, Integer> entry : dict.entrySet()) {
            String key = entry.getKey();
            Integer value = entry.getValue();
            System.out.println(key + " => " + value);
        }

    }

    double getTDF(String key) {
        double appears = 0  ;
        if(dict.containsKey(key)){
            appears = dict.get(key).intValue() ;
        }
        if(total_words==0){
            System.out.println("!!!!!!!!!!!!!!!!!!!!!!") ;
            return 0 ;
        }
        return appears/total_words ;
    }
}
