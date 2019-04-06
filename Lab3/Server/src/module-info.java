module Server {
    requires javafx.controls;
    requires javafx.fxml;

    opens org.lab to javafx.fxml;
    exports org.lab;
}