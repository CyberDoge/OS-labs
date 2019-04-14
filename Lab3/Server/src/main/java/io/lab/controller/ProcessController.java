package io.lab.controller;

import io.lab.model.ServerModel;

import java.io.IOException;

public class ProcessController {
    private ServerModel serverModel;

    public void init(int port, int clients) throws IOException {
        this.serverModel = new ServerModel(port);
    }
}
