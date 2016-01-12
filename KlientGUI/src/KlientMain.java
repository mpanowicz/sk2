
public class KlientMain {

	public static void main(String[] args) {
		try {
			ChooseOption chooseOption = new ChooseOption();
			chooseOption.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
