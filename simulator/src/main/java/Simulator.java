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
        ((VirtualDeviceWrapper)this.devices.toArray()[0]).phoneSendBluetoothPacket(new Packet(1,0, "Hello Device no.1, How are you?").getBytes());
        sleep(5000);
        ((VirtualDeviceWrapper)this.devices.toArray()[2]).phoneSendBluetoothPacket(new Packet(3,2, "Hello Device no.3, How was your day?").getBytes());
        ((VirtualDeviceWrapper)this.devices.toArray()[1]).phoneSendBluetoothPacket(new Packet(0,1, "Hello Device no.0! I am Good. How are you?").getBytes());
        sleep(2000);
        ((VirtualDeviceWrapper)this.devices.toArray()[3]).phoneSendBluetoothPacket(new Packet(2,3, "Hello Device no.2, It was good and you?").getBytes());
        sleep(1000);
        ((VirtualDeviceWrapper)this.devices.toArray()[0]).phoneSendBluetoothPacket(new Packet(1,0, "I am doing well? Did you see x?").getBytes());
        sleep(4000);
        ((VirtualDeviceWrapper)this.devices.toArray()[1]).phoneSendBluetoothPacket(new Packet(0,1, "No I did not.").getBytes());
        sleep(5000);
        ((VirtualDeviceWrapper)this.devices.toArray()[2]).phoneSendBluetoothPacket(new Packet(3,2, "Good. See you later!").getBytes());
        sleep(3000);
        ((VirtualDeviceWrapper)this.devices.toArray()[3]).phoneSendBluetoothPacket(new Packet(2,3, "See you later!").getBytes());
        sleep(8000);
        endSimulation();
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
        int numDevices = (Integer) this.args.get(Arg.NUMDEVICES);
        int[] signalStrenths = (int[]) this.args.get(Arg.SIGNAL_STRENGTHS);
        this.devices = new ArrayList<VirtualDeviceWrapper>();
        for (int i = 0; i < numDevices; i++)
        {
            VirtualDeviceWrapper virtualDevice = new VirtualDeviceWrapper(i, signalStrenths[i], this.environment);
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
