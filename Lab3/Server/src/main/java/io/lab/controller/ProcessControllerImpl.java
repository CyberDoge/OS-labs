package io.lab.controller;

import io.lab.model.ServerModel;
import io.lab.process.MessageReader;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;

import java.io.IOException;

public class ProcessControllerImpl implements ProcessController, MessageReader {
    private ServerModel serverModel;

    @FXML
    private VBox messageVbox;

    @Override
    public void init(int port, int clientsCount) throws IOException {
        this.serverModel = new ServerModel(port, clientsCount, this);
    }

    @Override
    public void readMessage(String message) {
        this.messageVbox.getChildren().add(new TextField(message));
    }
}
