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
 *
 * @author gigabyte
 */
public class ReadXMLFile {

    String filename = "";

    ReadXMLFile(String _filename) {
        filename = _filename;
        System.out.println(filename);
    }

    LinkedList<TreeMap<String, Integer>> read() {

        int id = 0;
        String line = "";
        LinkedList<TreeMap<String, Integer>> DictionList = new LinkedList<TreeMap<String, Integer>>();
        try {
            
            BufferedReader br = new BufferedReader(new FileReader(new File(filename)));
            while ((line = br.readLine()) != null) {
                //     System.out.println(line);
                //  id++;
                //System.out.println(id);
                TreeMap<String, Integer> dictionary = new TreeMap<>();
                int idx1 = line.indexOf("Body") + 6;
                int idx2 = line.indexOf("OwnerUserId") - 2;
                // System.out.println(line.length());
                //System.out.println(idx1+" "+idx2) ;
                if (idx2 < idx1) {
                    continue;
                }
                StringTokenizer strToken = new StringTokenizer(line.substring(idx1, idx2), " ");
                while (strToken.hasMoreTokens()) {
                    String word = strToken.nextToken();
                    if (dictionary.get(word) == null) { //this is a new entry
                        dictionary.put(word, 0);
                    } else {
                        int value = dictionary.get(word).intValue();
                        dictionary.put(word, value + 1);
                    }
                }
                //System.out.println("adding "+dictionary.size());
                DictionList.add(new TreeMap<String,Integer>(dictionary));
                dictionary.clear();
            }
            
        } catch (Exception ex) {
            System.out.println(line + " " + id + "\n" + ex.toString());
            return DictionList;
        }
        return DictionList;
    }

    public static void main(String args[]) {

        ReadXMLFile readXMLFile = new ReadXMLFile("Anime.xml");
        LinkedList<TreeMap<String, Integer>> dictionaryList = readXMLFile.read();
        for (int i = 0; i < dictionaryList.size(); i++) {
            TreeMap<String, Integer> dictionary = dictionaryList.get(i);
           System.out.println(dictionary.size()) ;
            for (Map.Entry<String, Integer> entry : dictionary.entrySet()) {
                String key = entry.getKey();
                Integer value = entry.getValue();
                System.out.println(key + " => " + value);
            }
        }
    }
}
