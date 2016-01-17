import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;


public class FileService {
	List<List<BigDecimal>> matrix = new ArrayList<List<BigDecimal>>();
	int columns;
	int rows;
	//Read file to matrix
	public boolean readFileIntoArray(File file){
		Scanner inFile;
		try {
			inFile = new Scanner(file);
			while (inFile.hasNextLine()) {
				String currentLine = inFile.nextLine().replace(',', '.');
				List<String> list = new ArrayList<String>(Arrays.asList(currentLine.split(" ")));
				BigDecimal[] row = new BigDecimal[list.size()];
			    
			    for (int i = 0; i < list.size(); i++)
			    {
			        row[i] = new BigDecimal(list.get(i));
			    }
			    matrix.addAll(Arrays.asList(Arrays.asList(row)));
			}
			inFile.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch(Exception e){
			Error error = new Error();
			error.open("Error in file " + file.getAbsolutePath() + " line " + (matrix.size() + 1));
		}
		rows = matrix.size();
		return chceckRows();
	}
	//Checks if all rows have the same size
	private boolean chceckRows(){
		int tempColumns = matrix.get(0).size();
		Boolean flag = true;
		List<BigDecimal> currentRow = matrix.get(0);
		for(List<BigDecimal> i : matrix){
			currentRow = i;
			if(i.size() != tempColumns){
				flag = false;
				break;
			}
		}
		if(flag){
			columns = tempColumns;
			return true;
		}else{
			Error error = new Error();
			error.open("Diffrent size of rows, line " + (matrix.indexOf(currentRow) + 1));
			return false;
		}
	}
}
