import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;


public class FileService {
	List<List<Float>> matrix = new ArrayList<List<Float>>();
	public void readFileIntoArray(File file){
		Scanner inFile;
		try {
			inFile = new Scanner(file);
			while (inFile.hasNextLine()) {
				String currentLine = inFile.nextLine().replace(',', '.');
				List<String> list = new ArrayList<String>(Arrays.asList(currentLine.split(" ")));
			    Float[] row = new Float[list.size()];

			    for (int i = 0; i < list.size(); i++)
			    {
			        row[i] = Float.parseFloat(list.get(i));
			    }
			    matrix.addAll(Arrays.asList(Arrays.asList(row)));
			}
			for(int i = 0; i < matrix.size(); i++){
		    	System.out.println(matrix.get(i));
		    }
			inFile.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch(Exception e){
			Error error = new Error();
			error.open("Error in file " + file.getAbsolutePath() + " line " + (matrix.size() + 1));
			System.out.println("Error in line " + (matrix.size() + 1));
		}
	}
}
