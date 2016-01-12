import java.io.File;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.widgets.FileDialog;
import java.net.*;
import java.io.*;
import org.eclipse.swt.widgets.Label;

public class MainWindow {

	protected Shell shell;
	private Text pathA;
	private Text pathB;
	private Text text;
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
		shell.setSize(450, 300);
		shell.setText("Mno¿enie macierzy");
		shell.setLayout(null);
		
		pathA = new Text(shell, SWT.BORDER);
		pathA.setBounds(28, 7, 298, 21);
		
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
				File fileA = new File(pathA.getText());
				File fileB = new File(pathB.getText());
				if(fileA.exists() && !fileA.isDirectory() && fileB.exists() && !fileB.isDirectory()){
					solve solver = new solve();
					solver.multiply(pathA.getText(), pathB.getText());
					//solver.connect();
					FileService fileService = new FileService();
					fileService.readFileIntoArray(fileA);
				}
				else{
					Error error = new Error();
					error.open("File no exists");
				}
				
			}
		});
		solve.setBounds(354, 82, 75, 25);
		solve.setText("Oblicz");
		
		text = new Text(shell, SWT.BORDER);
		text.setBounds(28, 84, 298, 21);
		
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
		adressText.setBounds(64, 127, 262, 21);
		
		portText = new Text(shell, SWT.BORDER);
		portText.setBounds(64, 154, 262, 21);

	}
}
