
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.Raster;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import sun.applet.AppletResourceLoader;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author User
 */
public class BruteForce {
    public static void main(String args[]){
        new BruteForce().Run() ;
    }
    public void Run(){
        int [][] test = getImage("test.bmp") ;
        /*
        for (int[] test1 : test) {
            for (int j = 0; j < test1.length; j++) {
                System.out.printf("%d ", test1[j]);
            }
            System.out.println("");
        }
        */
        System.out.println(test.length);
        
    }
    public int [][] getImage(String filename){
        try{
            Image image = ImageIO.read(new File(filename));
            BufferedImage img = new BufferedImage(image.getWidth(null), image.getHeight(null), BufferedImage.TYPE_BYTE_GRAY);
            Raster raster = img.getData() ;
            int w = img.getWidth();
            int h = img.getHeight();
            int[][] array = new int[w][h];
            for (int j = 0; j < w; j++) {
                for (int k = 0; k < h; k++) {
                    array[j][k] =  (array.getRGB(j, k) >> 16) & 0xFF
                }
            }
            return array ;
        }catch (Exception ex){
            System.out.println("Exception in reading image file");
        }
            return null ;
    }
}
