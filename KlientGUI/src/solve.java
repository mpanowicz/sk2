import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class solve {
	public void multiply(String str1, String str2){
		System.out.println(str1 + "\n" + str2);
	}
	public void connect(){
		try{
			String serverName = "localhost";
		    int port = Integer.parseInt("1234");
		    System.out.println("Connecting to " + serverName + " on port " + port);
		    Socket client = new Socket(serverName, port);
		    System.out.println("Just connected to " + client.getRemoteSocketAddress());
		    OutputStream outToServer = client.getOutputStream();
		    DataOutputStream out = new DataOutputStream(outToServer);
		    out.writeUTF("Hello from " + client.getLocalSocketAddress());
		    InputStream inFromServer = client.getInputStream();
		    DataInputStream in = new DataInputStream(inFromServer);
		    System.out.println("Server says " + in.readUTF());
		    client.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
