import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class Message {
    public Map<Integer, Boolean> hasRead;
    public byte[] data;

    public Message(Collection<Integer> nodesToRead, byte[] data)
    {
        this.hasRead = Collections.synchronizedMap(new HashMap<Integer, Boolean>());
        for(Integer node : nodesToRead)
        {
            this.hasRead.put(node, false);
        }
        this.data = data;
    }
    public Boolean readComplete()
    {
        Boolean readComplete = true;
        for(Boolean read : this.hasRead.values())
        {
            readComplete = readComplete && read;
        }
        return readComplete;
    }
}
