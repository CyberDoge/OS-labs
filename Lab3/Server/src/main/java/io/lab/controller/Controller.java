package io.lab.controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.UUID;

public class Controller {

    @FXML
    private TextField clientsCount;

    @FXML
    private PasswordField password;

    @FXML
    private Label randomLabel;

    @FXML
    private Label exceptionLabel;

    @FXML
    private TextField portInput;

    public void initialize() {
        randomLabel.setText(UUID.randomUUID().toString());
        portInput.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!newValue.matches("\\d*")) {
                portInput.setText(newValue.replaceAll("[^\\d]", ""));
            }
        });
        clientsCount.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!newValue.matches("\\d*")) {
                clientsCount.setText(newValue.replaceAll("[^\\d]", ""));
            }
        });
        password.textProperty().addListener((observable, oldValue, newValue)->{
            if (!newValue.matches("a-zA-Z0-9{1,5}")) {
                password.setText(newValue.replaceAll("[^a-zA-Z0-9]", ""));
            }
            if(newValue.length() > 5)
                password.setText(oldValue);
        });
    }

    public void startServer() throws IOException {
        int port;
        int clients;
        try {
            port = Integer.parseInt(portInput.getText());
            clients = Integer.parseInt(clientsCount.getText());
            if (port < 1) {
                exceptionLabel.setText("port have to be more than zero");
                return;
            }

            if (clients < 1) {
                exceptionLabel.setText("clients count have to be more than zero");
                return;
            }

            if(!password.getText().equals("pass1")){
                exceptionLabel.setText("wrong password");
                return;
            }
        } catch (NumberFormatException e) {
            exceptionLabel.setText("input values are invalid");
            portInput.setText("");
            return;
        }

        openNewScene(port, clients);
    }

    private void openNewScene(int port, int clients) throws IOException {
        Stage primaryStage = ((Stage) portInput.getScene().getWindow());
        primaryStage.close();

        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/process.fxml"));
        Parent root = fxmlLoader.load();

        ProcessController processController = fxmlLoader.getController();
        processController.init(port, clients);

        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }
}
