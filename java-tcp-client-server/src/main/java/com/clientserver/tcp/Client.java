package com.clientserver.tcp;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class Client {

    public static void main(String[] args) throws IOException {
        // Inizializza una socket TCP connessa all'indirizzo IP e alla porta del server
        Socket socket = new Socket("localhost", 8080);

        // Invia al server una richiesta
        OutputStream output = socket.getOutputStream();
        output.write("conversione".getBytes());

        // Ricevi dal server una risposta
        InputStream input = socket.getInputStream();
        byte[] bytes = new byte[1024];
        input.read(bytes);

        // Stampa la risposta del server
        System.out.println(new String(bytes));

        // Chiude il socket
        socket.close();
    }
}