import java.io.UnsupportedEncodingException;

public class Packet {
    private int toAddress;
    private int fromAddress;
    private String data;

    public Packet(int toAddress, int fromAddress, String data) {
        this.toAddress = toAddress;
        this.fromAddress = fromAddress;
        this.data = data;
    }

    public byte[] getBytes()
    {
        try
        {
            return (String.valueOf(toAddress) + "|" + String.valueOf(fromAddress) + "|" + data).getBytes("UTF-8");
        }
        catch (UnsupportedEncodingException e)
        {
            return null;
        }
    }
}
