package bgu.spl.net.SentFrames;

public class RECIEPT {

    private int id;

    public RECIEPT (int id) {
        this.id=id;
    }

    public String encodeSUBSCRIBE () {
        String toSend="";
        toSend = "RECEIPT" + "\n" + "receipt-id:" + id + "\n" +"\n"+ '\u0000';
        return toSend;
    }

    public String encodeUNSUBSCRIBE () {
        String toSend="";
        toSend = "RECEIPT" + "\n" + "receipt-id:" + id + "\n" +"\n"+ '\u0000';
        return toSend;
    }

}
