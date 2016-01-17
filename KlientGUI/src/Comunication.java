import java.net.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.io.*;
import java.math.BigDecimal;

public class Comunication {

    public static void main(String[] argv) {
    	
        try {

    		Socket socket = new Socket("192.168.0.100", 1234);
            DataInputStream input = new DataInputStream(socket.getInputStream());
            PrintStream output = new PrintStream(socket.getOutputStream());
        	File file = new File("macierzA.txt");
	        FileService fileService = new FileService();
	        List<List<BigDecimal>> matrix =  new ArrayList<List<BigDecimal>>();
	        if(fileService.readFileIntoArray(file)){
	        	matrix = fileService.matrix;
	        	for(Iterator<List<BigDecimal>> i = matrix.iterator(); i.hasNext();){
	            	for(Iterator<BigDecimal> j = i.next().iterator(); j.hasNext();){
	            		output.print(j.next().toPlainString() + " ");
	            	}
	            	output.print("\n");
	        	}
	        }
	        
	        socket.close();

        } catch (UnknownHostException e) {
            System.out.println("Unkonw exception " + e.getMessage());

        } catch (IOException e) {
            System.out.println("IOException caught " + e.getMessage());
        } 
    }
}