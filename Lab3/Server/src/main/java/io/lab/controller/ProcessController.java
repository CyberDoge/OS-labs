package io.lab.controller;

import java.io.IOException;

public interface ProcessController {
    void init(int port, int clients) throws IOException;

}
