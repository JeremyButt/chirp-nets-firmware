package Config;

import java.util.Collection;
import java.util.Map;

public class Config {
    private Integer numDevices;
    private Map<Integer, Map<Integer, Integer>> signalStrengths;
    private Integer RSSIThreshold;
    private Collection<Integer> deviceIds;
    private Map<Integer, Integer> groupIds;
    private Collection<ConfigPacket> packetsToSend;

    public Config() {
    }

    public Integer getNumDevices()
    {
        return this.numDevices;
    }

    public void setNumDevices(Integer numDevices)
    {
        this.numDevices = numDevices;
    }

    public Map<Integer, Map<Integer, Integer>> getSignalStrengths()
    {
        return this.signalStrengths;
    }

    public void setSignalStrengths(Map<Integer, Map<Integer, Integer>> signalStrengths)
    {
        this.signalStrengths = signalStrengths;
    }

    public Integer getRSSIThreshold()
    {
        return this.RSSIThreshold;
    }

    public void setRSSIThreshold(Integer RSSIThreshold)
    {
        this.RSSIThreshold = RSSIThreshold;
    }

    public Collection<Integer> getDeviceIds()
    {
        return this.deviceIds;
    }

    public void setDeviceIds(Collection<Integer> deviceIds)
    {
        this.deviceIds = deviceIds;
    }

    public Map<Integer, Integer> getGroupIds()
    {
        return this.groupIds;
    }

    public void setGroupIds(Map<Integer, Integer> groupIds)
    {
        this.groupIds = groupIds;
    }

    public Collection<ConfigPacket> getPacketsToSend()
    {
        return this.packetsToSend;
    }

    public void setPacketsToSend(Collection<ConfigPacket> packetsToSend)
    {
        this.packetsToSend = packetsToSend;
    }
}
