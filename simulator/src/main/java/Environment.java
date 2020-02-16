import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentLinkedQueue;

public class Environment
{

    private final Map<Integer, ConcurrentLinkedQueue<byte[]>> packets_in_transit;

    public Environment()
    {
        this.packets_in_transit = Collections.synchronizedMap(new HashMap<Integer, ConcurrentLinkedQueue <byte[]>>());
    }

    public void putPacketInTransit(int toAddress, byte payload[])
    {
        ConcurrentLinkedQueue<byte[]> packets = this.packets_in_transit.get(toAddress);
        if (packets == null)
        {
            packets = new ConcurrentLinkedQueue<byte[]>();
        }
        packets.add(payload);
        this.packets_in_transit.put(toAddress, packets);
    }

    public byte[] getPacketInTransit(int toAddress)
    {
        ConcurrentLinkedQueue<byte[]> packets = this.packets_in_transit.get(toAddress);
        if(packets != null && packets.size() != 0)
        {
            return packets.remove();
        }
        return null;
    }
}
