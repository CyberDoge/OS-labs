package io.lab.model;

import io.lab.process.MessageReader;

import java.io.Closeable;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class Connection implements Runnable, Closeable {

    private final DataInputStream dataInputStream;
    private final DataOutputStream dataOutputStream;
    private final Socket socket;
    private final MessageReader messageReader;

    public Connection(Socket socket, MessageReader messageReader) throws IOException {
        this.socket = socket;
        this.dataInputStream = new DataInputStream(socket.getInputStream());
        this.dataOutputStream = new DataOutputStream(socket.getOutputStream());
        this.messageReader = messageReader;
    }

    @Override
    public void run() {
        try {
            messageReader.readMessage(this.dataInputStream.readUTF());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendMessage(String message) throws IOException {
        this.dataOutputStream.writeUTF(message);
    }

    @Override
    public void close() throws IOException {
        this.socket.close();
        this.dataInputStream.close();
        this.dataOutputStream.close();
    }
}
