import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class FileService {
	public void readFileIntoArray(File file){
		Scanner inFile;
		try {
			inFile = new Scanner(file);
			
			while (inFile.hasNextLine()) {
				String currentLine = inFile.nextLine().replace(',', '.');
				String[] items = currentLine.split(" ");
			    float[] row = new float[items.length];

			    for (int i = 0; i < items.length; i++)
			    {
			        row[i] = Float.parseFloat(items[i]);
			        System.out.print(row[i] + " ");
			    }
				System.out.println();
			}
			inFile.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}
