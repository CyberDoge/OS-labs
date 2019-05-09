package io.lab.controller;

import io.lab.model.ServerModel;
import io.lab.process.MessageReader;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;

import java.io.IOException;

public class ProcessControllerImpl implements ProcessController, MessageReader {
    private ServerModel serverModel;

    @FXML
    private Pane pane;

    @Override
    public void init(int port, int clientsCount) throws IOException {
        this.serverModel = new ServerModel(port, clientsCount, this);
    }

    @Override
    public void readMessage(String message) {
        Platform.runLater(() -> pane.getChildren().add(new Label(message)));
    }
}
