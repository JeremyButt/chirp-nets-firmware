import Config.Config;
import Config.ConfigParser;

public class Runner
{
    public static void main(String[] args)
    {
        ConfigParser configParser = new ConfigParser();
        Config config = configParser.parse("simulator_config.json");
        Simulator simulator = new Simulator(config);
        simulator.simulate();
        ReportGenerator reportGenerator = new ReportGenerator(simulator);
        reportGenerator.generateReport();
        reportGenerator.printReport();
    }
}
