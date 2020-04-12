import Config.Config;
import Config.ConfigParser;
import org.junit.jupiter.api.Test;

public class VirtualDeviceWrapperTest {
    @Test
    public void Test_VirtualDeviceWrapper_Boot(){
        System.loadLibrary("VirtualDeviceWrapper");
        ConfigParser configParser = new ConfigParser();
        Config config = configParser.parse("simulator_config.json");
        Environment env = new Environment(config);
        VirtualDeviceWrapper virtualDevice = new VirtualDeviceWrapper(1, env);

        virtualDevice.phoneSendBluetoothPacket(new Packet(0,1,1,"hello"));

        virtualDevice.start();
    }
}
