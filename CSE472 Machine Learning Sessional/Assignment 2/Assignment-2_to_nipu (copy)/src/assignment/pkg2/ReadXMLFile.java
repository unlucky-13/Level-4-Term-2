/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment.pkg2;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.LinkedList;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.TreeMap;

/**
 *
 * @author gigabyte
 */
public class ReadXMLFile {

    String filename = "";
    private static final String html_tag_list_filename = "html_tag_list.txt";
    private static LinkedList<String> html_tag_list;
    private static final String stop_word_filename = "Words.txt";
    private static LinkedList<String> stop_words_list;
    private char punctuations[] = {'{', '}', '[', ']', '(', ')', ':', ',', '.', '"', '!', '?', ';', '-', '&', '#', '@', '<', '>', '\\', '+', '=', '%', '*', '~', '`', '/', '\''};
    private int row_read; // how many rows will be read
    private int fileID;
    private int start ;
    ReadXMLFile(String _filename, int _row_read, int _fileID,int _start) {
        filename = _filename;
        row_read = _row_read;
        fileID = _fileID;
        start=_start ;
        html_tag_list = new LinkedList<>();
        stop_words_list = new LinkedList<>();
        //System.out.println("Parsing file ->" + filename);
        try {

            BufferedReader bf = new BufferedReader(new FileReader(stop_word_filename));
            String line = null;
          //  int count= 0 ;
            while ((line = bf.readLine()) != null) {
               // count++ ;
              //  if(count<start) continue ; 
                StringTokenizer stk = new StringTokenizer(line, ",");
                while (stk.hasMoreTokens()) {
                    String word = (String) stk.nextElement();
                    stop_words_list.add((String) word.subSequence(1, word.length() - 1));
                }
            }
            bf.close();
            bf = new BufferedReader(new FileReader(html_tag_list_filename));
            line = null;
            while ((line = bf.readLine()) != null) {
                html_tag_list.add(line);
            }
        } catch (Exception ex) {
            System.out.println("can not read the  file " + stop_word_filename + " or file -> " + html_tag_list_filename);
        }
    }

    public boolean add_it(String word) {
        if (word.length() <= 1) { // 
            return false;
        }
        for (String stop_word : stop_words_list) {
            if (word.equals(stop_word)) {
                //System.out.println("this is a stop word");
                return false;
            }
        }
        
         for (String html_tags : html_tag_list) {
            if (word.equals(html_tags)) {
                //System.out.println("this is a stop word");
                return false;
            }
        }
        return true;
    }

    public String replacePunctuations(String s) {
        for (int i = 0; i < this.punctuations.length; i++) {
            if (s.indexOf(punctuations[i]) != -1) {
                s = s.replace(this.punctuations[i], ' ');
            }
            //System.out.println(punctuations[i]);
        }
        return s;
    }

    LinkedList<ClassDictionary> read() {
        LinkedList<ClassDictionary> dict_list = new LinkedList<>();
        int count=0 ;
        try {
         //   System.out.println("Row Read is ->" + row_read);
            
            String inputFile = filename;
            BufferedReader br = new BufferedReader(new FileReader(inputFile));
           
            String line;
            
            while ((line = br.readLine()) != null && dict_list.size()<row_read) {
                count++ ;
                if(count<start) continue;
                    
// new sample data
                ClassDictionary classDictionary = new ClassDictionary(filename, fileID);
                if (line.indexOf("<row") != -1) {
                    String[] parts = line.split("&lt;p&gt;");
                    String input = "";
                    for (int j = 1; j < parts.length; j++) {
                        String[] temp = parts[j].split("&lt;/p&gt;");
                        temp[0] = temp[0].trim().toLowerCase();
                        temp[0] = replacePunctuations(temp[0]);
                        temp[0] = temp[0].replaceAll("\\s+", " "); //all whitespaces and non-visible characters 
                        temp[0] = temp[0].replace("(^-?0\\.[0-9]*[1-9]+[0-9]*$)|(^-?[1-9]+[0-9]*((\\.[0-9]*[1-9]+[0-9]*$)|(\\.[0-9]+)))|(^-?[1-9]+[0-9]*$)|(^0$){1}", " ") ; // exclude all numbers
                        // numbers are also excluded codes to be written
                        // System.out.println(temp[0]+"-----") ;
                        String[] words = temp[0].split(" ");
                        for (int i = 0; i < words.length; i++) {
                            //  System.out.println(words[i]) ;
                            if (add_it(words[i])) {
                                classDictionary.add_word_to_dictionary(words[i]);
                            }
                        }
                    }
                    if(classDictionary.dict.size()!=0) dict_list.add(classDictionary);
                }
            }
            //System.out.println(inputFile+" done!"+" Line count= "+count);
        } catch (Exception ex) {
            System.out.println("can not read file->" + filename);
        }
      //  System.out.println(dict_list.size());
        return dict_list;
    }

    public static void main(String args[]) {

        ReadXMLFile readXMLFile = new ReadXMLFile("Data/Training/Anime.xml", 50,0,0);
        /*
        for(String w: stop_words_list){
            System.out.println(w);
        }
         */
        LinkedList<ClassDictionary> dictionaryList = readXMLFile.read();
        /*
        for (int i = 0; i < dictionaryList.size(); i++) {
            dictionaryList.get(i).show_dict();
            System.out.println("----------------------------------");
        }
         */
    }
}
