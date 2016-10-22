/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ann;

import java.util.LinkedList;

/**
 *
 * @author mazharul
 */
public class Network {
    
    public static void main(String args[]){
                LoadData ld = new LoadData() ;
                 Data[] testData = ld.ReadTestData() ;
                for(int i=0;i<1;i++){
                    testData[i].in.print(); 
                     testData[i].out.print(); 
                }
    }
}
