public class ReportGenerator
{
    private Simulator simulator;
    private String report;

    public ReportGenerator(Simulator simulator)
    {
        this.simulator = simulator;
        this.report = "";
    }

    public void generateReport()
    {
        for(VirtualDeviceWrapper virtualDevice : simulator.getDevices().values())
        {
            this.report = this.report.concat("======================================================================\n");
            this.report = this.report.concat("Device ID: " + virtualDevice.getDeviceId() + " of Group ID: " + virtualDevice.getGroupId() + "\n");

            // INIT Packets
            this.report = this.report.concat("----------------------------------------------------------------------\n");
            this.report = this.report.concat("Init Messages\n");
            for(Packet initMessage : virtualDevice.getInitMessages())
            {
                this.report = this.report.concat(initMessage.toString() + "\n");
            }

            //SENT Packets
            this.report = this.report.concat("----------------------------------------------------------------------\n");
            this.report = this.report.concat("Sent Messages\n");
            for(Packet sentMessage : virtualDevice.getSentMessages())
            {
                this.report = this.report.concat(sentMessage.toString() + "\n");
            }

            //RECEIVED Packets
            this.report = this.report.concat("----------------------------------------------------------------------\n");
            this.report = this.report.concat("Received Messages\n");
            for(Packet receivedMessage : virtualDevice.getReceivedMessages())
            {
                this.report = this.report.concat(receivedMessage.toString() + "\n");
            }
        }
        this.report = this.report.concat("======================================================================\n");
    }

    public void printReport()
    {
        System.out.print("\n\n SIMULATION REPORT \n");
        System.out.print(this.report);
    }
}
