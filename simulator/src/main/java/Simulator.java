import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
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
        // Initialize Devices with Bluetooth INIT PACKET
        ((VirtualDeviceWrapper)this.devices.toArray()[0]).phoneSendBluetoothPacket(new Packet(0,1, 1).getBytes());
        ((VirtualDeviceWrapper)this.devices.toArray()[1]).phoneSendBluetoothPacket(new Packet(0,1, 2).getBytes());
        ((VirtualDeviceWrapper)this.devices.toArray()[2]).phoneSendBluetoothPacket(new Packet(0,1, 3).getBytes());
        ((VirtualDeviceWrapper)this.devices.toArray()[3]).phoneSendBluetoothPacket(new Packet(0,1, 4).getBytes());

        sleep(2000);

        // Send Messages
        ((VirtualDeviceWrapper)this.devices.toArray()[0]).phoneSendBluetoothPacket(new Packet(1,1, 1, "Hello World, My Name Is Jeremy!").getBytes());
        sleep(2000);
        ((VirtualDeviceWrapper)this.devices.toArray()[3]).phoneSendBluetoothPacket(new Packet(1,1, 4, "I cannot reach node 1 by myself").getBytes());

    }

    private void sleep(int ms)
    {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void constructDevices()
    {
//        int numDevices = (Integer) this.args.get(Arg.NUMDEVICES);
//        int[] signalStrenths = (int[]) this.args.get(Arg.SIGNAL_STRENGTHS);
        int numDevices = 4;
        this.devices = new ArrayList<VirtualDeviceWrapper>();
        for (int i = 1; i < numDevices+1; i++)
        {
            VirtualDeviceWrapper virtualDevice = new VirtualDeviceWrapper(i, this.environment);
            virtualDevice.start();
            this.devices.add(virtualDevice);
        }
    }

    private void endSimulation()
    {
        for(VirtualDeviceWrapper device : this.devices)
        {
            device.kill();
        }
    }

}
