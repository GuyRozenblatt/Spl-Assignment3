package bgu.spl.net.SentFrames;

import bgu.spl.net.DataStructureHelper;

public class ERROR {

    private String error;

    public ERROR (String error) {
        this.error=error;
    }

    public String encode () {
        String toSend="";
        toSend = "ERROR" + "\n" + error + "\n" + '\u0000';
        return toSend;
    }

}
