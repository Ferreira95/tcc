import java.net.*;
import java.io.*;
import java.util.*;

public class Network {
	public final static String ADDR = "localhost";
	public final static int PORT = 8000;
	private Socket client;
	private Scanner clientRead;
	private PrintWriter clientWrite;
	private String addr;
	private int port;

	public Network() {
		this.connect();
	}

	public boolean connect() {
		try {
			client = new Socket(ADDR, PORT);
			this.clientWrite = new PrintWriter(this.client.getOutputStream());
			this.clientRead = new Scanner(this.client.getInputStream());
			return true;

		} catch(UnknownHostException ex) {
			System.err.println(ex);
			return false;
		} catch(Exception ex) {
			System.err.println(ex);
			return false;
		}
	}

	public void send(String msg) {
		try {
			this.clientWrite.write(msg);
			this.clientWrite.flush();
		} catch(Exception ex) {
			System.err.println(ex);
		}
	} 

	public String read() {
		StringBuilder temp = new StringBuilder();
		try {
			while(this.clientRead.hasNextLine())
				temp.append(this.clientRead.nextLine());
			return temp.toString();
			
		} catch(Exception ex) {
			System.err.println(ex);
			return null;
		}
	}
}
