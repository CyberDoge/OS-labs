package org.lab;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;

import java.util.UUID;

public class Controller {

    @FXML
    private Label randomLabel;

    @FXML
    private Label exceptionLabel;

    @FXML
    private TextField portInput;

    public void initialize() {
        randomLabel.setText(UUID.randomUUID().toString());
    }

    public void startServer() {
        String portStr = portInput.getText();
        try {
            int port = Integer.parseInt(portStr);
            if(port < 1){
                exceptionLabel.setText("port have to be more than zero");
                return;
            }

        }catch (NumberFormatException e){
            exceptionLabel.setText("port value is invalid");
            portInput.setText("");
        }
    }
}
