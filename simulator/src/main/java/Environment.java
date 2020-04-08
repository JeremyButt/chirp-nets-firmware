import Config.Config;

import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentLinkedQueue;

public class Environment
{
    int num_nodes;
    private Map<Integer, ConcurrentLinkedQueue<Message>> packets_in_transit;
    private Map<Integer, Map<Integer, Integer>> signal_strengths;
    private Integer rssiThreshold;

    public Environment(Config config)
    {
        this.num_nodes = config.getNumDevices();
        this.signal_strengths = config.getSignalStrengths();
        this.packets_in_transit = Collections.synchronizedMap(new HashMap<Integer, ConcurrentLinkedQueue <Message>>());
        this.rssiThreshold = config.getRSSIThreshold();
    }

    public void putPacketInTransit(int nodeId, int toAddress, byte payload[])
    {
        Collection<Integer> connected_nodes = getConnectedNodes(nodeId);

        ConcurrentLinkedQueue<Message> messages = this.packets_in_transit.get(nodeId);
        if (messages == null)
        {
            messages = new ConcurrentLinkedQueue<Message>();
        }
        Message message = new Message(connected_nodes, payload);
        messages.add(message);
        this.packets_in_transit.put(nodeId, messages);
    }

    public byte[] getPacketInTransit(int nodeId)
    {
        Collection<Integer> connected_nodes = getConnectedNodes(nodeId);
        for(Integer node : connected_nodes)
        {
            ConcurrentLinkedQueue<Message> messages = this.packets_in_transit.get(node);
            synchronized (this)
            {
                if(messages != null && messages.peek() != null)
                {
                    Message message = messages.peek();
                    if(!message.hasRead.get(nodeId))
                    {
                        message.hasRead.put(nodeId, true);
                        if(message.readComplete())
                        {
                            messages.remove();
                        }
                        return message.data;
                    }
                }
            }
        }
        return null;
    }

    private Collection<Integer> getConnectedNodes(int nodeId)
    {
        Collection<Integer> connected_nodes = new ArrayList<Integer>();
        Map<Integer, Integer> node_connections = this.signal_strengths.get(nodeId);
        if(node_connections != null)
        {
            for(int i = 1; i<num_nodes+1; i++)
            {
                if (i!=nodeId)
                {
                    if(node_connections.get(i) >= this.rssiThreshold)
                    {
                        connected_nodes.add(i);
                    }
                }
            }
        }
        return connected_nodes;
    }
}
