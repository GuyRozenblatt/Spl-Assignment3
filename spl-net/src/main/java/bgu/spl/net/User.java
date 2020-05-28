package bgu.spl.net;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

public class User {

    private String UserName;
    private String Password;
    private boolean LogStatus;

    public void setConnectionHandlerId(int connectionHandlerId) {
        ConnectionHandlerId = connectionHandlerId;
    }

    private int ConnectionHandlerId;
    private ConcurrentHashMap<Integer, String> SubscriptionIdMapByGenre; // <SubscriptionId, genre>
    private ConcurrentHashMap<String, Integer> SubscriptionIdMapByGenre2; // <genre, SubscriptionId>
    private List<String> genreList;

    public User(String userName, String password, boolean logStatus, int id) {
        UserName = userName;
        Password = password;
        LogStatus = logStatus;
        this.ConnectionHandlerId = id;
        SubscriptionIdMapByGenre=new ConcurrentHashMap<>();
        SubscriptionIdMapByGenre2 = new ConcurrentHashMap<>();
        genreList = new LinkedList<>();
    }

    public String getPassword() {
        return Password;
    }

    public int getId() {
        return ConnectionHandlerId;
    }

    public boolean getLogStatus() {
        return LogStatus;
    }

    public void setLogStatus(boolean status) {
        LogStatus = status;
    }

    public ConcurrentHashMap<Integer, String> getSubscriptionIdMapByGenre() {
        return SubscriptionIdMapByGenre;
    }

    public List<String> getGenreList() {
        return genreList;
    }

    public ConcurrentHashMap<String, Integer> getSubscriptionIdMapByGenre2() {
        return SubscriptionIdMapByGenre2;
    }
    
}
