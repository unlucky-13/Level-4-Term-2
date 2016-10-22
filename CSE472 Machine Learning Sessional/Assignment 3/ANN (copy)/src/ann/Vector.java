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
public class Vector {
    int  row,col ;
    Double [][]  Matrix ;
    Vector(){
        
    }
    Vector(int _row,int _col,LinkedList<Double>data){
        row = _row ;
        col = _col ;
        Matrix = new Double [row][col] ;
        int I=0,J=0 ;
        for(int i=0;i<row*col;i++){
            Matrix[I][J] = data.get(i) ;
            J++ ;
            if(J==col){
                J=0 ;
                I++ ;
            }
        
        }
    }
    public void print(){
        System.out.println("Row -> "+row+" Col -> "+col) ;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                System.out.print(Matrix[i][j]) ;
                System.out.print(" ") ;
            }
            System.out.println() ;
        }
    }
}
