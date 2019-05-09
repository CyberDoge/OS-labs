package io.lab.model;

import io.lab.process.MessageReader;
import javafx.concurrent.Task;

import java.io.Closeable;
import java.io.IOException;
import java.net.ServerSocket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServerModel implements Closeable {

    private final ServerSocket serverSocket;
    //thread pool
    private final ExecutorService service;

    public ServerModel(int port, int clientCount, MessageReader messageReader) throws IOException {
        if (port < 1) throw new IllegalArgumentException("port have to be more then 0");
        this.serverSocket = new ServerSocket(port);
        this.service = Executors.newFixedThreadPool(2);

        new Thread(()->{
            for (int i = 0; i < clientCount; i++) {
                try {
                    service.submit(new Connection(serverSocket.accept(), messageReader));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    @Override
    public void close() throws IOException {
        this.service.shutdownNow();
        serverSocket.close();
    }
}
