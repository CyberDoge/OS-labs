package org.lab.model;

import java.io.IOException;
import java.net.ServerSocket;

public class ServerModel {
    private final Integer port;

    private final ServerSocket serverSocket;

    public ServerModel(Integer port) throws IOException {
        if(port < 1) throw new IllegalArgumentException("port have to be more then 0");
        this.port = port;
        serverSocket = new ServerSocket(port);
    }
}
