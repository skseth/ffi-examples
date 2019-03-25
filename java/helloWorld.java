import java.nio.ByteBuffer;

public class helloWorld {

	public static void main(String[] args){
		helloWorld h = new helloWorld();
		System.out.println("Starting Java Main");
		h.encrypt();
	}

	public void encrypt() {
		System.out.println("  encrypt in Java");
		ByteBuffer bb;
		bb = ByteBuffer.allocateDirect(3);
		byte[] byteArray = new byte[] { 0x01, 0x02, 0x03 };
		bb.put(byteArray);
		externEncrypt(bb); 
	}

	public static native void externEncrypt(ByteBuffer bb); 
	
}

