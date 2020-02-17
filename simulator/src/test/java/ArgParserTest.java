import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.Test;

import java.util.Map;

public class ArgParserTest {

    @Test
    public void Test_ArgParse()
    {
        String[] args = {"--numDevices", "4", "--signal_strengths", "[-20,-30,0,-10]", "--NOT_AN_ARG", "not an arg"};
        ArgParser argParser = new ArgParser();

        Map<Arg, Object> parsedArgs = argParser.parse(args);
        assertEquals(2, parsedArgs.size(), "Error! Expected 2 args!");

        assertEquals(4, parsedArgs.get(Arg.NUMDEVICES), "Incorrect numDevice Arg.");

        assertEquals(4, ((int[])parsedArgs.get(Arg.SIGNAL_STRENGTHS)).length, "Incorrect number of signal strengths.");
        int[] correct_signal_strengths = new int[]{-20,-30,0,-10};
        for(int i=0; i<4; i++)
        {
            assertEquals(correct_signal_strengths[i], ((int[])parsedArgs.get(Arg.SIGNAL_STRENGTHS))[i], "Incorrect signal strength.");
        }
    }

    @Test
    public void Test_FailedArgParse()
    {
        String[] args = {"--NOT_AN_ARG", "not an arg"};
        ArgParser argParser = new ArgParser();

        Map<Arg, Object> parsedArgs = argParser.parse(args);
        assertEquals(0, parsedArgs.size(), "Error! Expected 0 args!");
    }
}
