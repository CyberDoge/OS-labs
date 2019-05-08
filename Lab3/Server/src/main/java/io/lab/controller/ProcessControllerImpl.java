package io.lab.controller;

import io.lab.model.ServerModel;
import io.lab.process.MessageReader;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;

import java.io.IOException;

public class ProcessControllerImpl implements ProcessController, MessageReader {
    private ServerModel serverModel;

    @FXML
    private TextArea textArea;

    @Override
    public void init(int port, int clientsCount) throws IOException {
        this.serverModel = new ServerModel(port, clientsCount, this);
    }

    @Override
    public void readMessage(String message) {
        textArea.setText(textArea.getText() + message);
    }
}
