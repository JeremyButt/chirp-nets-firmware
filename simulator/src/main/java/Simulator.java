import Config.Config;
import Config.ConfigPacket;

import java.util.HashMap;
import java.util.Map;

public class Simulator
{
    private Map<Integer, VirtualDeviceWrapper> devices;
    private Environment environment;
    private Config config;

    public Simulator(Config config)
    {
        //Load JNI Library
        System.loadLibrary("VirtualDeviceWrapper");

        this.config = config;
        this.environment = new Environment(config);
        this.constructDevices();
    }

    public void simulate()
    {
        System.out.println("================================================================================================");
        System.out.println("REALTIME SIMULATION OUTPUT");
        this.sendInitPackets();
        this.sendPackets();
        endSimulation();
        System.out.println("END OF SIMULATION");
        System.out.println("================================================================================================");
    }

    private void sendInitPackets()
    {
        for(VirtualDeviceWrapper device : this.devices.values())
        {
            device.phoneSendBluetoothPacket(new Packet(Packet.INIT_PACKET, config.getGroupIds().get(device.getDeviceId()), device.getDeviceId()));
        }
        sleep(2000);
    }

    private void sendPackets()
    {
        for(ConfigPacket packetToSend : config.getPacketsToSend())
        {
            VirtualDeviceWrapper device = this.devices.get(packetToSend.getFromNodeId());
            device.phoneSendBluetoothPacket(new Packet(Packet.DATA_PACKET, device.getGroupId(), device.getDeviceId(), packetToSend.getMessage()));
            sleep(packetToSend.getDelay());
        }
    }

    static private void sleep(int ms)
    {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void constructDevices()
    {
        if(this.config.getDeviceIds().size() != this.config.getNumDevices())
        {
            return;
        }

        this.devices = new HashMap<>();
        for (Integer deviceId : this.config.getDeviceIds())
        {
            VirtualDeviceWrapper virtualDevice = new VirtualDeviceWrapper(deviceId, this.environment);
            virtualDevice.start();
            this.devices.put(deviceId, virtualDevice);
        }
    }

    private void endSimulation()
    {
        for(VirtualDeviceWrapper device : this.devices.values())
        {
            device.kill();
        }
    }

    public Map<Integer, VirtualDeviceWrapper> getDevices()
    {
        return this.devices;
    }
}
