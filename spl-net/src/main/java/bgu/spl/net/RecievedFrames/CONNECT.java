package bgu.spl.net.RecievedFrames;

import bgu.spl.net.DataStructureHelper;
import bgu.spl.net.SentFrames.CONNECTED;
import bgu.spl.net.SentFrames.ERROR;
import bgu.spl.net.User;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.ConnectionsImpl;

public class CONNECT {

    private String loginName;
    private String passcode;
    private int connectionHandlerId;
    private String version;

    public CONNECT (String loginName, String passcode, int connectionHandlerId, String version) {
        this.loginName=loginName;
        this.passcode=passcode;
        this.connectionHandlerId = connectionHandlerId;
        this.version=version;
    }

    public String run () {
        User user = DataStructureHelper.UserMapByName.get(loginName);
        if (user != null) {
            if (user.getLogStatus()) {
                ERROR error = new ERROR("User already logged in");
                return error.encode();
            }
            else {
                if(!user.getPassword().equals(passcode)) {
                    ERROR error = new ERROR("Wrong password");
                    return error.encode();
                }
                else { // here we know the user exists but isnt logged in.
                    user.setLogStatus(true);
                    CONNECTED connected = new CONNECTED(version);
                    int oldId= DataStructureHelper.UserMapByName.get(loginName).getId();
                    DataStructureHelper.updateID(connectionHandlerId, oldId);
                    return connected.encode();
                }
            }
        }
        else { // here we know the user doesnt exist so we create him.
            user = new User(loginName, passcode, true, connectionHandlerId);
            DataStructureHelper.UserMapById.putIfAbsent(connectionHandlerId, user);
            DataStructureHelper.UserMapByName.putIfAbsent(loginName, user);
            CONNECTED connected = new CONNECTED(version);
            return connected.encode();
        }
    }

}
