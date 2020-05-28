package bgu.spl.net.SentFrames;

import bgu.spl.net.DataStructureHelper;

public class CONNECTED {

    private String version;

    public CONNECTED (String version) {
        this.version=version;
    }

    public String encode () {
        String toSend="";
        toSend = "CONNECTED" + "\n" + "version:"+version + "\n" +"\n"+ '\u0000';
        return toSend;
    }

}


