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



public class MainWindow {

	protected Shell shell;
	private Text pathA;
	private Text pathB;
	private Text text;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			MainWindow window = new MainWindow();
			window.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Open the window.
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

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shell = new Shell();
		shell.setSize(450, 300);
		shell.setText("SWT Application");
		shell.setLayout(null);
		
		pathA = new Text(shell, SWT.BORDER);
		pathA.setBounds(28, 7, 298, 21);
		pathA.setText("Macierz A");
		
		Button chooseA = new Button(shell, SWT.NONE);
		chooseA.addMouseListener(new MouseAdapter() {
			public void mouseDown(MouseEvent e) {
				FileDialog fileDialog = new FileDialog(shell, SWT.MULTI);
		        fileDialog.setFilterExtensions(new String[]{"*.txt"});
		        
		        String file = fileDialog.open();
		        if(file != null) {
		          pathA.setText(file);
		        }
			}
		});
		chooseA.setBounds(354, 5, 75, 25);
		chooseA.setText("Wybierz");
		
		pathB = new Text(shell, SWT.BORDER);
		pathB.setText("Macierz B");
		pathB.setBounds(28, 36, 298, 21);
		
		Button chooseB = new Button(shell, SWT.NONE);
		chooseB.addMouseListener(new MouseAdapter() {
			public void mouseDown(MouseEvent e) {
				FileDialog fileDialog = new FileDialog(shell, SWT.MULTI);
		        fileDialog.setFilterExtensions(new String[]{"*.txt"});
		        
		        String file = fileDialog.open();
		        if(file != null) {
		          pathB.setText(file);
		        }
			}
		});
		chooseB.setText("Wybierz");
		chooseB.setBounds(354, 34, 75, 25);
		
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

	}
}
