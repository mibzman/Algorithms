import java.io.*;
import java.util.*;
import java.io.File;

/**
	//this program compares two files pixel by pixel
*/
public class MyDiff 
{
   private int[] rowN = new int[2];
   private int[] columnN = new int[2];     //the image has rowN rows and columnN columns
   private int[] maxG = new int[2];              //the grey scale level max: maxG
   private int[][][] img = new int[2][][];  //pixel values of the image  
 	
	/** 
		read the image file
		@param filename : the image filename
      @param fileID : the first file =0
	*/	
   private void readImage(String filename, int fileID)
   {			 
      String header = ""; //store pgm image header in header
      try {
         Scanner input = new Scanner(new File(filename));
      	
         if (input.hasNext("P2")) 
            header += input.nextLine()+"\n";
         else
            throw new IOException();
      			
         if (input.hasNext("#.*")) 
            header += input.nextLine()+"\n";
      	     	
         columnN[fileID] = input.nextInt();
         rowN[fileID] = input.nextInt();
         maxG[fileID] = input.nextInt();

         img[fileID] = new int[rowN[fileID]][columnN[fileID]];
         for (int i=0; i<rowN[fileID]; i++) 
         for (int j=0; j< columnN[fileID]; j++) 
            img[fileID][i][j] = input.nextInt();
         
         input.close();
      }
      catch (FileNotFoundException e) {
         System.out.println("warning: file not found");
      }
      catch (IOException e) {
         System.out.println("warning: file format error");
      }
      catch (NoSuchElementException e) {
         System.out.println("warning: NoSuchElementException");
      }
   }	
   
   private boolean sameImages() {
      if (rowN[0]!=rowN[1] || columnN[0]!=columnN[1] || maxG[0]!=maxG[1]){
         System.out.println("Size different!");
         return false;
      }
      for (int i=0; i<rowN[0]; i++) {
         for (int j=0; j< columnN[0]; j++) {
            if (img[0][i][j] != img[1][i][j]) {
              System.out.println("[0][" + i + "][" + j + "] = " + img[0][i][j]);
              System.out.println("[1][" + i + "][" + j + "] = " + img[1][i][j]);
              return false;
            }
        } 
     }           
      return true;
   }
   
	public static void main(String[] args) throws IOException {	
      MyDiff imgComp = new MyDiff();
      if (args.length==2) {	
         imgComp.readImage(args[0], 0);
         imgComp.readImage(args[1], 1);
         if(imgComp.sameImages())
            System.out.println("same!");
         else
            System.out.println("different!");
      }
      else {
         System.out.println("Correct call format: a.exe your.pgm mine.pgm");
      }
   }
}