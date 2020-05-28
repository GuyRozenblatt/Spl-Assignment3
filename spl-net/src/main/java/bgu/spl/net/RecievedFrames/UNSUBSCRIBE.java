package bgu.spl.net.RecievedFrames;

import bgu.spl.net.DataStructureHelper;
import bgu.spl.net.SentFrames.RECIEPT;
import bgu.spl.net.User;
import bgu.spl.net.srv.ConnectionHandler;

import java.util.List;

public class UNSUBSCRIBE {

    private int SubscriptionId;
    private int connectionId;
    private String genre;
    private int receipt;

    public UNSUBSCRIBE(int subscriptionId, int receipt, int connectionId) {
        SubscriptionId = subscriptionId;
        this.connectionId = connectionId;
        this.receipt = receipt;
    }

    public String run() {
        User user = DataStructureHelper.UserMapById.get(connectionId);
        genre = user.getSubscriptionIdMapByGenre().get(SubscriptionId);
        boolean check = user.getGenreList().remove(genre);

        if (user != null && check) {
            genre = user.getSubscriptionIdMapByGenre().get(SubscriptionId);
            user.getSubscriptionIdMapByGenre().remove(SubscriptionId);
            user.getSubscriptionIdMapByGenre2().remove(genre);
            List<User> userList = DataStructureHelper.UserMapByGenre.get(genre);
            if (userList != null) {
                userList.remove(user);
            }
            RECIEPT reciept = new RECIEPT(receipt);
            return reciept.encodeUNSUBSCRIBE();
        }
        return null;
    }

}
