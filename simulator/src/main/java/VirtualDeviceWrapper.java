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
    private long radioPtr;
    private long bluetoothPtr;
    private long routerPtr;


    public VirtualDeviceWrapper(int deviceId, Environment environment)
    {
        this.deviceId = deviceId;
        this.bluetoothPacketsReceiving = new LinkedList<>();
        this.bluetoothPacketsSending = new LinkedList<>();
        this.environment = environment;
        this.init();
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
            this.loop();
            String bluetoothPacket = this.phoneReceiveBluetoothPacket();
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

    public native synchronized void init();
    public native synchronized void loop();

    public void send(int nodeId, int toAddress, byte[] payload)
    {
        this.environment.putPacketInTransit(nodeId, toAddress, payload);
    }

    public byte[] receive()
    {
        return this.environment.getPacketInTransit(this.deviceId);
    }

    public byte[] receiveBluetoothPacket()
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

    public String phoneReceiveBluetoothPacket()
    {
        try
        {
            byte[] payload = this.bluetoothPacketsSending.pop();
            if(payload.length > 0)
            {
                return new Packet(payload).toString();
            }
            else
            {
                return null;
            }
        }
        catch(NoSuchElementException e)
        {
            return null;
        }
    }
}
