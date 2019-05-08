package io.lab.model;

import io.lab.process.MessageReader;

import java.io.*;
import java.net.Socket;

public class Connection implements Runnable, Closeable {

    private final BufferedReader reader;
    private final Socket socket;
    private final MessageReader messageReader;

    public Connection(Socket socket, MessageReader messageReader) throws IOException {
        this.socket = socket;
        this.reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.messageReader = messageReader;
    }

    @Override
    public void run() {
        try {
            String request;
            while ((request = reader.readLine()) != null) {
                messageReader.readMessage(request);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void close() throws IOException {
        this.socket.close();
        this.reader.close();
    }
}
