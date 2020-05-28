package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MsgEncDecImpl;
import bgu.spl.net.api.StompMessagingProtocolImpl;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {
        if (args[1].equals("tpc")) {
            Server.threadPerClient(Integer.parseInt(args[0]), //port
                    () -> new StompMessagingProtocolImpl(), //protocol factory
                    MsgEncDecImpl::new //message encoder decoder factory
            ).serve();
        }
        if (args[1].equals("reactor")) {
            Server.reactor(
                    Runtime.getRuntime().availableProcessors(),
                    Integer.parseInt(args[0]), //port
                    () -> new StompMessagingProtocolImpl(), //protocol factory
                    MsgEncDecImpl::new //message encoder decoder factory
            ).serve();
        }
    }


}
