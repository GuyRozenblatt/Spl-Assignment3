package bgu.spl.net.RecievedFrames;

import bgu.spl.net.DataStructureHelper;
import bgu.spl.net.SentFrames.RECIEPT;
import bgu.spl.net.User;
import bgu.spl.net.srv.ConnectionHandler;

import java.util.LinkedList;
import java.util.List;

public class SUBSCRIBE {

    private String genre;
    private int SubscriptionId;
    private int receipt;
    private int connectionId;

    public SUBSCRIBE(String genre, int subscriptionId, int receipt, int connectionId) {
        this.genre = genre;
        SubscriptionId = subscriptionId;
        this.receipt = receipt;
        this.connectionId=connectionId;
    }

    public String run() {
        User user = DataStructureHelper.UserMapById.get(connectionId);
        if (!user.getGenreList().contains(genre)) {
            user.getSubscriptionIdMapByGenre().putIfAbsent(SubscriptionId, genre);
            user.getSubscriptionIdMapByGenre2().putIfAbsent(genre, SubscriptionId);
            user.getGenreList().add(genre);

            List<User> userList = DataStructureHelper.UserMapByGenre.get(genre);

            if (userList != null) {
                userList.add(user);
            } else {
                userList = new LinkedList<>();
                DataStructureHelper.UserMapByGenre.putIfAbsent(genre, userList);
                userList.add(user);
            }
            RECIEPT reciept = new RECIEPT(receipt);
            return reciept.encodeSUBSCRIBE();
        }
        return null;
    }
}
