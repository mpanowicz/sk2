import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;


public class ChooseOption {

	protected Shell shlMnoenieMacierzy;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			ChooseOption window = new ChooseOption();
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
		shlMnoenieMacierzy.open();
		shlMnoenieMacierzy.layout();
		while (!shlMnoenieMacierzy.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}
	
	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shlMnoenieMacierzy = new Shell();
		shlMnoenieMacierzy.setSize(450, 128);
		shlMnoenieMacierzy.setText("Mno\u017Cenie macierzy");
		shlMnoenieMacierzy.setLayout(null);
		
		Label chooseLabel = new Label(shlMnoenieMacierzy, SWT.CENTER);
		chooseLabel.setBounds(141, 10, 140, 15);
		chooseLabel.setText("Wybierz typ klienta");
		
		Button countButton = new Button(shlMnoenieMacierzy, SWT.NONE);
		countButton.setText("Licz\u0105cy");
		countButton.setBounds(67, 49, 75, 25);
		
		Button sendButton = new Button(shlMnoenieMacierzy, SWT.NONE);
		sendButton.addMouseListener(new MouseAdapter() {
			public void mouseDown(MouseEvent e) {
				MainWindow window = new MainWindow();
				shlMnoenieMacierzy.close();
				window.open();
			}
		});
		sendButton.setText("Zg\u0142aszaj\u0105cy");
		sendButton.setBounds(282, 49, 75, 25);

	}
}
