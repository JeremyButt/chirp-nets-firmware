import org.junit.jupiter.api.Test;

import java.io.UnsupportedEncodingException;

public class VirtualDeviceWrapperTest {
    @Test
    public void Test_VirtualDeviceWrapper_Boot(){
        System.loadLibrary("VirtualDeviceWrapper");
        Environment env = new Environment();
        VirtualDeviceWrapper virtualDevice = new VirtualDeviceWrapper(1, env);

        try {
            virtualDevice.phoneSendBluetoothPacket("1helloworld2!".getBytes("UTF-8"));
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        virtualDevice.start();
    }
}
