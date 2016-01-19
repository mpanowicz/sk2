import java.net.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.io.*;
import java.math.BigDecimal;

public class Comunication {

    public void connect(String address, Integer port, String matrixA, String matrixB, String matrixC){
        try {

    		Socket socket = new Socket(address, port);
            DataInputStream input = new DataInputStream(socket.getInputStream());
            PrintStream output = new PrintStream(socket.getOutputStream());
            sendFile(output, matrixA, false);
            sendFile(output, matrixB, true);
            readFile(input, matrixC);
	        socket.close();

        } catch (UnknownHostException e) {
            System.out.println("Unkonw exception " + e.getMessage());
            Error error = new Error();
            error.open(e.getMessage());

        } catch (IOException e) {
            System.out.println("IOException caught " + e.getMessage());
            Error error = new Error();
            error.open(e.getMessage());
        } 
    }
    
    private void sendFile(PrintStream output, String path, Boolean transpose){
    	File file = new File(path);
        FileService fileService = new FileService();
        List<List<BigDecimal>> matrix =  new ArrayList<List<BigDecimal>>();
        if(fileService.readFileIntoArray(file)){
        	if(transpose){
        		fileService.transpose();
        	}
        	matrix = fileService.matrix;
        	for(Iterator<List<BigDecimal>> i = matrix.iterator(); i.hasNext();){
            	for(Iterator<BigDecimal> j = i.next().iterator(); j.hasNext();){
            		output.print(j.next().toPlainString() + " ");
            	}
            	output.print("\n");
        	}
        	output.print("e");
        }
    }
    
    @SuppressWarnings("deprecation")
	private void readFile(DataInputStream input, String path){
    	PrintWriter matrixC;
		try {
			matrixC = new PrintWriter(path);
			String line = "";
	        while((line = input.readLine()) != null && line.length() > 0){
	        	matrixC.println(line);
	        }
	        matrixC.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			Error error = new Error();
            error.open(e.getMessage());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			Error error = new Error();
            error.open(e.getMessage());
		}
    }
}