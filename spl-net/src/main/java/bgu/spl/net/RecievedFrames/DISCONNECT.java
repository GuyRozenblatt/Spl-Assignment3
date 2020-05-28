package bgu.spl.net.RecievedFrames;

import bgu.spl.net.DataStructureHelper;
import bgu.spl.net.SentFrames.RECIEPT;
import bgu.spl.net.User;
import bgu.spl.net.srv.ConnectionHandler;

import java.util.List;
import java.util.Map;

public class DISCONNECT {

    private int connectionId;
    private int receipt;

    public DISCONNECT(int receipt ,int connectionId) {
        this.connectionId = connectionId;
        this.receipt=receipt;
    }

    public String run () {
        User user = DataStructureHelper.UserMapById.get(connectionId);
        user.setLogStatus(false);

        ////////////////// clear the users subscriptions ///////////////////
        user.getSubscriptionIdMapByGenre().clear();
        user.getSubscriptionIdMapByGenre2().clear();
        user.getGenreList().clear();
        ////////////////// clear the users subscriptions ///////////////////

        for (int i=0; i<user.getGenreList().size(); i++) { // remove the user from every genre he is subscribed to.
            String genre = user.getGenreList().get(i);
            List<User> userList = DataStructureHelper.UserMapByGenre.get(genre);
            userList.remove(user);
        }
        RECIEPT rec = new RECIEPT(receipt);
        return rec.encodeSUBSCRIBE();
    }
}
