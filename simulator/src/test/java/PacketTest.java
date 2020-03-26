import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class PacketTest {
    @Test
    public void PacketSerializationTest()
    {
        Packet packet = new Packet(0,1,1, "Hi");
        byte bytes[] = packet.getBytes();
        Assertions.assertEquals((char)bytes[0], '0', "Incorrect Type Byte!");
        Assertions.assertEquals((char)bytes[1], '1', "Incorrect groupId Byte!");

        byte b1 = (byte) (1 & 0xFF);
        byte b2 = (byte) ((1 >> 8) & 0xFF);
        Assertions.assertEquals((char)bytes[2], b1, "Incorrect nodeId Byte1!");
        Assertions.assertEquals((char)bytes[3], b2, "Incorrect nodeId Byte2!");

        Assertions.assertEquals((char)bytes[4], 'H', "Incorrect data Byte!");
        Assertions.assertEquals((char)bytes[5], 'i', "Incorrect data Byte!");
    }
}
