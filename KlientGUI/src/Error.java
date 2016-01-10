import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.widgets.Label;


public class Error {

	protected Shell errorWindow;

	/**
	 * Open the window.
	 * @wbp.parser.entryPoint
	 */
	public void open(String error) {
		Display display = Display.getDefault();
		createContents(error);
		errorWindow.open();
		errorWindow.layout();
		while (!errorWindow.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents(String error) {
		errorWindow = new Shell();
		errorWindow.setSize(409, 135);
		errorWindow.setText("Error");
		
		Button okButton = new Button(errorWindow, SWT.NONE);
		okButton.addMouseListener(new MouseAdapter() {
			public void mouseDown(MouseEvent e) {
				errorWindow.close();
			}
		});
		okButton.setBounds(159, 61, 75, 25);
		okButton.setText("OK");
		
		Label errorLabel = new Label(errorWindow, SWT.CENTER);
		errorLabel.setBounds(10, 10, 373, 45);
		errorLabel.setText(error);

	}
}
