import java.util.Map;

public class Runner
{
    public static void main(String[] args)
    {
        ArgParser argParser = new ArgParser();
        Map<Arg, Object> parsedArgs;
        parsedArgs = argParser.parse(args);
        Simulator simulator = new Simulator(parsedArgs);
        simulator.simulate();
    }
}
