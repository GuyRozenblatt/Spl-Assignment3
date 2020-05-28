package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl<T> implements Connections<T> {

    private ConcurrentHashMap<Integer, ConnectionHandler<T>> ConnectionHandlerMap = new ConcurrentHashMap<>();

    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler connectionHandler = ConnectionHandlerMap.get(connectionId);
        if (connectionHandler!=null) {
            connectionHandler.send(msg);
            return true;
        }
        else return false;
    }

    @Override
    public void send(String channel, T msg) {

    }

    @Override
    public void disconnect(int connectionId) {
        ConnectionHandlerMap.remove(connectionId);
    }

    public void addHandler(int connectionHandlerId, ConnectionHandler<T> handler) {
        ConnectionHandlerMap.put(connectionHandlerId, handler );
    }
}
