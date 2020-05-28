package bgu.spl.net;

import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

public class DataStructureHelper {

    public static ConcurrentHashMap<String, User> UserMapByName = new ConcurrentHashMap<>(); // <UserName, user>
    public static ConcurrentHashMap<Integer, User> UserMapById = new ConcurrentHashMap<>(); // <UserConnectionId, user>
    public static ConcurrentHashMap<String, List<User>> UserMapByGenre = new ConcurrentHashMap<>(); // <genre, list of users registered to the genre>
    public static int messageId=1;

    public static void IncrementMessageId() {
        messageId++;
    }

    public static void updateID (int newId, int oldId) {
        User user= UserMapById.get(oldId);
        UserMapById.get(oldId).setConnectionHandlerId(newId);
        UserMapById.remove(oldId);
        UserMapById.put(newId, user);
    }

}
