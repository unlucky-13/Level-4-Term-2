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
public class Main {
    public static void main(String args[]){
        LoadData loadData = new LoadData() ;
        
//          TRAINING PHASE          ////////////////////////////////////
        LinkedList<Data> TrainData  = loadData.ReadTrainData() ;
        Network network = new Network(TrainData.get(0).in.row,TrainData.get(0).out.row ,5, 4) ;
        network.printWeightVectos(); 
    }
}
