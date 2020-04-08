package Config;

public class ConfigPacket
{
    private Integer fromNodeId;
    private Integer delay;
    private String message;

    public ConfigPacket()
    {}

    public ConfigPacket(Integer fromNodeId, Integer delay, String message)
    {
        this.fromNodeId = fromNodeId;
        this.delay = delay;
        this.message = message;
    }

    public Integer getFromNodeId()
    {
        return this.fromNodeId;
    }

    public void setFromNodeId(Integer fromNodeId)
    {
        this.fromNodeId = fromNodeId;
    }

    public Integer getDelay()
    {
        return this.delay;
    }

    public void setDelay(Integer delay)
    {
        this.delay = delay;
    }

    public String getMessage()
    {
        return this.message;
    }

    public void setMessage(String message)
    {
        this.message = message;
    }
}
