import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.URL;
import java.util.ResourceBundle;

public class MainController implements Initializable {

    @FXML
    public TextField message;

    private Socket socket;
    private DataInputStream dataInputStream;
    private DataOutputStream dataOutputStream;

    public MainController() throws IOException {
        socket = new Socket("localhost", 8080);
        dataInputStream = new DataInputStream(socket.getInputStream());
        dataOutputStream = new DataOutputStream(socket.getOutputStream());
    }


    public String read() throws IOException {
        return dataInputStream.readUTF();
    }

    public void send() throws IOException {
        if(message.getText().isBlank()) return;
        dataOutputStream.writeBytes(message.getText());
        message.setText("");
    }

    public void close() throws IOException {
        socket.close();
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Task<String> dataReader = new Task<>() {
            @Override
            protected String call() throws Exception {
                return read();
            }
        };
        Thread thread = new Thread(dataReader);
        thread.setDaemon(true);
        thread.start();
    }
}
