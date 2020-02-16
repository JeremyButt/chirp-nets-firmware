import java.util.ArrayList;
import java.util.Collection;
import java.util.Map;

public class Simulator
{
    Collection<VirtualDeviceWrapper> devices;
    Environment environment;
    Map<Arg, Object> args;

    public Simulator(Map<Arg, Object> args)
    {
        //Load JNI Library
        System.loadLibrary("VirtualDeviceWrapper");

        this.args = args;
        this.environment = new Environment();
        this.constructDevices();
    }

    public void simulate()
    {
        byte[] phoneVirtualDevice0 = new Packet(1,0, "Hello Device no.1, How are you?").getBytes();
        byte[] phoneVirtualDevice1 = new Packet(2,1, "Hello Device no.2, Good how are you?").getBytes();
        byte[] phoneVirtualDevice2 = new Packet(3,2, "Hello Device no.3, Love you!").getBytes();
        byte[] phoneVirtualDevice3 = new Packet(1,3, "Hello 1, Whats up?").getBytes();
        byte[][] bluetoothPayloads = {phoneVirtualDevice0, phoneVirtualDevice1, phoneVirtualDevice2, phoneVirtualDevice3};
        int i = 0;
        for(VirtualDeviceWrapper device : this.devices)
        {
            device.phoneSendBluetoothPacket(bluetoothPayloads[i]);
            i++;
        }
        for(VirtualDeviceWrapper device: this.devices)
        {
            device.start();
        }
    }

    private void constructDevices()
    {
        int numDevices = (Integer) this.args.get(Arg.NUMDEVICES);
        int[] signalStrenths = (int[]) this.args.get(Arg.SIGNAL_STRENGTHS);
        this.devices = new ArrayList<VirtualDeviceWrapper>();
        for (int i = 0; i < numDevices; i++)
        {
            VirtualDeviceWrapper virtualDevice = new VirtualDeviceWrapper(i, signalStrenths[i], this.environment);
            this.devices.add(virtualDevice);
        }
    }

}
