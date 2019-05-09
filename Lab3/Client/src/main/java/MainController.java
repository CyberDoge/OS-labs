import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

import java.io.*;
import java.net.Socket;

public class MainController implements Closeable {

    @FXML
    public TextField message;

    @FXML
    public Button btnSend;

    private Socket socket;
    private PrintWriter writer;

    public MainController() throws IOException {
        socket = new Socket("localhost", 8080);
        writer = new PrintWriter(socket.getOutputStream());
    }

    public void send() throws IOException {
        if (message.getText().isBlank()) return;
        writer.println(message.getText());
        writer.flush();
        message.setText("");
        message.setEditable(false);
        btnSend.setDisable(true);
        close();
    }

    public void close() throws IOException {
        socket.close();
    }
}
