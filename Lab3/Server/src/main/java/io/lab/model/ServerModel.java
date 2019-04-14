package io.lab.model;

import java.io.IOException;
import java.net.ServerSocket;

public class ServerModel {

    private final ServerSocket serverSocket;

    public ServerModel(int port) throws IOException {
        if(port < 1) throw new IllegalArgumentException("port have to be more then 0");
        serverSocket = new ServerSocket(port);
    }
}
