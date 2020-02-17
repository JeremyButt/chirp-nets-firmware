import java.util.*;
import java.util.stream.Stream;

/*
*  To add an argument:
*  1. Add to Arg enum,
*  2. Handle special parsing in switch block if needed,
*  3. Add test case if adding a special parsing.
* */

enum Arg
{
    NUMDEVICES,
    SIGNAL_STRENGTHS,
}

public class ArgParser {

    public ArgParser()
    {

    }

    public Map<Arg, Object> parse(String[] args)
    {
        Map<Arg, Object> parsedArgs = new HashMap<>();
        Arg tempArg = null;
        for(String string : args)
        {
            Boolean existsInArgs = false;
            try
            {
                existsInArgs = Arrays.stream(Arg.values()).anyMatch(Arg.valueOf(string.toUpperCase().replace("--", ""))::equals);
            }
            catch (IllegalArgumentException e)
            {
                if(string.matches("^--.+"))
                    System.out.println("Not a valid argument: " + e.getMessage().split("\\.")[1]);
            }

            if (tempArg == null && string.matches("^--.+") && existsInArgs)
            {
                tempArg = Arg.valueOf(string.toUpperCase().replace("--", ""));
            }
            else if (tempArg != null && !string.matches("^--.+"))
            {
                switch (tempArg){
                    case NUMDEVICES:
                        parsedArgs.put(tempArg, Integer.parseInt(string));
                        break;
                    case SIGNAL_STRENGTHS:
                        parsedArgs.put(tempArg, stringToArrayOfInts(string));
                        break;
                    default:
                        parsedArgs.put(tempArg, string);
                        break;
                }
                tempArg = null;
            }
        }
        return parsedArgs;
    }

    // PARSE HELPER FUNCTIONS

    static public int[] stringToArrayOfInts(String string)
    {
        return Stream.of(string.replace("[","").replace("]","").split("\\,")).mapToInt(Integer::parseInt).toArray();
    }
}
