import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.NoSuchElementException;

public class VirtualDeviceWrapper extends Thread{
    private int deviceId;
    private int groupId;
    private boolean isRunning;
    private LinkedList<byte[]> bluetoothPacketsReceiving;
    private LinkedList<byte[]> bluetoothPacketsSending;
    private Environment environment;
    private long radioPtr;
    private long bluetoothPtr;
    private long routerPtr;

    private Collection<Packet> sentMessages;
    private Collection<Packet> receivedMessages;
    private Collection<Packet> initMessages;


    public VirtualDeviceWrapper(int deviceId, Environment environment)
    {
        this.deviceId = deviceId;
        this.bluetoothPacketsReceiving = new LinkedList<>();
        this.bluetoothPacketsSending = new LinkedList<>();
        this.sentMessages = new ArrayList<>();
        this.receivedMessages = new ArrayList<>();
        this.initMessages = new ArrayList<>();
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

    public void phoneSendBluetoothPacket(Packet packet)
    {
        if(packet.isInitPacket())
        {
            this.groupId = packet.getGroupId();
            this.initMessages.add(packet);
        }
        else
        {
            this.sentMessages.add(packet);
        }
        this.bluetoothPacketsReceiving.add(packet.getBytes());

    }

    public String phoneReceiveBluetoothPacket()
    {
        try
        {
            byte[] payload = this.bluetoothPacketsSending.pop();
            if(payload.length > 0)
            {
                Packet packet = new Packet(payload);
                this.receivedMessages.add(packet);
                return packet.toString();
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

    public int getDeviceId()
    {
        return this.deviceId;
    }

    public int getGroupId()
    {
        return this.groupId;
    }

    public Collection<Packet> getSentMessages()
    {
        return this.sentMessages;
    }

    public Collection<Packet> getReceivedMessages()
    {
        return this.receivedMessages;
    }

    public Collection<Packet> getInitMessages()
    {
        return this.initMessages;
    }
}
