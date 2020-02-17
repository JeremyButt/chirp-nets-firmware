import java.io.UnsupportedEncodingException;
import java.util.LinkedList;
import java.util.NoSuchElementException;

public class VirtualDeviceWrapper extends Thread{
    private int deviceId;
    private int signalStrenth;
    private boolean isRunning;
    private LinkedList<byte[]> bluetoothPacketsReceiving;
    private LinkedList<byte[]> bluetoothPacketsSending;
    private Environment environment;

    public VirtualDeviceWrapper(int deviceId, int signalStrength, Environment environment)
    {
        this.deviceId = deviceId;
        this.signalStrenth = signalStrength;
        this.bluetoothPacketsReceiving = new LinkedList<>();
        this.bluetoothPacketsSending = new LinkedList<>();
        this.environment = environment;
    }

    public void start()
    {
        this.isRunning = true;
        super.start();
    }

    public void run()
    {
        System.loadLibrary("VirtualDeviceWrapper");
        while(this.isRunning)
        {
            this.main();
            String bluetoothPacket = this.phoneRecieveBluetoothPacket();
            if(bluetoothPacket != null)
            {
                System.out.println("["+System.nanoTime()+"]"+"(Device-"+this.deviceId+") " + bluetoothPacket);
            }
        }
    }

    public void kill()
    {
        this.isRunning = false;
    }

    public native void main();

    public int getDeviceId()
    {
        return this.deviceId;
    }

    public void send(int toAddress, byte[] payload)
    {
        this.environment.putPacketInTransit(toAddress, payload);
    }

    public byte[] receive()
    {
        return this.environment.getPacketInTransit(this.deviceId);
    }

    public byte[] recieveBluetoothPacket()
    {
        try
        {
            return this.bluetoothPacketsReceiving.pop();
        }
        catch(NoSuchElementException e)
        {
            return null;
        }
    }

    public void sendBluetoothPacket(byte[] payload)
    {
        this.bluetoothPacketsSending.add(payload);
    }

    public void phoneSendBluetoothPacket(byte[] payload)
    {
        this.bluetoothPacketsReceiving.add(payload);
    }

    public String phoneRecieveBluetoothPacket()
    {
        try
        {
            return new String(this.bluetoothPacketsSending.pop(), "UTF-8");
        }
        catch(NoSuchElementException | UnsupportedEncodingException e)
        {
            return null;
        }
    }

}
