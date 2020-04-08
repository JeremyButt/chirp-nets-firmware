import java.io.UnsupportedEncodingException;

public class Packet {
    private int type;
    private int groupId;
    private int nodeId;
    private String data;

    public Packet(int type, int groupId, int nodeId, String data) {
        this.type = type;
        this.groupId = groupId;
        this.nodeId = nodeId;
        this.data = data;
    }

    public Packet(int type, int groupId, int nodeId) {
        this.type = type;
        this.groupId = groupId;
        this.nodeId = nodeId;
    }

    public Packet(byte[] payload) {
        this.type = (int) (payload[0]-48);
        this.groupId = (int) (payload[1]-48);
        this.nodeId = ((int)(payload[2]-48) * 10) + (int)(payload[3]-48);
        byte[] data_bytes = new byte[payload.length - 4];
        for(int i = 0; i < payload.length - 4; i++)
        {
            data_bytes[i] = payload[4+i];
        }

        try
        {
            this.data = new String(data_bytes, "UTF-8");
        }
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }
    }

    public byte[] getBytes()
    {
        try
        {
            if(this.type == 1)
            {
                byte bytes[] = (String.valueOf(this.type) + String.valueOf(this.groupId) + (this.nodeId<10?"0":"") + String.valueOf(this.nodeId) + data ).getBytes("UTF-8");
                return bytes;
            }
            else if(this.type == 0)
            {
                byte bytes[] = (String.valueOf(this.type) + String.valueOf(this.groupId) + (this.nodeId<10?"0":"") + String.valueOf(this.nodeId)).getBytes("UTF-8");
                return bytes;
            }
        }
        catch (UnsupportedEncodingException e)
        {
            return null;
        }
        return null;
    }

    public boolean isInitPacket()
    {
        return this.type == 0;
    }

    public int getGroupId()
    {
        return this.groupId;
    }

    @Override
    public String toString() {
        return "Packet{" +
                "type=" + type +
                ", groupId=" + groupId +
                ", nodeId=" + nodeId +
                ((this.type == 1 ) ? ", data='" + data + '\'' : "") +
                '}';
    }
}
