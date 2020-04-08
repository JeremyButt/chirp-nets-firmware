package Config;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import java.io.FileReader;
import java.util.*;

public class ConfigParser {

    private JSONParser parser;

    public ConfigParser() {
        this.parser = new JSONParser();
    }

    public Config parse(String filename)
    {
        Config config = new Config();
        try
        {
            Object obj = parser.parse(new FileReader("src/main/resources/" + filename));
            JSONObject jsonObject = (JSONObject) obj;

            Integer numDevices = parseNumDevices(jsonObject);
            config.setNumDevices(numDevices);

            Map<Integer, Map<Integer, Integer>> signalStrengths = parseSignalStrengths(jsonObject);
            config.setSignalStrengths(signalStrengths);

            Integer RSSIThreshold = parseRSSIThreshold(jsonObject);
            config.setRSSIThreshold(RSSIThreshold);

            Collection<Integer> deviceIds = parseDeviceIDs(jsonObject);
            config.setDeviceIds(deviceIds);

            Map<Integer, Integer> groupIds = parseGroupIDs(jsonObject);
            config.setGroupIds(groupIds);

            Collection<ConfigPacket> packetsToSend = parsePacketsToSend(jsonObject);
            config.setPacketsToSend(packetsToSend);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        return config;
    }

    static private Integer parseNumDevices(JSONObject obj)
    {
        return ((Long)obj.get("number_of_nodes")).intValue();
    }

    static private Map<Integer, Map<Integer, Integer>> parseSignalStrengths(JSONObject obj)
    {
        Map<Integer, Map<Integer, Integer>> signalStrengths = Collections.synchronizedMap(new HashMap<Integer, Map<Integer, Integer>>());;
        JSONObject json_signal_strengths = (JSONObject) obj.get("signal_strengths");
        Iterator<String> iterator1 = (Iterator<String>) json_signal_strengths.keySet().iterator();
        while (iterator1.hasNext())
        {
            Integer deviceId = Integer.parseInt(iterator1.next());
            signalStrengths.put(deviceId, Collections.synchronizedMap(new HashMap<Integer, Integer>()));

            JSONObject device_strengths = (JSONObject) json_signal_strengths.get(deviceId.toString());
            Iterator<String> iterator2 = (Iterator<String>) device_strengths.keySet().iterator();
            while (iterator2.hasNext())
            {
                Integer neighbourId = Integer.parseInt(iterator2.next());
                Integer signal_strength = ((Long)device_strengths.get(neighbourId.toString())).intValue();
                signalStrengths.get(deviceId).put(neighbourId, signal_strength);
            }
        }
        return signalStrengths;
    }

    static private Integer parseRSSIThreshold(JSONObject obj)
    {
        return ((Long)obj.get("rssi_threshold")).intValue();
    }

    static private Collection<Integer> parseDeviceIDs(JSONObject obj)
    {
        Collection<Integer> deviceIds = new ArrayList<Integer>();
        JSONArray json_device_ids = (JSONArray) obj.get("device_ids");

        for (Object json_device_id : json_device_ids) {
            deviceIds.add(Integer.parseInt((String)json_device_id));
        }
        return deviceIds;
    }

    static private Map<Integer, Integer> parseGroupIDs(JSONObject obj)
    {
        Map<Integer, Integer> groupIds = new HashMap<>();
        JSONObject json_group_ids = (JSONObject) obj.get("groups");
        Iterator<String> i = (Iterator<String>) json_group_ids.keySet().iterator();
        while (i.hasNext())
        {
            Integer deviceId = Integer.parseInt(i.next());
            Integer groupId = ((Long)json_group_ids.get(deviceId.toString())).intValue();
            groupIds.put(deviceId, groupId);
        }
        return groupIds;
    }

    static private Collection<ConfigPacket> parsePacketsToSend(JSONObject obj)
    {
        Collection<ConfigPacket> packetsToSend = new ArrayList<>();
        JSONArray json_packets_to_send = (JSONArray) obj.get("packets_to_send");

        for (Object packet_to_send : json_packets_to_send)
        {
            Integer from = ((Long)((JSONObject)packet_to_send).get("from")).intValue();
            Integer delay = ((Long)((JSONObject)packet_to_send).get("delay")).intValue();
            String message = (String)((JSONObject)packet_to_send).get("message");
            ConfigPacket packetToSend = new ConfigPacket(from, delay, message);
            packetsToSend.add(packetToSend);
        }
        return packetsToSend;
    }
}
