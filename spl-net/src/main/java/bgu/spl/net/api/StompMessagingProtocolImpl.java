package bgu.spl.net.api;

import bgu.spl.net.DataStructureHelper;
import bgu.spl.net.RecievedFrames.CONNECT;
import bgu.spl.net.RecievedFrames.DISCONNECT;
import bgu.spl.net.RecievedFrames.SUBSCRIBE;
import bgu.spl.net.RecievedFrames.UNSUBSCRIBE;
import bgu.spl.net.User;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

import java.util.List;

public class StompMessagingProtocolImpl implements StompMessagingProtocol<String> {

    private int connectionId;
    private boolean ShouldTerminate = false;
    private Connections<String> connections;

    public StompMessagingProtocolImpl() {}

    @Override
    public void start(int connectionId, Connections<String> connections) {
        this.connectionId=connectionId;
        this.connections=connections;
    }

    @Override
    public void process(String message) {
        String[] result = message.split("\n", 10);
        if (result[0].equals("CONNECT")) {
            String userName = result[3].substring(6);
            String passcode = result[4].substring(9);
            String version = result[1].substring(15);
            CONNECT connect = new CONNECT(userName, passcode, connectionId, version);
            String toReturn = connect.run();
            connections.send(connectionId, toReturn);
        }
        else if (result[0].equals("SEND")) {
            this.SEND(message);
        }
        else if (result[0].equals("SUBSCRIBE")) {
            String Genre = result[1].substring(12);
            int SubscriptionId = Integer.parseInt(result[2].substring(3));
            int receipt= Integer.parseInt(result[3].substring(8));
            SUBSCRIBE subscribe = new SUBSCRIBE(Genre, SubscriptionId, receipt, connectionId);
            String toReturn = subscribe.run();
            if (toReturn!=null) {
                connections.send(connectionId, toReturn);
            }
        }
        else if (result[0].equals("UNSUBSCRIBE")) {
            int SubscriptionId = Integer.parseInt(result[1].substring(3));
            int receipt = Integer.parseInt(result[2].substring(8));
            UNSUBSCRIBE unsubscribe = new UNSUBSCRIBE(SubscriptionId, receipt,  connectionId);
            String toReturn = unsubscribe.run();
            if(toReturn!=null) {
                connections.send(connectionId, toReturn);
            }
        }
        else if (result[0].equals("DISCONNECT")) {
            int receipt = Integer.parseInt(result[1].substring(8));
            DISCONNECT disconnect = new DISCONNECT(receipt, connectionId);
            String toReturn = disconnect.run();
            connections.send(connectionId, toReturn);
            connections.disconnect(connectionId);
        }
    }


    @Override
    public boolean shouldTerminate() {
        return ShouldTerminate;
    }

    private void SEND (String message) {
        String[] line = message.split("\n", 10);
        String genre = line[1].substring(12);
        String relevantLine = line[3];
        String toSend="";
        List<User> RelevantUsers = DataStructureHelper.UserMapByGenre.get(genre);
        if (RelevantUsers!=null) {
            for (User user : RelevantUsers) {
                if (user.getLogStatus()) {
                    String SubId = user.getSubscriptionIdMapByGenre2().get(genre).toString();
                    Integer MsgId = DataStructureHelper.messageId;
                    String MessageId = MsgId.toString();
                    toSend = toSend + "MESSAGE" + "\n" + "subscription:" + SubId + "\n" + "Message-id:" + MessageId + "\n" + "destination:" + genre + "\n" + "\n" + relevantLine + "\n" + '\u0000';
                    connections.send(user.getId(), toSend);
                    toSend = "";
                    DataStructureHelper.IncrementMessageId();
                }
            }
        }
    }

}
