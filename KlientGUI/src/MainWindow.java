import java.io.File;
import java.nio.file.Paths;

import javax.naming.CommunicationException;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Label;

public class MainWindow {

	protected Shell shell;
	private Text pathA;
	private Text pathB;
	private Text pathC;
	private Text adressText;
	private Text portText;
	private void findFile(Text path){
		FileDialog fileDialog = new FileDialog(shell, SWT.MULTI);
        fileDialog.setFilterExtensions(new String[]{"*.txt"});
        String file = fileDialog.open();
        if(file != null) {
          path.setText(file);
        }
	}
	
	//Open the window
	/**
	 * @wbp.parser.entryPoint
	 */
	public void open() {
		Display display = Display.getDefault();
		createContents();
		shell.open();
		shell.layout();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	 //Create contents of the window
	protected void createContents() {
		shell = new Shell();
		shell.setSize(450, 224);
		shell.setText("Mno¿enie macierzy");
		shell.setLayout(null);
		
		pathA = new Text(shell, SWT.BORDER);
		pathA.setBounds(28, 7, 298, 21);
		pathA.setText("C:\\GIT\\sk2\\macierzA.txt");
		
		Button chooseA = new Button(shell, SWT.NONE);
		chooseA.addMouseListener(new MouseAdapter() {
			public void mouseDown(MouseEvent e) {
				findFile(pathA);
			}
		});
		chooseA.setBounds(354, 5, 75, 25);
		chooseA.setText("Wybierz");
		
		pathB = new Text(shell, SWT.BORDER);
		pathB.setBounds(28, 36, 298, 21);
		pathB.setText("C:\\GIT\\sk2\\macierzB.txt");
		
		Button chooseB = new Button(shell, SWT.NONE);
		chooseB.addMouseListener(new MouseAdapter() {
			public void mouseDown(MouseEvent e) {
				findFile(pathB);
			}
		});
		chooseB.setText("Wybierz");
		chooseB.setBounds(354, 34, 75, 25);
		
		//Do some magic
		Button solve = new Button(shell, SWT.NONE);
		solve.addMouseListener(new MouseAdapter() {
			public void mouseDown(MouseEvent e) {
				Comunication com = new Comunication();
				String matrixC = "";
				if(pathC.getText() == ""){
					matrixC = Paths.get("").toAbsolutePath().toString() + "\\matrixC.txt";
				}else{
					matrixC = pathC.getText().toString();
				}
				com.connect(adressText.getText().toString(), Integer.parseInt(portText.getText().toString()), pathA.getText().toString(), pathB.getText().toString(), matrixC);	
				pathC.setText(matrixC);
			}
		});
		solve.setBounds(354, 82, 75, 25);
		solve.setText("Oblicz");
		
		pathC = new Text(shell, SWT.BORDER);
		pathC.setBounds(28, 84, 298, 21);
		
		Label pathLabel = new Label(shell, SWT.NONE);
		pathLabel.setBounds(28, 63, 180, 15);
		pathLabel.setText("Adres wygenerowanego pliku");
		
		Label adressLabel = new Label(shell, SWT.NONE);
		adressLabel.setBounds(28, 130, 30, 15);
		adressLabel.setText("Adres");
		
		Label portLabel = new Label(shell, SWT.NONE);
		portLabel.setText("Port");
		portLabel.setBounds(28, 157, 30, 15);
		
		adressText = new Text(shell, SWT.BORDER);
		adressText.setText("panowiczmichal.ddns.net");
		adressText.setBounds(64, 127, 262, 21);
		
		portText = new Text(shell, SWT.BORDER);
		portText.setText("4321");
		portText.setBounds(64, 154, 262, 21);

	}
}
